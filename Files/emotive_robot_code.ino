#include <LiquidCrystal_I2C.h>
#include <LedControlMS.h>
#include <Servo.h>

// pins for LED matrix
int DIN = 13;
int CS = 12;
int CLK = 11;
// number of devices being programmed
#define NUM_DEVICE 2
// pins for all the buttons
#define BLACK_PIN 9
#define BLUE_PIN 2
#define YELLOW_PIN A3
#define WHITE_PIN A2
#define GREEN_PIN A1
#define RED_PIN A0
// pins for ultrasonic sensor
const int triggerPin = 7;
const int echoPin = 8;
// used to get distance from another object
float pulse_width, distance;
// instance of LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
// instance if LED matrix
LedControl ledmatrix = LedControl(DIN, CLK, CS, NUM_DEVICE);
// instances of servos used to convery robot's emotion
Servo pan;  
Servo tilt;
Servo leftBrow;
Servo rightBrow;
// byte arrays with LED matrix patterns for each emotion
byte happyL_bmp[8] =
{ B00000000,
B00011100,
B00100100,
B01011100,
B01011100,
B00100100,
B00011100,
B00000000 };
byte happyR_bmp[8] =
{ B00000000,
B00011100,
B00100100,
B01011100,
B01011100,
B00100100,
B00011100,
B00000000 };
byte neutralL_bmp[8] =
{ B00000000,
B00111100,
B01000010,
B01011010,
B01011010,
B01000010,
B00111100,
B00000000 };
byte neutralR_bmp[8] =
{ B00000000,
B00111100,
B01000010,
B01011010,
B01011010,
B01000010,
B00111100,
B00000000 };
byte angryL_bmp[8] =
{ B00000000,
B00001100,
B00010010,
B00111010,
B01011010,
B11000010,
B00111100,
B00000000 };
byte angryR_bmp[8] =
{ B00000000,
B00111100,
B11000010,
B01011010,
B00111010,
B00010010,
B00001100,
B00000000 };
byte surprisedL_bmp[8] =
{ B01111110,
B10000001,
B10000001,
B10011001,
B10011001,
B10000001,
B10000001,
B01111110 };
byte surprisedR_bmp[8] =
{ B01111110,
B10000001,
B10000001,
B10011001,
B10011001,
B10000001,
B10000001,
B01111110 };
byte sadL_bmp[8] =
{ B00000000,
B00111100,
B01000010,
B01011010,
B00111010,
B00010010,
B00001100,
B00000000 };
byte sadR_bmp[8] =
{ B00000000,
B00001100,
B00010010,
B00111010,
B01011010,
B01000010,
B00111100,
B00000000 };
byte loveL_bmp[8] =
{ B01111000,
B10000100,
B10000010,
B01011001,
B01011001,
B10000010,
B10000100,
B01111000 };
byte loveR_bmp[8] =
{ B01111000,
B10000100,
B10000010,
B01011001,
B01011001,
B10000010,
B10000100,
B01111000 };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // set up LCD
  lcd.init();
  lcd.backlight();
  // set up LED
  for (int i=0; i< NUM_DEVICE; i++){
    ledmatrix.shutdown(i,false);
  // Set the brightness to a low value 
    ledmatrix.setIntensity(i,1);
  // and clear the display */
    ledmatrix.clearDisplay(i);
  }

  pan.attach(6); 
  tilt.attach(5);
  leftBrow.attach(4);
  rightBrow.attach(3);

  lcd.println("Hello!          ");
  lcd.println("I am Brobot    ");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.clear();

  pinMode(YELLOW_PIN, INPUT_PULLUP);
  pinMode(BLUE_PIN, INPUT_PULLUP);
  pinMode(BLACK_PIN, INPUT_PULLUP); 
  pinMode(RED_PIN, INPUT_PULLUP); 
  pinMode(GREEN_PIN, INPUT_PULLUP);
  pinMode(WHITE_PIN, INPUT_PULLUP);
  // set up ultrasonic sensor
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

}

