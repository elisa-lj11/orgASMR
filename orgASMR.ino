// "orgASMR" Arduino code
// Created by Elisa Lupin-Jimenez

#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <Bounce.h>

const int FLEX_PIN = A0; // Flex sensor pin
const int KNOB_PIN = A1; // Potentiometer pin
const int BUTTON_PIN = 0; // Button pin

// LED pins
const int RED_PIN = 1;
const int GREEN_PIN = 2;
const int BLUE_PIN = 3;

// Accelerometer instantiation
Adafruit_MMA8451 mma = Adafruit_MMA8451();

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 47500.0; // Measured resistance of 3.3k resistor

int cnt = 1;

bool change = false;
bool lastGateState = false;
bool on = false;

void setup() 
{
  Serial.begin(9600);
  pinMode(FLEX_PIN, INPUT);
  pinMode(KNOB_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  mma.begin();
  mma.setRange(MMA8451_RANGE_2_G);
}

void loop() 
{
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC = analogRead(FLEX_PIN);  
  int fpCC = 8;
  int fpValue = flexADC*127/1024; // value between 0-127
  int uselessChannel = 0; // doesn't really matter

  int knobCC = 9;
  int dialValue = analogRead(KNOB_PIN);
  //int knobValue = (dialValue - 510) * 2 * 127 / 1024;//*127/1024;
  int knobValue = dialValue * 127 / 1024;

  mma.read();
  int mmaCC = mma.getOrientation();

  Serial.println(mma.getOrientation());

  int buttonCC = 10; 
  if (digitalRead(BUTTON_PIN)) { // button is pressed
    if (!on) change = true; // did the status of the button changed
    on = true;
  } else {
    if (on) change = true; // did the status of the button change?
    on = false;
  }

  if (change){ // if the status of the button changed
    if (on){ // if the button is pressed
      usbMIDI.sendControlChange(buttonCC,cnt,0);
      cnt = (cnt+1)%2;
    }
    change = false; // status changed
  }
  
  usbMIDI.sendControlChange(fpCC,fpValue,uselessChannel);
  usbMIDI.sendControlChange(knobCC,knobValue,uselessChannel);
  usbMIDI.sendControlChange(mmaCC,127,uselessChannel);

  for (int i = 0; i < 8; i++) {
    if (i != mmaCC)
      usbMIDI.sendControlChange(i, 0, uselessChannel);
  }

  delay(30);
}
