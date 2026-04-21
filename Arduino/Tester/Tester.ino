
// Test Poterntiometrs
const byte RED_CONTROL_PIN   = A2;
const byte GREEN_CONTROL_PIN = A1;
const byte BLUE_CONTROL_PIN  = A0;


int redRaw;
int greenRaw;
int blueRaw;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Start tester");
  Serial.println();
}


void loop() {
  // put your main code here, to run repeatedly:
  redRaw   = analogRead(RED_CONTROL_PIN);
  greenRaw = analogRead(GREEN_CONTROL_PIN);
  blueRaw  = analogRead(BLUE_CONTROL_PIN);

  Serial.print("RedRaw: "); Serial.print(redRaw); Serial.print("\t"); Serial.print("GreenRaw: "); Serial.print(greenRaw); Serial.print("\t");Serial.print("BlueRaw: "); Serial.print(blueRaw); Serial.print("\t");
  Serial.println();
}

/*
// Test RGB
const byte RED_PIN   = 11;
const byte GREEN_PIN = 10;
const byte BLUE_PIN  = 9;

int redLevel   = 0;
int greenLevel = 0;
int blueLevel  = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN,   OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN,  OUTPUT);

  digitalWrite(RED_PIN,   HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN,  HIGH);
}


void loop() {
  // put your main code here, to run repeatedly:
  redLevel = 0;                       greenLevel = 0;                         blueLevel = 0;
  analogWrite(RED_PIN, 255-redLevel); analogWrite(GREEN_PIN, 255-greenLevel); analogWrite(BLUE_PIN, 255-blueLevel);
  delay(1000);

  redLevel = 255;                     greenLevel = 0;                         blueLevel = 0;
  analogWrite(RED_PIN, 255-redLevel); analogWrite(GREEN_PIN, 255-greenLevel); analogWrite(BLUE_PIN, 255-blueLevel);
  delay(1000);

  redLevel = 0;                       greenLevel = 0;                         blueLevel = 0;
  analogWrite(RED_PIN, 255-redLevel); analogWrite(GREEN_PIN, 255-greenLevel); analogWrite(BLUE_PIN, 255-blueLevel);
  delay(1000);

  redLevel = 0;                       greenLevel = 255;                       blueLevel = 0;
  analogWrite(RED_PIN, 255-redLevel); analogWrite(GREEN_PIN, 255-greenLevel); analogWrite(BLUE_PIN, 255-blueLevel);
  delay(1000);

  redLevel = 0;                       greenLevel = 0;                         blueLevel = 0;
  analogWrite(RED_PIN, 255-redLevel); analogWrite(GREEN_PIN, 255-greenLevel); analogWrite(BLUE_PIN, 255-blueLevel);
  delay(1000);

  redLevel = 0;                       greenLevel = 0;                         blueLevel = 255;
  analogWrite(RED_PIN, 255-redLevel); analogWrite(GREEN_PIN, 255-greenLevel); analogWrite(BLUE_PIN, 255-blueLevel);
  delay(1000);

  redLevel = 0;                       greenLevel = 0;                         blueLevel = 0;
  analogWrite(RED_PIN, 255-redLevel); analogWrite(GREEN_PIN, 255-greenLevel); analogWrite(BLUE_PIN, 255-blueLevel);
  delay(1000);

  for (int i=0; i<255; i++) {
    analogWrite(RED_PIN, 255-i);
    delay(5);
  }
  for (int i=255; i>0; i--) {
    analogWrite(RED_PIN, 255-i);
    delay(5);
  }

  for (int i=0; i<255; i++) {
    analogWrite(GREEN_PIN, 255-i);
    delay(5);
  }
  for (int i=255; i>0; i--) {
    analogWrite(GREEN_PIN, 255-i);
    delay(5);
  }

  for (int i=0; i<255; i++) {
    analogWrite(BLUE_PIN, 255-i);
    delay(5);
  }
  for (int i=255; i>0; i--) {
    analogWrite(BLUE_PIN, 255-i);
    delay(5);
  }
}
*/
/*
// Test RGB with Transistors keys
const byte RED_PIN   = 9;
const byte GREEN_PIN = 10;
const byte BLUE_PIN  = 11;

int redLevel   = 0;
int greenLevel = 0;
int blueLevel  = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN,   OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN,  OUTPUT);

  digitalWrite(RED_PIN,   HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN,  HIGH);
}


void loop() {
  // put your main code here, to run repeatedly:
  redLevel = 0;                   greenLevel = 0;                     blueLevel = 0;
  analogWrite(RED_PIN, redLevel); analogWrite(GREEN_PIN, greenLevel); analogWrite(BLUE_PIN, blueLevel);
  delay(1000);

  redLevel = 255;                 greenLevel = 0;                     blueLevel = 0;
  analogWrite(RED_PIN, redLevel); analogWrite(GREEN_PIN, greenLevel); analogWrite(BLUE_PIN, blueLevel);
  delay(1000);

  redLevel = 0;                   greenLevel = 0;                     blueLevel = 0;
  analogWrite(RED_PIN, redLevel); analogWrite(GREEN_PIN, greenLevel); analogWrite(BLUE_PIN, blueLevel);
  delay(1000);

  redLevel = 0;                   greenLevel = 255;                   blueLevel = 0;
  analogWrite(RED_PIN, redLevel); analogWrite(GREEN_PIN, greenLevel); analogWrite(BLUE_PIN, blueLevel);
  delay(1000);

  redLevel = 0;                   greenLevel = 0;                     blueLevel = 0;
  analogWrite(RED_PIN, redLevel); analogWrite(GREEN_PIN, greenLevel); analogWrite(BLUE_PIN, blueLevel);
  delay(1000);

  redLevel = 0;                   greenLevel = 0;                     blueLevel = 255;
  analogWrite(RED_PIN, redLevel); analogWrite(GREEN_PIN, greenLevel); analogWrite(BLUE_PIN, blueLevel);
  delay(1000);

  redLevel = 0;                   greenLevel = 0;                     blueLevel = 0;
  analogWrite(RED_PIN, redLevel); analogWrite(GREEN_PIN, greenLevel); analogWrite(BLUE_PIN, blueLevel);
  delay(1000);

  for (int i=0; i<=255; i++) {
    analogWrite(RED_PIN, i);
    delay(5);
  }
  for (int i=255; i>=0; i--) {
    analogWrite(RED_PIN, i);
    delay(5);
  }

  for (int i=0; i<=255; i++) {
    analogWrite(GREEN_PIN, i);
    delay(5);
  }
  for (int i=255; i>=0; i--) {
    analogWrite(GREEN_PIN, i);
    delay(5);
  }

  for (int i=0; i<=255; i++) {
    analogWrite(BLUE_PIN, i);
    delay(5);
  }
  for (int i=255; i>=0; i--) {
    analogWrite(BLUE_PIN, i);
    delay(5);
  }
}
*/

/*
  Ночник-звезда.

  Программа управления работой RGB-светильника.
  Подразумевается "ручное" управление потенциометрами по 3-м каналам
  либо автоматическое управление по заданному алгоритму.

  Контроллер - Arduino Nano

*/
/*
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
    redLevel = map(analogRead(RED_CONTROL_PIN), 0, 1023, 0, 255);
    greenLevel = map(analogRead(GREEN_CONTROL_PIN), 0, 1023, 0, 255);
    blueLevel = map(analogRead(BLUE_CONTROL_PIN), 0, 1023, 0, 255);
    analogWrite(RED_PIN,   redLevel);
    analogWrite(GREEN_PIN, greenLevel);
    analogWrite(BLUE_PIN,  blueLevel);
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
*/


/*
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
    redLevel = map(analogRead(RED_CONTROL_PIN), 0, 1023, 0, 255);
    greenLevel = map(analogRead(GREEN_CONTROL_PIN), 0, 1023, 0, 255);
    blueLevel = map(analogRead(BLUE_CONTROL_PIN), 0, 1023, 0, 255);
    analogWrite(RED_PIN,   redLevel);
    analogWrite(GREEN_PIN, greenLevel);
    analogWrite(BLUE_PIN,  blueLevel);
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
*/