void loop() {
  // put your main code here, to run repeatedly:
  // set up ultrasonic sensor signals
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // get and calculate distance
  pulse_width = pulseIn(echoPin, HIGH);
  distance = (pulse_width*0.0343)/2;
  int blackState = digitalRead(BLACK_PIN);
  int blueState = digitalRead(BLUE_PIN);
  Serial.println(blueState);
  int yellowState = digitalRead(YELLOW_PIN);
  int whiteState = digitalRead(WHITE_PIN);
  int greenState = digitalRead(GREEN_PIN);
  int redState = digitalRead(RED_PIN);
  // if-else statements determining emotion
  // each distance corresponds to an emotion and updateFace() and moveServos() are called to
  // express that emotion on the robot
   if(redState == LOW)
  {
    updateFace("ANGRY", angryL_bmp, angryR_bmp);
    moveServos(45, 135, 150, 100);
  }
  else if(greenState == LOW)
  {
    updateFace("SURPRISED       ", surprisedL_bmp, surprisedR_bmp);
    moveServos(100, 80, 170, 45);
  }
  else if(whiteState == LOW)
  {
    updateFace("LOVE            ", loveL_bmp, loveR_bmp);
    moveServos(115, 65, 170, 30);
  }
  else if(yellowState == LOW)
  {
    updateFace("HAPPY           ", happyL_bmp, happyR_bmp);
    moveServos(120, 60, 180, 60);
  }
  else if(blueState == LOW)
  {
    Serial.println("blue pressed");
    updateFace("SAD             ", sadL_bmp, sadR_bmp);
    moveServos(30, 150, 135, 120);
  }
  else if (blackState == LOW)
  {
    updateFace("NEUTRAL         ", neutralL_bmp, neutralR_bmp);
    moveServos(90, 90, 180, 90);
  }
  else
  {
      if(distance <= 10.0)
    {
      updateFace("ANGRY", angryL_bmp, angryR_bmp);
      moveServos(45, 135, 150, 100);
    }
    else if(distance <= 20.0)
    {
      updateFace("SURPRISED       ", surprisedL_bmp, surprisedR_bmp);
      moveServos(100, 80, 170, 45);
    }
    else if(distance <= 30.0)
    {
      updateFace("LOVE            ", loveL_bmp, loveR_bmp);
      moveServos(115, 65, 170, 30);
    }
    else if(distance <= 40.0)
    {
      updateFace("HAPPY           ", happyL_bmp, happyR_bmp);
      moveServos(120, 60, 180, 60);
    }
    else if(distance <= 50.0)
    {
      updateFace("SAD             ", sadL_bmp, sadR_bmp);
      moveServos(30, 150, 135, 120);
    }
    else
    {
      updateFace("NEUTRAL         ", neutralL_bmp, neutralR_bmp);
      moveServos(90, 90, 180, 90);
    }
  }
}

// takes in the emotion and the arrays for the eyes as parameters and uses them to change
// the LED matrices and LCD
void updateFace(String emotion, byte leftEye[], byte rightEye[])
{
  int i = 0;
  // draws pattern on left eye matrix
	for(i = 0; i < 8; i++)
	{
		ledmatrix.setColumn(0, i, leftEye[i]);
	}
	int j = 0;
  // draws pattern on right eye matrix
	for(j = 0; j < 8; j++)
	{
		ledmatrix.setColumn(1, j, rightEye[j]);
	}
  // displays emotion on LCD and resets cursor
  lcd.clear();
	lcd.print(emotion);
  lcd.setCursor(0, 0);
}

// takes in the angle measures that each servo turns as parameters and sets each servo to that angle
void moveServos(int left, int right, int panIn, int tiltIn)
{ 
  leftBrow.write(left);
  rightBrow.write(right);
  pan.write(panIn);
  tilt.write(tiltIn);

}
