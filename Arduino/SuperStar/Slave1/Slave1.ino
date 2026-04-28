/*
  Ночник-суперзвезда.

  Программа управления работой RGB-светильника.
  Подразумевается управление любым светодиодом с помощью 
  клавиатуры и LCD дисплея в одном из режимов:
  ручной, автоматический или случайный.
  Предусмотрена возможность задания циклической программы.

  Прорабатывается возможность сохранения заданной программы после отключения питания.

  Контроллеры - Arduino Nano (Master)? + 2 * Arduino Mega 2560 Pro (Slaves)

  Slave1 I2C
*/

#include <Wire.h>
#include "constants.h"


byte programm[MAX_TICKS_COUNT][LEDS_PINS_COUNT][2];
byte tickChoise = 0;
byte pinNum = 0;


void setup() {
  if (DEBUG) {
    Serial.begin(9600);
    Serial.println();
    Serial.println("Super starlight slave 1 start");
  }
  Wire.begin(8);                // join i2c bus with address 8
  Wire.onReceive(receiveEvent); // register receive event
  Wire.onRequest(requestEvent); // register request event
  for (tickChoise=0; tickChoise<MAX_TICKS_COUNT; tickChoise++) {
    for (pinNum=0; pinNum<LEDS_PINS_COUNT; pinNum++) {
      programm[tickChoise][pinNum][0] = 0;
      programm[tickChoise][pinNum][1] = 0;
    }
  }
}


void loop() {
  delay(100);
}


// function that executes whenever data is received from master
void receiveEvent(int howMany) {
  if (DEBUG) Serial.print("The master gave me a command ");
  byte doing = 0;
  byte pin = 0;
  byte data = 0;
  while (2 < Wire.available()) {
    doing = Wire.read();
    pin = Wire.read();
    data = Wire.read();
  }
  if (DEBUG) {
    Serial.print(doing); Serial.print(", "); Serial.print(pin); Serial.print(", "); Serial.println(data);
  }
  switch (doing) {
    case CONFIGURE:
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
      delay(100);
      digitalWrite(pin, HIGH);
      break;
    case SET:
      analogWrite(pin, data);
      break;
    case WRITE_TICK:
      tickChoise = data;
      Serial.print("tickChoise = "); Serial.println(tickChoise);
      break;
    case WRITE_LED:
      programm[tickChoise][pinNum][0] = pin;
      programm[tickChoise][pinNum][1] = data;
      pinNum++;
      if (pinNum >= LEDS_PINS_COUNT) pinNum = 0;
      break;
    case TICK:
      for (pinNum=0; pinNum<LEDS_PINS_COUNT; pinNum++) analogWrite(programm[data][pinNum][0], 255-programm[data][pinNum][1]);
      break;
  }
}


// function that executes whenever data is requested from master
void requestEvent() {
  if (DEBUG) Serial.println("Master ask me");
  Wire.write("Hi Master");  // send string on request
}
