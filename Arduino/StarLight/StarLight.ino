/*
  Ночник-звезда.

  Программа управления работой RGB-светильника.
  Подразумевается "ручное" управление потенциометрами по 3-м каналам
  либо автоматическое управление по заданному алгоритму.

  Контроллер - Arduino Nano

*/

const bool DEBUG = true;


#include "colors.h"

const byte RED_CONTROL_PIN   = A2;
const byte GREEN_CONTROL_PIN = A1;
const byte BLUE_CONTROL_PIN  = A0;
const byte MODE_PIN          = 2;

const bool AUTO   = true;
const bool MANUAL = false;

const byte RED_PIN   = 9;
const byte GREEN_PIN = 10;
const byte BLUE_PIN  = 11;

const byte COLORS_COUNT = 6;

int redRaw;
int greenRaw;
int blueRaw;

byte redValue;
byte greenValue;
byte blueValue;

bool mode;

unsigned long lastControl = 0;

int colorNum = 0;
int nextColorNum = 1;

int moment;


void setup() {
  pinMode(RED_PIN,   OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN,  OUTPUT);
  pinMode(MODE_PIN,  INPUT_PULLUP);

  if (DEBUG) {
    Serial.begin(115200);
    Serial.println("Start program");
    Serial.println();
  }
}


void loop() {
  redRaw   = analogRead(RED_CONTROL_PIN);
  greenRaw = analogRead(GREEN_CONTROL_PIN);
  blueRaw  = analogRead(BLUE_CONTROL_PIN);
  mode     = digitalRead(MODE_PIN);

  if (mode == MANUAL) {
    redValue   = map(redRaw,   0, 1023, 0, 255);
    greenValue = map(greenRaw, 0, 1023, 0, 255);
    blueValue  = map(blueRaw,  0, 1023, 0, 255);
    if (redValue==0 and greenValue==0 and blueValue==0) {
      redValue   = 1;
      greenValue = 1;
      blueValue  = 1;
    }

  } else {
    redRaw = 1023 - redRaw;
    if (millis() - lastControl > redRaw) {
      if (greenRaw < 512) {
        colorNum--;
        nextColorNum = colorNum - 1;
      } else {
        colorNum++;
        nextColorNum = colorNum + 1;
      }
      if (colorNum >= COLORS_COUNT) {
        colorNum = 0;
        nextColorNum = 1;
      }
      if (colorNum < 0) {
        colorNum = COLORS_COUNT - 1;
        nextColorNum = COLORS_COUNT - 2;
      }
      if (nextColorNum >= COLORS_COUNT) nextColorNum = 0;
      if (nextColorNum < 0) nextColorNum = COLORS_COUNT - 1;
      lastControl = millis();
    }

    moment = (millis() - lastControl);
    redValue   = map(moment, 0, redRaw, COLORS[colorNum][0], COLORS[nextColorNum][0]);
    greenValue = map(moment, 0, redRaw, COLORS[colorNum][1], COLORS[nextColorNum][1]);
    blueValue =  map(moment, 0, redRaw, COLORS[colorNum][2], COLORS[nextColorNum][2]);
  }

  analogWrite(RED_PIN,   redValue);
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN,  blueValue);

  if (DEBUG) {
    Serial.print("Red: ");   Serial.print(redRaw);   Serial.print('/'); Serial.print(redValue);   Serial.print('\t');
    Serial.print("Green: "); Serial.print(greenRaw); Serial.print('/'); Serial.print(greenValue); Serial.print('\t');
    Serial.print("Blue: ");  Serial.print(blueRaw);  Serial.print('/'); Serial.print(blueValue);  Serial.print('\t');
    Serial.print("Mode: ");  Serial.print(mode);     Serial.print('\t');
    Serial.print("Moment: "); Serial.print(moment); Serial.print('\t');
    Serial.print("Color num: "); Serial.print(colorNum); Serial.print("\t("); Serial.print(COLORS[colorNum][0]); Serial.print(","); Serial.print(COLORS[colorNum][1]); Serial.print(","); Serial.print(COLORS[colorNum][2]); Serial.print(")\t");
    Serial.print("Next color num: "); Serial.print(nextColorNum); Serial.print("\t("); Serial.print(COLORS[nextColorNum][0]); Serial.print(","); Serial.print(COLORS[nextColorNum][1]); Serial.print(","); Serial.print(COLORS[nextColorNum][2]); Serial.print(")\t");
    Serial.println();
  }
}
