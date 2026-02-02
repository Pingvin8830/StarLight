/*
  Ночник-звезда.

  Программа управления работой RGB-светильника.
  Подразумевается "ручное" управление потенциометрами по 3-м каналам
  либо автоматическое управление по заданному алгоритму.

  Контроллер - Arduino Nano

*/

#include "colors.h"

const byte RED_PIN   = 11;
const byte GREEN_PIN = 10;
const byte BLUE_PIN  = 9;

const byte RED_CONTROL_PIN   = A0;
const byte GREEN_CONTROL_PIN = A1;
const byte BLUE_CONTROL_PIN  = A2;

const byte MODE_PIN = 2;

bool isManualMode = false; // Режим работы. 0 - авто, 1 - ручной

int redLevel   = 0;
int greenLevel = 0;
int blueLevel  = 0;

unsigned long lastControl;

byte autoStep = 0;
int speed = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN,   OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN,  OUTPUT);
  pinMode(MODE_PIN,  INPUT_PULLUP);

  digitalWrite(RED_PIN,   HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN,  HIGH);

  lastControl = millis();
}


void loop() {
  // put your main code here, to run repeatedly:
  isManualMode = digitalRead(MODE_PIN);
  if (isManualMode) {
    analogWrite(RED_PIN,   analogRead(RED_CONTROL_PIN));
    analogWrite(GREEN_PIN, analogRead(GREEN_CONTROL_PIN));
    analogWrite(BLUE_PIN,  analogRead(BLUE_CONTROL_PIN));
    autoStep = 0;
    lastControl = millis();
  } else {
    speed = 1023 - analogRead(RED_CONTROL_PIN);
    if (millis() - lastControl > speed) {
      autoStep++;
      lastControl = millis();
    }
    if (autoStep > 23) autoStep = 0;
    analogWrite(RED_PIN,   255 - COLORS[autoStep][0]);
    analogWrite(GREEN_PIN, 255 - COLORS[autoStep][1]);
    analogWrite(BLUE_PIN,  255 - COLORS[autoStep][2]);
  }
}
