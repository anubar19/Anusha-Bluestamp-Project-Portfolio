# WALL-E Emotive Robot
The WALL-E Emotive Robot detects how far it is from another object and displays an "emotion" that corresponds with that distance. It has and ultrasonic sensor which transmits and receives a signal to determine how far the nearest object is. Using that distance, an emotion is selected, for example, if the sensor detects an object that is within 10 centimeters of the robot, it will display anger. There are four main aspects of expressing an emotion: the LED matrices (the eyes), the LCD which says what emotion is being expressed, the two servos for the neck, and the two micro servos that are the robot's eyebrows. Each component is programmed to perform a specific action based on the distance calculated by the ultrasonic sensor. 
<!--| **Engineer** | **School** | **Area of Interest** | **Grade** |
|:--:|:--:|:--:|:--:|-->

| Anusha B | Monta Vista High School | Mechanical Engineering | Incoming Sophmore |

<!--![Headstone Image](logo.svg)-->
  
<a href="https://www.instructables.com/Emotionally-Responsive-Robot/"> Project Guide </a>

# Final Milestone
<iframe width="560" height="315" src="https://www.youtube.com/embed/QYzmalx_MOU" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

My final milestone was to finish the programming of the robot. At first, I was trying to upload the code provided in the guide, but I was getting many errors with it and it was not completely compatible with my project because my parts and wiring were slightly different. Due to this, I decided to write my own program rather than trying to alter the given code. 

There were two main parts that I still had to program: the LED matrices, and the servos. I was able to get the LED matrices to work as desired by replacing them again and wiring two single matrices together. I also used a different library than before, called LedControlMS, to program them so that I could display different patterns on each matrix, but only use three pins to connect them to the Arduino. The servos took slightly longer to program. Initially, when I wired the servos and uploaded code, the servos would not respond at all. I then changed the pins the servos were connected to from analog to digital pins, and I was then able to upload code. The servos required an external source of power since the arduino was not powerful enough to power them, so I also connected 4 AA batteries which provided 6 volts for the servos to use.

I did not expect that the programming process would take so long, especially because I did not think I would need to write my own program. Writing my own program gave me more control over the function of my robot, and I was able to gain a deeper understanding of how each component functions.

# Second Milestone

<iframe width="560" height="315" src="https://www.youtube.com/embed/RuqsUkzLOlw" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

My second milestone was to finish assembling the "body" of the robot. I had to get all the parts 3D printed so that they could fit all the components, like the sensor and the LCD. The box at the bottom is what holds the circuit, and it was not ready for the longest time. The original plan was to use a plastic box and dremel out the the spaces I needed to support the components. However, the plastic was quite flimsy and thin, so when I tried using the dremel to cut it, the plastic slightly melted. Since I would have had to cut out many large pieces, it was best to 3D print the box instead. After switching to the 3D printed box, I realized that it was not big enough to store the entire circuit, so I switched to a smaller breadboard. I then screwed in the LCD and ultrasonic sensor into the box and the two micro servos into the face.

I changed my LED matrices from the previous set of four to two single matrices that I wired together. However, when I made this change, I was unable to upload code to them because they were both cut out of the set of four, which damaged their individual connections. I was able to program the LCD and ultrasonic sensor to work together to display the distance detected by the sensor onto the LCD. I can now focus on my final milestone, which is to program all the components of the robot, like the LED matrices and servos, to work together. 

# First Milestone

<iframe width="560" height="315" src="https://www.youtube.com/embed/AAFQRoqYj6Q" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

My first milestone was to finish wiring all my components together and to be able to program the LED matrix so that a design of my choice shows up on it. In order to start wiring, I first had to solder resistors, capacitors, integrated circuits, and pin headers to the wave shield, which I placed onto the arduino. Since I have so many components that I need to connect to the Arduino, I used a breadboard facilitate these connections. I also put together the pan-tilt servos and their mounts and attached them to the 3D printed "neck" piece. My biggest challenge in finishing the wiring was connecting and programming the LED matrices. My matrices were different than the ones listed in the guide, so I had to use different pins to connect them to the Arduino. I also had to use a different Arduino library called LedControl to program the LED matrices to display a pattern. My first set of matrices did not respond to any uploaded code, so I had to replace them with a new set, which successfuly responded to code and displayed a programmed pattern. I now want to work towards my second milestone, which is assembling my 3D printed pieces to form the "body" of the robot.

# Starter Project

<iframe width="560" height="315" src="https://www.youtube.com/embed/yNEFJC3x2WI" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

