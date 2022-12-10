#include <Servo.h>

#define OE_PIN      3 //Used for PWM signal to output enable pin
#define SER_PIN     2 //Used for serial signal, determine which servo motors to activate.
#define RCLK_PIN    1 //Used for sending data to storage.
#define SRCLK_PIN   0 //Used for shifting data into temp storage.
#define THUMB_PIN   5 //used for inverted thumb servo

Servo mainServo; //Create instance of servo class. Used for timing and easy servo control.
Servo thumbServo;

int AIN_PIN = A0; //Used for reading analog data.
int analogValue; //Value read from analog input
int analogValue2; //analog value for thumb.
byte shiftRegisterValue = B01111000; //first five outputs set to high, and last three set to 0. 

void setup() {
  pinMode(SER_PIN, OUTPUT);
  pinMode(RCLK_PIN, OUTPUT);
  pinMode(SRCLK_PIN, OUTPUT);
  mainServo.attach(OE_PIN);
  thumbServo.attach(THUMB_PIN);
  SetShiftRegister();
}

void loop() {
  // put your main code here, to run repeatedly:
  analogValue = analogRead(AIN_PIN);
  analogValue2 = analogRead(AIN_PIN);
  analogValue = map(analogValue, 0, 1023, 5, 175);
  analogValue2 = map(analogValue2, 0, 1023, 175, 5);
  mainServo.write(analogValue);
  thumbServo.write(analogValue2);
  delay(15);
}

void SetShiftRegister()
{
  digitalWrite(RCLK_PIN, LOW);
  shiftOut(SER_PIN, SRCLK_PIN, LSBFIRST, shiftRegisterValue);
  digitalWrite(RCLK_PIN, HIGH);
}
