
# ASL Robotic Arm
<!--Replace this text with a brief description (2-3 sentences) of your project. This description should draw the reader in and make them interested in what you've built. You can include what the biggest challenges, takeaways, and triumphs from completing the project were. As you complete your portfolio, remember your audience is less familiar than you are with all that your project entails!-->

The ASL Robotic Arm uses image detection to recognize certain letters and displays the ASL representation of that letter. It uses a robotic hand which uses 5 servos to control the movement of each finger.

<!---You should comment out all portions of your portfolio that you have not completed yet, as well as any instructions: -->

| **Engineer** | **School** | **Area of Interest** | **Grade** |
|:--:|:--:|:--:|:--:|
| Anusha B. | Monta Vista High School | Mechanical Engineering | Incoming Junior

<!---**Replace the BlueStamp logo below with an image of yourself and your completed project. Follow the guide [here](https://tomcam.github.io/least-github-pages/adding-images-github-pages-site.html) if you need help.** -->

![Headstone Image](Files/Anusha_B.png)
  
<!--- # Final Milestone

**Don't forget to replace the text below with the embedding for your milestone video. Go to Youtube, click Share -> Embed, and copy and paste the code to replace what's below.**

<iframe width="560" height="315" src="https://www.youtube.com/embed/F7M7imOVGug" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

For your final milestone, explain the outcome of your project. Key details to include are:
- What you've accomplished since your previous milestone
- What your biggest challenges and triumphs were at BSE
- A summary of key topics you learned about
- What you hope to learn in the future after everything you've learned at BSE -->



# Second Milestone

<iframe width="560" height="315" src="https://www.youtube.com/embed/jk74IgKE5pA?si=5Ikt3A3PYuS-8cEA" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

For my second milestone, I was able to get the Raspberry Pi to recognize letters. I did this by using TensorFlow along with EasyOCR. OCR stands for Optical Character Recognition, which is responsible for identifying letters, numbers, special characters, as well as full words. I initially tried using OpenCV to perform text recognition, but I was running into many errors when trying to turn on my camera with the necessary Picamera library. The difference between OpenCV and EasyOCR is that OpenCV is a library that is used for computer vision and object detection, whereas EasyOCR is used specifically for extracting text from an image. After I made the switch to TensorFlow, it started working immediately.

The video feed displaying the camera’s input is currently very slow at about 0.3 FPS. This is because the text recognition process takes a heavy toll on the Raspberry Pi, making it difficult to process the frames from the camera while simultaneously displaying video at a high framerate. I made many attempts to speed up the video feed. I tried to set the framerate in code, speed up image processing by checking every 10 frames instead of checking every single frame, and trigger the text recognition process using keyboard input. However, none of these attempts sped up the video display. I do want to try finding more potential solutions for this later on.

I am now going to focus on completing my third milestone which is to get my robotic hand to respond to the video input by signing the letter detected by the Pi. I have already gotten the hand working as my First Milestone, so I need to write a new file with code that handles text recognition as well as the servo positions for the hand.

<!-- For your second milestone, explain what you've worked on since your previous milestone. You can highlight:
- Technical details of what you've accomplished and how they contribute to the final goal
- What has been surprising about the project so far
- Previous challenges you faced that you overcame
- What needs to be completed before your final milestone -->

## Flowchart
![Headstone Image](Files/ProjectProcessFlowchart.png)

The image above is a representation of how the software aspect of my project works. As part of my second milestone, I needed to establish an input/output system. The input is the camera’s video feed which the Raspberry Pi processes frame-by-frame using EasyOCR. In order to accomplish this milestone, I made the output a simple print statement displaying, “Cam detected,” when the Pi detected the word “Cam” in the video frame. For the final product, the output would be the robotic hand signing a letter.

In my first milestone, I programmed the robotic hand to form 4 letters, but there was no input that it needed to respond to. For my next milestone, I am going to get the hand to form letters in response to the Pi detecting them, and I am going to write more functions so that the hand can form as many letters as possible.

## Examples

![Headstone Image](Files/SERVO.heic)

![Headstone Image](Files/Raspberry.heic)

![Headstone Image](Files/FrAMe.heic)


## Code
```python
# SPDX-FileCopyrightText: 2021 Limor Fried/ladyada for Adafruit Industries
# SPDX-FileCopyrightText: 2021 Melissa LeBlanc-Williams for Adafruit Industries
#
# SPDX-License-Identifier: MIT

import time
import logging
import argparse
import pygame
import os
import subprocess
import sys
import numpy as np
import signal
import rpi_vision
import easyocr # importing easy ocr

CONFIDENCE_THRESHOLD = 0.5   # at what confidence level do we say we detected a thing
PERSISTANCE_THRESHOLD = 0.25  # what percentage of the time we have to have seen a thing

def dont_quit(signal, frame):
   print('Caught signal: {}'.format(signal))
signal.signal(signal.SIGHUP, dont_quit)

# App
from rpi_vision.agent.capturev2 import PiCameraStream

logging.basicConfig()
logging.getLogger().setLevel(logging.INFO)

# initialize the display
pygame.init()
# screen = pygame.display.set_mode((0,0), pygame.FULLSCREEN)
screen_width = 800
screen_height = 600
screen = pygame.display.set_mode((screen_width, screen_height))

capture_manager = None

FPS = 60

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('--include-top', type=bool,
                        dest='include_top', default=True,
                        help='Include fully-connected layer at the top of the network.')

    parser.add_argument('--tflite',
                        dest='tflite', action='store_true', default=False,
                        help='Convert base model to TFLite FlatBuffer, then load model into TFLite Python Interpreter')

    parser.add_argument('--rotation', type=int, choices=[0, 90, 180, 270],
                        dest='rotation', action='store', default=0,
                        help='Rotate everything on the display by this amount')
    args = parser.parse_args()
    return args

last_seen = [None] * 10
last_spoken = None

def main(args):
    global last_spoken, capture_manager

    capture_manager = PiCameraStream(preview=False)
    
    capture_manager.camera.framerate=60
    
    capture_manager.camera.resolution=(320,240)

    if args.rotation in (0, 180):
        buffer = pygame.Surface((screen.get_width(), screen.get_height()))
    else:
        buffer = pygame.Surface((screen.get_height(), screen.get_width()))

    pygame.mouse.set_visible(False)
    screen.fill((0,0,0))
    try:
        splash = pygame.image.load(os.path.dirname(sys.argv[0])+'/bchatsplash.bmp')
        splash = pygame.transform.rotate(splash, args.rotation)
        # Scale the square image up to the smaller of the width or height
        splash = pygame.transform.scale(splash, (min(screen.get_width(), screen.get_height()), min(screen.get_width(), screen.get_height())))
        # Center the image
        screen.blit(splash, ((screen.get_width() - splash.get_width()) // 2, (screen.get_height() - splash.get_height()) // 2))

    except pygame.error:
        pass
    pygame.display.update()

    # Let's figure out the scale size first for non-square images
    scale = max(buffer.get_height() // capture_manager.resolution[1], 1)
    scaled_resolution = tuple([x * scale for x in capture_manager.resolution])

    # use the default font, but scale it
    smallfont = pygame.font.Font(None, 24 * scale)
    medfont = pygame.font.Font(None, 36 * scale)
    bigfont = pygame.font.Font(None, 48 * scale)

    #model = MobileNetV2Base(include_top=args.include_top)
    reader = easyocr.Reader(['en'])
    capture_manager.start()
    
    # frame_count = 0
    while not capture_manager.stopped:
        if capture_manager.frame is None: 
            continue
        #and frame_count % 10 == 0:
        buffer.fill((0,0,0))
        frame = capture_manager.read()
        # get the raw data frame & swap red & blue channels
        previewframe = np.ascontiguousarray(capture_manager.frame)
        # make it an image
        img = pygame.image.frombuffer(previewframe, capture_manager.resolution, 'RGB')
        img = pygame.transform.scale(img, scaled_resolution)

        cropped_region = (
            (img.get_width() - buffer.get_width()) // 2,
            (img.get_height() - buffer.get_height()) // 2,
            buffer.get_width(),
            buffer.get_height()
        )

        # draw it!
        buffer.blit(img, (0, 0), cropped_region)
        
        
        timestamp = time.monotonic()
        result = reader.readtext(np.array(frame), detail=1)
        prediction = [(bbox, text, conf) for bbox, text, conf in result]
        logging.info(prediction)
        delta = time.monotonic() - timestamp
        logging.info("OCR inference took %d ms, %0.1f FPS" % (delta * 1000, 1 / delta))
        print(last_seen)
        

        # add FPS & temp on top corner of image
        fpstext = "%0.1f FPS" % (1/delta,)
        fpstext_surface = smallfont.render(fpstext, True, (255, 0, 0))
        fpstext_position = (buffer.get_width()-10, 10) # near the top right corner
        buffer.blit(fpstext_surface, fpstext_surface.get_rect(topright=fpstext_position))
        try:
            temp = int(open("/sys/class/thermal/thermal_zone0/temp").read()) / 1000
            temptext = "%d\N{DEGREE SIGN}C" % temp
            temptext_surface = smallfont.render(temptext, True, (255, 0, 0))
            temptext_position = (buffer.get_width()-10, 50) # near the top right corner
            buffer.blit(temptext_surface, temptext_surface.get_rect(topright=temptext_position))
        except OSError:
            pass

        for p in prediction:
            label, name, conf = p
            if conf > CONFIDENCE_THRESHOLD:
                print("Detected", name)
                
                if name == "Cam":
                    print("Cam detected!")

                persistant_obj = False  # assume the object is not persistant
                last_seen.append(name)
                last_seen.pop(0)

                inferred_times = last_seen.count(name)
                if inferred_times / len(last_seen) > PERSISTANCE_THRESHOLD:  # over quarter time
                    persistant_obj = True

                detecttext = name.replace("_", " ")
                detecttextfont = None
                for f in (bigfont, medfont, smallfont):
                    detectsize = f.size(detecttext)
                    if detectsize[0] < screen.get_width(): # it'll fit!
                        detecttextfont = f
                        break
                else:
                    detecttextfont = smallfont # well, we'll do our best
                detecttext_color = (0, 255, 0) if persistant_obj else (255, 255, 255)
                detecttext_surface = detecttextfont.render(detecttext, True, detecttext_color)
                detecttext_position = (buffer.get_width()//2,
                                       buffer.get_height() - detecttextfont.size(detecttext)[1])
                buffer.blit(detecttext_surface, detecttext_surface.get_rect(center=detecttext_position))

                if persistant_obj and last_spoken != detecttext:
                    subprocess.call(f"echo {detecttext} | festival --tts &", shell=True)
                    last_spoken = detecttext
                break
        else:
            last_seen.append(None)
            last_seen.pop(0)
            if last_seen.count(None) == len(last_seen):
                last_spoken = None

        screen.blit(pygame.transform.rotate(buffer, args.rotation), (0,0))
        pygame.display.update()
        # frame_count += 1

if __name__ == "__main__":
    args = parse_args()
    try:
        main(args)
    except KeyboardInterrupt:
        capture_manager.stop()
```

# First Milestone

<!---**Don't forget to replace the text below with the embedding for your milestone video. Go to Youtube, click Share -> Embed, and copy and paste the code to replace what's below.** -->

<iframe width="560" height="315" src="https://www.youtube.com/embed/g3mT7fR1rYY?si=DX0YXWGzsUZFmJ7D" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

My project is an ASL Robotic Arm. The end goal is for it to use image detection to identify written letters and form the ASL representation of it. For the first milestone, I set up my Raspberry Pi, connected the hand, and programmed it. The hand is made up of 5 servos which control the fingers. In order to get the hand to form letters in ASL, I had to individually program each finger. Each finger moves to a position determined by the angle that the servo rotated.Since there is limited mobility for the hand, it is incapable of forming all 26 letters, but it was able to spell "blue". 

I faced a few challenges in completing this milestone. First, I was finding it difficult to set up my Raspberry Pi, so I had to go over documentation and various resources to get it functioning. Additionally, I had trouble compiling my code because my Python libraries were not located in the correct directories. Afterwards, I had to plug in the Pi to an external power source in order to power the servos. 

My next steps include working on my second milestone, which is getting the letter detection aspect working, and I want to add a couple servos to the bottom of the hand to give it more mobility so that it can form more than just 12 letters.

## Servo Hat
![Headstone Image](Files/Servo_Hat_Image.png)

The Servo Hat is what allows me to connect so many servos to my Raspberry Pi at once. It connects to the Pi through the GPIO pins and sits on top. On the other side of the Servo Hat, there are pins that make room for up to 16 servos. Each servo takes up 3 pins for ground, power, and signal. By connecting the servos through this method, I can program them using the Adafruit ServoKit library, which lets me set each servo to a specified degree.

## Code
```python
from time import *
from adafruit_servokit import ServoKit
print(1)
kit = ServoKit(channels=16)
print(2)
kit.servo[0].angle = 0
kit.servo[1].angle = 180
kit.servo[2].angle = 180
kit.servo[3].angle = 180
kit.servo[4].angle = 180

sleep(3)

#letter B
kit.servo[0].angle = 180
kit.servo[1].angle = 180
kit.servo[2].angle = 180
kit.servo[3].angle = 180
kit.servo[4].angle = 180

sleep(3)

#letter L
kit.servo[0].angle = 0
kit.servo[1].angle = 180
kit.servo[2].angle = 0
kit.servo[3].angle = 0
kit.servo[4].angle = 0

sleep(3)

#letter L
kit.servo[0].angle = 180
kit.servo[1].angle = 180
kit.servo[2].angle = 180
kit.servo[3].angle = 0
kit.servo[4].angle = 0

sleep(3)

#letter E
kit.servo[0].angle = 180
kit.servo[1].angle = 0
kit.servo[2].angle = 0
kit.servo[3].angle = 0
kit.servo[4].angle = 0

sleep(3)
```

<!--- For your first milestone, describe what your project is and how you plan to build it. You can include:
- An explanation about the different components of your project and how they will all integrate together
- Technical progress you've made so far
- Challenges you're facing and solving in your future milestones
- What your plan is to complete your project -->

<!--- # Schematics 
Here's where you'll put images of your schematics. [Tinkercad](https://www.tinkercad.com/blog/official-guide-to-tinkercad-circuits) and [Fritzing](https://fritzing.org/learning/) are both great resoruces to create professional schematic diagrams, though BSE recommends Tinkercad becuase it can be done easily and for free in the browser. 

# Code
Here's where you'll put your code. The syntax below places it into a block of code. Follow the guide [here]([url](https://www.markdownguide.org/extended-syntax/)) to learn how to customize it to your project needs. 

```c++
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello World!");
}

void loop() {
  // put your main code here, to run repeatedly:

}
```

# Bill of Materials
Here's where you'll list the parts in your project. To add more rows, just copy and paste the example rows below.
Don't forget to place the link of where to buy each component inside the quotation marks in the corresponding row after href =. Follow the guide [here]([url](https://www.markdownguide.org/extended-syntax/)) to learn how to customize this to your project needs. 

| **Part** | **Note** | **Price** | **Link** |
|:--:|:--:|:--:|:--:|
| Item Name | What the item is used for | $Price | <a href="https://www.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/"> Link </a> |
| Item Name | What the item is used for | $Price | <a href="https://www.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/"> Link </a> |
| Item Name | What the item is used for | $Price | <a href="https://www.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/"> Link </a> |

# Other Resources/Examples
One of the best parts about Github is that you can view how other people set up their own work. Here are some past BSE portfolios that are awesome examples. You can view how they set up their portfolio, and you can view their index.md files to understand how they implemented different portfolio components.
- [Example 1](https://trashytuber.github.io/YimingJiaBlueStamp/)
- [Example 2](https://sviatil0.github.io/Sviatoslav_BSE/)
- [Example 3](https://arneshkumar.github.io/arneshbluestamp/) -->

<!---To watch the BSE tutorial on how to create a portfolio, click here.-->

[Homepage](./index.md)