My starter project was the Exploding Star Color Organ, which responds to sound by lighting up various LEDs. This was not my original starter project, but I had to change it because of some soldering mistakes that melted one of the components. Soldering this project went quite smoothly, and I enjoyed learning about the the various components involved in the circuit and their functions.

<a href="https://www.instructables.com/Exploding-Star-Color-Organ/"> Starter Project Guide </a>

<!--**Don't forget to replace the text below with the embedding for your milestone video. Go to Youtube, click Share -> Embed, and copy and paste the code to replace what's below.**-->

# Schematics

![Schematics](Anusha_BlueStampPortfolio/Files/brobot_schematic.png)

In my project, I connected my LED matrix backpack to pins 13 (DIN), 12 (CS), and 11 (CLK). The signal wires of the servos are not connected to the analog pins, instead, they are connected to pins 3, 4, 5, and 6. I also used a smaller breadboard in order to condense my circuit to fit it inside the box.
<!--Here's where you'll put images of your schematics. [Tinkercad](https://www.tinkercad.com/blog/official-guide-to-tinkercad-circuits) and [Fritzing](https://fritzing.org/learning/) are both great resoruces to create professional schematic diagrams, though BSE recommends Tinkercad becuase it can be done easily and for free in the browser.--> 

# Code
![Code](Anusha_BlueStampPortfolio/Files/emotive_robot_code.ino)
<!--Here's where you'll put your code. The syntax below places it into a block of code. Follow the guide [here]([url](https://www.markdownguide.org/extended-syntax/)) to learn how to customize it to your project needs. -->


# Bill of Materials
<!--Here's where you'll list the parts in your project. To add more rows, just copy and paste the example rows below.
Don't forget to place the link of where to buy each component inside the quotation marks in the corresponding row after href =. Follow the guide [here]([url](https://www.markdownguide.org/extended-syntax/)) to learn how to customize this to your project needs. -->

| **Part** | **Note** | **Price** | **Link** |
|:--:|:--:|:--:|
| Arduino UNO REV3 | Facilitates the project's function | $28.50 | <a href="https://www.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/"> Link </a> |
|  Adafruit Wave Shield for Arduino | Simplifies the interface of the Arduino. | $22.00| <a href="https://www.adafruit.com/product/94"> Link </a> |
| 8x8 LED Matrix + Backpack | Acts as the robot's "eyes" and displays its "emotion" | $7.99 | <a href="https://www.amazon.com/Alinan-MAX7219-Matrix-Display-Control/dp/B09TSJL783/ref=asc_df_B09TSJL783/?tag=hyprod-20&linkCode=df0&hvadid=599693037728&hvpos=&hvnetw=g&hvrand=8238989648180540621&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9032183&hvtargid=pla-1923353677832&psc=1/"> Link </a> |
| 16x2 LCD Character Display w/ I2C backpack | Displays the robot's greeting and emotions | $9.99 | <a href="https://www.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/"> Link </a> |
| 2 Servo Motors | Pan-tilt servos that act as the robot's neck and head| $14.99 | <a href="https://www.amazon.com/180%C2%B0Metal-Waterproof-Airplane-Helicopter-Mechanical/dp/B09JWK2GB3/ref=asc_df_B09JWK2GB3/?tag=hyprod-20&linkCode=df0&hvadid=598270536205&hvpos=&hvnetw=g&hvrand=11300398354597975709&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9032183&hvtargid=pla-1675722646259&th=1"> Link </a> |

<!---| Item Name | What the item is used for | $Price | <a href="https://www.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/"> Link </a> |
|:--:|:--:|:--:|:--:|
| Item Name | What the item is used for | $Price | <a href="https://www.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/"> Link </a> |
|:--:|:--:|:--:|:--:|
| Item Name | What the item is used for | $Price | <a href="https://www.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/"> Link </a> |
|:--:|:--:|:--:|:--:|
| Item Name | What the item is used for | $Price | <a href="https://www.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/"> Link </a> |
|:--:|:--:|:--:|:--:|-->

<!--- Other Resources/Examples
One of the best parts about Github is that you can view how other people set up their own work. Here are some past BSE portfolios that are awesome examples. You can view how they set up their portfolio, and you can view their index.md files to understand how they implemented different portfolio components.
- [Example 1](https://trashytuber.github.io/YimingJiaBlueStamp/)
- [Example 2](https://sviatil0.github.io/Sviatoslav_BSE/)
- [Example 3](https://arneshkumar.github.io/arneshbluestamp/)-->

<!--To watch the BSE tutorial on how to create a portfolio, click here.-->
