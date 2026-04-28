/*
  Ночник-суперзвезда.

  Программа управления работой RGB-светильника.
  Подразумевается управление любым светодиодом с помощью 
  клавиатуры и LCD дисплея в одном из режимов:
  ручной, автоматический или случайный.
  Предусмотрена возможность задания циклической программы.

  Прорабатывается возможность сохранения заданной программы после отключения питания.

  Контроллеры - Arduino Nano (Master)? + 2 * Arduino Mega 2560 Pro (Slaves)

  Master I2C
*/

#include <LiquidCrystal_I2C.h>
#include "constants.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Slaves addresses
//const byte SLAVES[2] = {0x8, 0x9};
//const byte SLAVES[3] = {0, 0x8, 0x8};
const byte SLAVES[2] = {0, 0x8};

/*const byte LEDS[LEDS_COUNT][4] = {
  // Red pin, Green pin, Blue pin, I2C address
  { 3,  5,  6, 0},
  { 9, 10, 11, 0},
  { 2,  3,  4, SLAVES[0]},
  { 5,  6,  7, SLAVES[0]},
  { 8,  9, 10, SLAVES[0]},
  {11, 12, 13, SLAVES[0]},
  {44, 45, 46, SLAVES[0]},
  { 2,  3,  4, SLAVES[1]},
  { 5,  6,  7, SLAVES[1]},
  { 8,  9, 10, SLAVES[1]},
  {11, 12, 13, SLAVES[1]},
  {44, 45, 46, SLAVES[1]}
};*/
/*const byte LEDS[LEDS_COUNT][4] = {
  // Red pin, Green pin, Blue pin, I2C address
  {3,  5,  6, 0},
  {9, 10, 11, 0},
  {3,  5,  6, SLAVES[1]},
  {9, 10, 11, SLAVES[1]}
};*/
const byte LEDS[LEDS_COUNT][4] = {
  // Red pin, Green pin, Blue pin, I2C address
  {3,  5,  6, SLAVES[0]},
  {3,  5,  6, SLAVES[1]},
};


byte cursor[3] = {0, 1, (byte)'>'};
byte ledChoise = 0;
byte ledsActual[LEDS_COUNT][3];
byte ledsPrepare[LEDS_COUNT][3];
byte state = 0;
bool isApply = true;
/*byte programm[MAX_TICKS_COUNT][LEDS_COUNT][3] = {
  {
    {255,   0,   0},
    {128, 127,   0},
    {  0, 255,   0},
    {  0, 128, 127},
  },
  {
    {128, 127,   0},
    {  0, 255,   0},
    {  0, 128, 127},
    {  0,   0, 255},
  },
  {
    {  0, 255,   0},
    {  0, 128, 127},
    {  0,   0, 255},
    {127,   0, 128},
  },
  {
    {  0, 128, 127},
    {  0,   0, 255},
    {127,   0, 128},
    {255,   0,   0},
  },
  {
    {  0,   0, 255},
    {127,   0, 128},
    {255,   0,   0},
    {128, 127,   0},
  },
  {
    {127,   0, 128},
    {255,   0,   0},
    {128, 127,   0},
    {  0, 255,   0},
  },
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  }
};*/
/*byte programm[MAX_TICKS_COUNT][LEDS_COUNT][3] = {
  {
    {  0,   0,   0},
    {  0,   0,   0},
    {  0,   0,   0},
    {  0,   0,   0},
  },
  {
    {255,   0,   0},
    {255,   0,   0},
    {255,   0,   0},
    {255,   0,   0},
  },
  {
    {  0, 255,   0},
    {  0, 255,   0},
    {  0, 255,   0},
    {  0, 255,   0},
  },
  {
    {  0,   0, 255},
    {  0,   0, 255},
    {  0,   0, 255},
    {  0,   0, 255},
  },
  {
    {255, 255,   0},
    {128, 255, 127},
    {  0, 255, 255},
    {127, 128, 255},
  },
  {
    {128, 255, 127},
    {  0, 255, 255},
    {127, 128, 255},
    {255,   0, 255},
  },
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  }
};*/
byte programm[MAX_TICKS_COUNT][LEDS_COUNT][3] = {
  {
    {  0,   0,   0},
    {  0,   0,   0},
  },
  {
    {255,   0,   0},
    {255,   0,   0},
  },
  {
    {  0, 255,   0},
    {  0, 255,   0},
  },
  {
    {  0,   0, 255},
    {  0,   0, 255},
  },
  {
    {  0, 255, 255},
    {127, 128, 255},
  },
  {
    {127, 128, 255},
    {255,   0, 255},
  },
  {
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0}
  }
};
byte ticksCount = 4;
int ticksDuration = 1000;
byte tickChoise = 0;
byte mode = 0;
bool displayLight = true;
int lastChange = 0;
int control = 0;


void setup() {
  randomSeed(analogRead(0));
  if (DEBUG) {
    Serial.begin(9600);
    Serial.println();
    Serial.println("Super starlight master start");
  }
  initLCD();
  initSlaves();
  initLEDs();
  if (TRAINING) {
    Serial.setTimeout(10);
  }
  printMenu();
}


void loop() {
  byte doing = getDoing();
  applyDoing(doing);
  if (state == 0) {
    switch (mode) {
      case 1: // Auto
        control = millis();
        if (control > lastChange+ticksDuration) {
          tickChoise++;
          if (tickChoise >= ticksCount) tickChoise = 0;
          for (byte slaveNum=0; slaveNum<sizeof(SLAVES)/sizeof(SLAVES[0]); slaveNum++) sendCommand(SLAVES[slaveNum], TICK, 0, tickChoise);
          lastChange = control;
        }
        break;
      case 2: // Random
        control = millis();
        if (control > lastChange+ticksDuration) {
          byte ledNum = random(LEDS_COUNT);
          sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][0], (byte)random(255));
          ledNum = random(LEDS_COUNT);
          sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][1], (byte)random(255));
          ledNum = random(LEDS_COUNT);
          sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][2], (byte)random(255));
          ticksDuration = random(MAX_TICKS_DURATION);
          lastChange = control;
        }
        break;
    }
  }
}


void initLCD() {
  if (DEBUG) Serial.println("Init LCD");
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("   SuperStarLight   ");
  lcd.setCursor(0, 2); lcd.print("Initialization...   ");
}


void initSlaves() {
  if (DEBUG) Serial.println("Init slaves");
  lcd.setCursor(0, 3); lcd.print("Init slaves...");
  for (byte i=1; i<(sizeof(SLAVES)/sizeof(SLAVES[0])); i++) {
    while (!isSlaveReady(SLAVES[i])) {
      if (DEBUG) {
        Serial.print("Slave "); Serial.print(i); Serial.print("("); Serial.print(SLAVES[i]); Serial.println(") not found");
      }
      lcd.setCursor(14, 3); lcd.print(i); lcd.print(" ("); lcd.print(SLAVES[i]); lcd.print(')');
      delay(1000);
    }
  }
  lcd.setCursor(0, 2); lcd.print("Sync slaves...      ");
  lcd.setCursor(0, 3); lcd.print("T.. A. L.. Clr......");
  for (byte tick=0; tick<ticksCount; tick++) {
    lcd.setCursor(1, 3);
    if (tick<10) lcd.print('.'); lcd.print(tick);
    for (byte slaveNum=1; slaveNum<sizeof(SLAVES)/sizeof(SLAVES[0]); slaveNum++) sendCommand(SLAVES[slaveNum], WRITE_TICK, 0, tick);
    for (byte ledNum=0; ledNum<LEDS_COUNT; ledNum++) {
      lcd.setCursor(5, 3); lcd.print(LEDS[ledNum][3]);
      lcd.setCursor(8, 3);
      if (ledNum < 10) lcd.print('.'); lcd.print(ledNum);
      lcd.setCursor(14, 3);
      if (programm[tick][ledNum][0] < 17) lcd.print('0'); lcd.print(programm[tick][ledNum][0], HEX);
      if (programm[tick][ledNum][1] < 17) lcd.print('0'); lcd.print(programm[tick][ledNum][1], HEX);
      if (programm[tick][ledNum][2] < 17) lcd.print('0'); lcd.print(programm[tick][ledNum][2], HEX);
      sendCommand(LEDS[ledNum][3], WRITE_LED, LEDS[ledNum][0], programm[tick][ledNum][0]);
      sendCommand(LEDS[ledNum][3], WRITE_LED, LEDS[ledNum][1], programm[tick][ledNum][1]);
      sendCommand(LEDS[ledNum][3], WRITE_LED, LEDS[ledNum][2], programm[tick][ledNum][2]);
    }
  }
  lcd.setCursor(14, 3); lcd.print("Ok    ");
  if (DEBUG) Serial.println("Slaves ok");
}


void initLEDs() {
  if (DEBUG) Serial.println("Init leds");
  lcd.setCursor(0, 3); lcd.print("Init leds...");
  for (byte ledNum=0; ledNum<LEDS_COUNT; ledNum++) {
    byte address = LEDS[ledNum][3];
    if (DEBUG) {
      Serial.print("Address: "); Serial.println(address);
    }
    lcd.setCursor(12, 3); lcd.print(address); lcd.print(" (");
    if (TRAINING) {
      sendCommand(address, CONFIGURE, 4, 0);
      sendCommand(address, SET, 4, 0);
    }
    for (byte ledPinNum=0; ledPinNum<3; ledPinNum++) {
      ledsActual[ledNum][ledPinNum] = 0;
      ledsPrepare[ledNum][ledPinNum] = 0;
      byte pin = LEDS[ledNum][ledPinNum];
      if (DEBUG) {
        Serial.print("Pin: "); Serial.print(pin); Serial.print("\t(");
      }
      lcd.setCursor(15, 3); lcd.print(pin); lcd.print(')');
      lcd.setCursor(19, 3);
      if (address == 0) {
        if (DEBUG) Serial.println("Local)");
        lcd.print('L');
      } else {
        if (DEBUG) Serial.println("Distant)");
        lcd.print('D');
      }
      sendCommand(address, CONFIGURE, pin, 0);
    }
  }
}


bool isSlaveReady(int address) {
  bool result = false;
  Wire.requestFrom(address, 1);
  while (Wire.available()) {
    byte response = Wire.read();
    result = true;
  }
  return result;
}


void sendCommand(byte address, byte command, byte pin, byte data) {
  if (command == SET) data = 255 - data;
  if (address == 0) applyCommand(command, pin, data);
  else {
    Wire.beginTransmission(address);
    Wire.write(command);
    Wire.write(pin);
    Wire.write(data);
    Wire.endTransmission();
  }
}


void applyCommand(byte doing, byte pin, byte data) {
  if (DEBUG) {
    Serial.print("Apply command "); Serial.print(doing); Serial.print(", "); Serial.print(pin); Serial.print(", "); Serial.println(data);
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
    case TICK:
      for (byte ledNum=0; ledNum<LEDS_COUNT; ledNum++) {
        if (LEDS[ledNum][3] == 0) {
          analogWrite(LEDS[ledNum][0], 255-programm[data][ledNum][0]);
          analogWrite(LEDS[ledNum][1], 255-programm[data][ledNum][1]);
          analogWrite(LEDS[ledNum][2], 255-programm[data][ledNum][2]);
        }
      }
      break;
  }
}


void printMenu() {
  switch (state) {
    case 0: // Main
      lcd.setCursor(0, 0); lcd.print("   SuperStarLight   ");
      lcd.setCursor(0, 1); lcd.print(" 1. Set colors      ");
      lcd.setCursor(0, 2); lcd.print(" 2. Set program     ");
      lcd.setCursor(0, 3); lcd.print(" 3. Settings        ");
      break;
    case 1: // Set colors
      lcd.setCursor(0, 1); lcd.print("     Set colors     ");
      lcd.setCursor(0, 2); lcd.print("Led:"); lcd.print(ledChoise, HEX);
      lcd.print("R:"); printByte(7, 2, ledsPrepare[ledChoise][0]);
      lcd.print("G:"); printByte(12, 2, ledsPrepare[ledChoise][1]);
      lcd.print("B:"); printByte(17, 2, ledsPrepare[ledChoise][2]);
      lcd.setCursor(0, 3); lcd.print("                    ");
      break;
    case 2: // Set program, set count ticks
      lcd.setCursor(0, 1); lcd.print("  Set program ticks ");
      lcd.setCursor(0, 2); lcd.print("Cnt:");
      if (ticksCount < 10) lcd.print('.'); lcd.print(ticksCount);
      lcd.print(" Duration:");
      if (ticksDuration < 1000) lcd.print('.');
      if (ticksDuration <  100) lcd.print('.');
      if (ticksDuration <   10) lcd.print('.');
      lcd.print(ticksDuration);
      lcd.setCursor(0, 3); lcd.print("                    ");
      break;
    case 21: // Set program, set 
      lcd.setCursor(0, 1); lcd.print("     Set program    ");
      lcd.setCursor(0, 2); lcd.print("Led:"); lcd.print(ledChoise, HEX);
      lcd.print("R:"); printByte(7, 2, programm[tickChoise][ledChoise][0]);
      lcd.print("G:"); printByte(12, 2, programm[tickChoise][ledChoise][1]);
      lcd.print("B:"); printByte(17, 2, programm[tickChoise][ledChoise][2]);
      lcd.setCursor(0, 3); lcd.print('T');
      if (tickChoise < 10) lcd.print('.'); lcd.print(tickChoise);
      lcd.print("                 ");
      break;
    case 3: // Settings
      lcd.setCursor(0, 1); lcd.print("      Settings      ");
      lcd.setCursor(0, 2); lcd.print("Display light Mode  ");
      lcd.setCursor(0, 3);
      if (displayLight) lcd.print("  On");
      else lcd.print(" Off");
      lcd.print("          ");
      switch (mode) {
        case 0:
          lcd.print("Manual");
          break;
        case 1:
          lcd.print("Auto  ");
          break;
        case 2:
          lcd.print("Random");
          break;
      }
      break;
  }
  lcd.setCursor(cursor[0], cursor[1]); lcd.write(cursor[2]);
}


void updateCursor(byte column, byte line, char symbol) {
  cursor[0] = column;
  cursor[1] = line;
  cursor[2] = (byte)symbol;
}


byte getDoing() {
  if (TRAINING && Serial.available()) {
    /*
      Codes:
      1 - Cancel/reset
      2 - Down
      3 - Enter
      4 - Left
      6 - Right
      8 - Up
    */
    byte doing = Serial.parseInt();
    doing = constrain(doing, 0, 255);
    Serial.print("Doing: "); Serial.print(doing); Serial.print(" ("); Serial.print((byte)doing); Serial.println(')');
    while (Serial.available()) Serial.read();
    return doing;
  }
}


void applyDoing(byte doing) {
  switch (state) {
    case 0: // Main menu
      switch (doing) {
        case 3: // Enter
          switch (cursor[1]) {
            case 1: // Cursor indicate menu "Set color"
              state = 1;
              updateCursor(4, 3, '^');
              break;
            case 2: // Cursor indicate menu "Set program"
              state = 2;
              updateCursor(5, 3, '^');
              break;
            case 3: // Cursor indicate menu "Settings"
              state = 3;
              break;
          }
          printMenu();
          break;
        case 2: // Down
        case 8: // Up
          moveCursor(doing, 1);
          break;
      }
      break;
    case 1: // Menu "Set color"
      switch (doing) {
        case 1: // Cancel/reset
          if (isApply) {
            for (byte ledNum=0; ledNum<LEDS_COUNT; ledNum++) {
              sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][0], ledsActual[ledNum][0]);
              sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][1], ledsActual[ledNum][1]);
              sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][2], ledsActual[ledNum][2]);
            }
            state = 0;
            updateCursor(0, 1, '>');
            printMenu();
          } else {
            ledsPrepare[ledChoise][0] = ledsActual[ledChoise][0];
            ledsPrepare[ledChoise][1] = ledsActual[ledChoise][1];
            ledsPrepare[ledChoise][2] = ledsActual[ledChoise][2];
            printByte(7, 2, ledsPrepare[ledChoise][0]);
            printByte(12, 2, ledsPrepare[ledChoise][1]);
            printByte(17, 2, ledsPrepare[ledChoise][2]);
          }
          break;
        case 3: // Enter
          if (isApply) {
            for (byte ledNum=0; ledNum<LEDS_COUNT; ledNum++) {
              sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][0], ledsActual[ledNum][0]);
              sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][1], ledsActual[ledNum][1]);
              sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][2], ledsActual[ledNum][2]);
            }
            state = 0;
            updateCursor(0, 1, '>');
            printMenu();
          } else {
            for (byte ledNum=0; ledNum<LEDS_COUNT; ledNum++) {
              ledsActual[ledNum][0] = ledsPrepare[ledNum][0];
              ledsActual[ledNum][1] = ledsPrepare[ledNum][1];
              ledsActual[ledNum][2] = ledsPrepare[ledNum][2];
            }
            lcd.setCursor(0, 3); lcd.print("  ");
            isApply = true;
          }
          break;
        case 4: // Left
        case 6: // Right
          moveCursor(doing, 5);
          break;
        case 2: // Down
          switch (cursor[0]) {
            case 4: // Cursor indicate choise led
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][0], ledsPrepare[ledChoise][0]);
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][1], ledsPrepare[ledChoise][1]);
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][2], ledsPrepare[ledChoise][2]);
              ledChoise--;
              if (ledChoise >= LEDS_COUNT) ledChoise = LEDS_COUNT - 1;
              lcd.setCursor(4, 2); lcd.print(ledChoise, HEX);
              printByte( 7, 2, ledsPrepare[ledChoise][0]);
              printByte(12, 2, ledsPrepare[ledChoise][1]);
              printByte(17, 2, ledsPrepare[ledChoise][2]);
              break;
            case 9: // Cursor indicate choise red level
              isApply = false;
              lcd.setCursor(0, 3); lcd.print("NA");
              ledsPrepare[ledChoise][0]--;
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][0], ledsPrepare[ledChoise][0]);
              printByte(7, 2, ledsPrepare[ledChoise][0]);
              break;
            case 14: // Cursor indicate choise green level
              isApply = false;
              lcd.setCursor(0, 3); lcd.print("NA");
              ledsPrepare[ledChoise][1]--;
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][1], ledsPrepare[ledChoise][1]);
              printByte(12, 2, ledsPrepare[ledChoise][1]);
              break;
            case 19: // Cursor indicate choise blue level
              isApply = false;
              lcd.setCursor(0, 3); lcd.print("NA");
              ledsPrepare[ledChoise][2]--;
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][2], ledsPrepare[ledChoise][2]);
              printByte(17, 2, ledsPrepare[ledChoise][2]);
              break;
          }
          break;
        case 8: // Up
          switch (cursor[0]) {
            case 4: // Cursor indicate choise led
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][0], ledsPrepare[ledChoise][0]);
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][1], ledsPrepare[ledChoise][1]);
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][2], ledsPrepare[ledChoise][2]);
              ledChoise++;
              if (ledChoise >= LEDS_COUNT) ledChoise = 0;
              lcd.setCursor(4, 2); lcd.print(ledChoise, HEX);
              printByte(7, 2, ledsPrepare[ledChoise][0]);
              printByte(12, 2, ledsPrepare[ledChoise][1]);
              printByte(17, 2, ledsPrepare[ledChoise][2]);
              break;
            case 9: // Cursor indicate choise red level
              isApply = false;
              lcd.setCursor(0, 3); lcd.print("NA");
              ledsPrepare[ledChoise][0]++;
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][0], ledsPrepare[ledChoise][0]);
              printByte(7, 2, ledsPrepare[ledChoise][0]);
              break;
            case 14: // Cursor indicate choise green level
              isApply = false;
              lcd.setCursor(0, 3); lcd.print("NA");
              ledsPrepare[ledChoise][1]++;
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][1], ledsPrepare[ledChoise][1]);
              printByte(12, 2, ledsPrepare[ledChoise][1]);
              break;
            case 19: // Cursor indicate choise blue level
              isApply = false;
              lcd.setCursor(0, 3); lcd.print("NA");
              ledsPrepare[ledChoise][2]++;
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][2], ledsPrepare[ledChoise][2]);
              printByte(17, 2, ledsPrepare[ledChoise][2]);
              break;
          }
        default: // Nothing to choise do
          if (millis() % 1000 < 800) {
            sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][0], ledsPrepare[ledChoise][0]);
            sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][1], ledsPrepare[ledChoise][1]);
            sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][2], ledsPrepare[ledChoise][2]);
          } else {
            sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][0], 0);
            sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][1], 0);
            sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][2], 0);
          }
      }
      break;
    case 2: // Menu "Set program", set ticks params
      switch (doing) {
        case 1: // Cancel
          state = 0;
          updateCursor(0, 2, '>');
          printMenu();
          break;
        case 3: // Enter
          state = 21;
          tickChoise = 0;
          ledChoise = 0;
          updateCursor(4, 3, '^');
          printMenu();
          for (byte ledNum=0; ledNum<LEDS_COUNT; ledNum++) {
            sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][0], programm[tickChoise][ledNum][0]);
            sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][1], programm[tickChoise][ledNum][1]);
            sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][2], programm[tickChoise][ledNum][2]);
          }
          break;
        case 8: // Up
          switch (cursor[0]) {
            case 5: // Cursor indicate count ticks
              ticksCount++;
              if (ticksCount > MAX_TICKS_COUNT) ticksCount = MAX_TICKS_COUNT;
              lcd.setCursor(4, 2);
              if (ticksCount < 10) lcd.print('.'); lcd.print(ticksCount);
              break;
            case 19: // cursor indicate duration ticks
              ticksDuration += 10;
              if (ticksDuration > MAX_TICKS_DURATION) ticksDuration = MAX_TICKS_DURATION;
              lcd.setCursor(16, 2);
              if (ticksDuration < 1000) lcd.print('.');
              if (ticksDuration <  100) lcd.print('.');
              if (ticksDuration <   10) lcd.print('.');
              lcd.print(ticksDuration);
              break;
          }
          break;
        case 2: // Down
          switch (cursor[0]) {
            case 5: // Cursot indicate count ticks
              ticksCount--;
              if (ticksCount < 1) ticksCount = 1;
              lcd.setCursor(4, 2);
              if (ticksCount < 10) lcd.print('.'); lcd.print(ticksCount);
              break;
            case 19: // CUrsor indicate duration ticks
              ticksDuration -= 10;
              if (ticksDuration < 10) ticksDuration = 10;
              lcd.setCursor(16, 2);
              if (ticksDuration < 1000) lcd.print('.');
              if (ticksDuration <  100) lcd.print('.');
              if (ticksDuration <   10) lcd.print('.');
              lcd.print(ticksDuration);
              break;
          }
          break;
        case 4: // Left
          if (cursor[0] == 19) moveCursor(doing, 14);
          break;
        case 6: // Right
          if (cursor[0] == 5) moveCursor(doing, 14);
          break;
      }
      break;
    case 21: // Menu "Set program". Set leds params
      switch (doing) {
        case 1: // Cancel/reset
          state = 2;
          for (byte ledNum=0; ledNum<LEDS_COUNT; ledNum++) {
            sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][0], ledsActual[ledNum][0]);
            sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][1], ledsActual[ledNum][1]);
            sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][2], ledsActual[ledNum][2]);
          }
          updateCursor(5, 3, '^');
          printMenu();
          break;
        case 3: // Enter
          lcd.setCursor(0, 2); lcd.print("Sync slaves...      ");
          lcd.setCursor(0, 3); lcd.print("T.. A. L.. Clr......");
          for (byte tick=0; tick<ticksCount; tick++) {
            lcd.setCursor(1, 3);
            if (tick<10) lcd.print('.'); lcd.print(tick);
            for (byte slaveNum=1; slaveNum<sizeof(SLAVES)/sizeof(SLAVES[0]); slaveNum++) sendCommand(SLAVES[slaveNum], WRITE_TICK, 0, tick);
            for (byte ledNum=0; ledNum<LEDS_COUNT; ledNum++) {
              lcd.setCursor(5, 3); lcd.print(LEDS[ledNum][3]);
              lcd.setCursor(8, 3);
              if (ledNum < 10) lcd.print('.'); lcd.print(ledNum);
              lcd.setCursor(14, 3);
              if (programm[tick][ledNum][0] < 17) lcd.print('0'); lcd.print(programm[tick][ledNum][0], HEX);
              if (programm[tick][ledNum][1] < 17) lcd.print('0'); lcd.print(programm[tick][ledNum][1], HEX);
              if (programm[tick][ledNum][2] < 17) lcd.print('0'); lcd.print(programm[tick][ledNum][2], HEX);
              sendCommand(LEDS[ledNum][3], WRITE_LED, LEDS[ledNum][0], programm[tick][ledNum][0]);
              sendCommand(LEDS[ledNum][3], WRITE_LED, LEDS[ledNum][1], programm[tick][ledNum][1]);
              sendCommand(LEDS[ledNum][3], WRITE_LED, LEDS[ledNum][2], programm[tick][ledNum][2]);
            }
          }
          state = 0;
          updateCursor(0, 2, '>');
          printMenu();
          for (byte ledNum=0; ledNum<LEDS_COUNT; ledNum++) {
            sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][0], ledsActual[ledNum][0]);
            sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][1], ledsActual[ledNum][1]);
            sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][2], ledsActual[ledNum][2]);
          }
          break;
        case 4: // Left
          switch (cursor[0]) {
            case 3:
              break;
            case 4: // Cursor indicate Led
              updateCursor(4, 3, '<');
              moveCursor(doing, 1);
              break;
            default: // Cursor indicate color
              moveCursor(doing, 5);
              break;
          }
          break;
        case 6: // Right
          switch (cursor[0]) {
            case 3: // Cursor indicate tick
              updateCursor(3, 3, '^');
              moveCursor(doing, 1);
              break;
            case 19: // Cursor indicate blue color
              break;
            default: // Cursor indicate Led, red or green colors
              moveCursor(doing, 5);
              break;
          }
          break;
        case 8: // Up
          switch (cursor[0]) {
            case 3: // Cursor indicate tick
              tickChoise++;
              ledChoise = 0;
              if (tickChoise >= ticksCount) tickChoise = ticksCount - 1;
              lcd.setCursor(1, 3);
              if (tickChoise < 10) lcd.print('.'); lcd.print(tickChoise);
              lcd.setCursor(4, 2); lcd.print(ledChoise, HEX);
              printByte(7, 2, programm[tickChoise][ledChoise][0]);
              printByte(12, 2, programm[tickChoise][ledChoise][1]);
              printByte(17, 2, programm[tickChoise][ledChoise][2]);
              for (byte ledNum=0; ledNum<LEDS_COUNT; ledNum++) {
                sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][0], programm[tickChoise][ledNum][0]);
                sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][1], programm[tickChoise][ledNum][1]);
                sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][2], programm[tickChoise][ledNum][2]);
              }
              break;
            case 4: // Cursor indicate choise led
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][0], programm[tickChoise][ledChoise][0]);
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][1], programm[tickChoise][ledChoise][1]);
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][2], programm[tickChoise][ledChoise][2]);
              ledChoise++;
              if (ledChoise >= LEDS_COUNT) ledChoise = 0;
              lcd.setCursor(4, 2); lcd.print(ledChoise, HEX);
              printByte( 7, 2, programm[tickChoise][ledChoise][0]);
              printByte(12, 2, programm[tickChoise][ledChoise][1]);
              printByte(17, 2, programm[tickChoise][ledChoise][2]);
              break;
            case 9: // Cursor indicate choise red level
              programm[tickChoise][ledChoise][0]++;
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][0], programm[tickChoise][ledChoise][0]);
              printByte(7, 2, programm[tickChoise][ledChoise][0]);
              break;
            case 14: // Cursor indicate choise green level
              programm[tickChoise][ledChoise][1]++;
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][1], programm[tickChoise][ledChoise][1]);
              printByte(12, 2, programm[tickChoise][ledChoise][1]);
              break;
            case 19: // Cursor indicate choise blue level
              programm[tickChoise][ledChoise][2]++;
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][2], programm[tickChoise][ledChoise][2]);
              printByte(17, 2, programm[tickChoise][ledChoise][2]);
              break;
          }
          break;
        case 2: // Down
          switch (cursor[0]) {
            case 3: // Cursor indicate tick
              tickChoise--;
              ledChoise = 0;
              if (tickChoise >= ticksCount) tickChoise = 0;
              lcd.setCursor(1, 3);
              if (tickChoise < 10) lcd.print('.'); lcd.print(tickChoise);
              lcd.setCursor(4, 2); lcd.print(ledChoise, HEX);
              printByte(7, 2, programm[tickChoise][ledChoise][0]);
              printByte(12, 2, programm[tickChoise][ledChoise][1]);
              printByte(17, 2, programm[tickChoise][ledChoise][2]);
              for (byte ledNum=0; ledNum<LEDS_COUNT; ledNum++) {
                sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][0], programm[tickChoise][ledNum][0]);
                sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][1], programm[tickChoise][ledNum][1]);
                sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][2], programm[tickChoise][ledNum][2]);
              }
              break;
            case 4: // Cursor indicate choise led
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][0], programm[tickChoise][ledChoise][0]);
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][1], programm[tickChoise][ledChoise][1]);
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][2], programm[tickChoise][ledChoise][2]);
              ledChoise--;
              if (ledChoise >= LEDS_COUNT) ledChoise = LEDS_COUNT - 1;
              lcd.setCursor(4, 2); lcd.print(ledChoise, HEX);
              printByte( 7, 2, programm[tickChoise][ledChoise][0]);
              printByte(12, 2, programm[tickChoise][ledChoise][1]);
              printByte(17, 2, programm[tickChoise][ledChoise][2]);
              break;
            case 9: // Cursor indicate choise red level
              programm[tickChoise][ledChoise][0]--;
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][0], programm[tickChoise][ledChoise][0]);
              printByte(7, 2, programm[tickChoise][ledChoise][0]);
              break;
            case 14: // Cursor indicate choise green level
              programm[tickChoise][ledChoise][1]--;
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][1], programm[tickChoise][ledChoise][1]);
              printByte(12, 2, programm[tickChoise][ledChoise][1]);
              break;
            case 19: // Cursor indicate choise blue level
              programm[tickChoise][ledChoise][2]--;
              sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][2], programm[tickChoise][ledChoise][2]);
              printByte(17, 2, programm[tickChoise][ledChoise][2]);
              break;
          }
          break;
        default: // Nothing to choise do
          if (millis() % 1000 < 800) {
            sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][0], programm[tickChoise][ledChoise][0]);
            sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][1], programm[tickChoise][ledChoise][1]);
            sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][2], programm[tickChoise][ledChoise][2]);
          } else {
            sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][0], 0);
            sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][1], 0);
            sendCommand(LEDS[ledChoise][3], SET, LEDS[ledChoise][2], 0);
          }

      }
      break;
    case 3: // Menu "Settings"
      switch (doing) {
        case 1: // Cancel/reset
        case 3: // Enter
          state = 0;
          updateCursor(0, 3, '>');
          printMenu();
          break;
        case 4: // Left
          if (cursor[0] == 13) moveCursor(doing, 13);
          break;
        case 6: // Right
          if (cursor[0] == 0) moveCursor(doing, 13);
          break;
        case 8: // Up
          if (cursor[0] == 0) {
            displayLight = !displayLight;
            if (displayLight) lcd.backlight();
            else lcd.noBacklight();
          } else {
            mode++;
            if (mode > 2) mode = 0;
            if (mode == 0) for (byte ledNum=0; ledNum< LEDS_COUNT; ledNum++) {
              sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][0], ledsActual[ledNum][0]);
              sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][1], ledsActual[ledNum][1]);
              sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][2], ledsActual[ledNum][2]);
            }
          }
          printMenu();
          break;
        case 2: // Down
          if (cursor[0] == 0) {
            displayLight = !displayLight;
            if (displayLight) lcd.backlight();
            else lcd.noBacklight();
          } else {
            mode--;
            if (mode > 2) mode = 2;
            if (mode == 0) for (byte ledNum=0; ledNum<LEDS_COUNT; ledNum++) {
              sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][0], ledsActual[ledNum][0]);
              sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][1], ledsActual[ledNum][1]);
              sendCommand(LEDS[ledNum][3], SET, LEDS[ledNum][2], ledsActual[ledNum][2]);
            }
          }
          printMenu();
          break;
      }
      break;
  }
}


void moveCursor(byte direction, byte step) {
  lcd.setCursor(cursor[0], cursor[1]); lcd.write(' ');
  switch (direction) {
    case 4: // Left
      if (cursor[0] >= step) cursor[0] -= step;
      break;
    case 6: // Right
      if (cursor[0] <= 19-step) cursor[0] += step;
      break;
    case 2: // Down
      cursor[1] += step;
      if (cursor[1] > 3) cursor[1] = 1;
      break;
    case 8: // Up
      cursor[1] -= step;
      if (cursor[1] < 1) cursor[1] = 3;
      break;
  }
  lcd.setCursor(cursor[0], cursor[1]); lcd.write(cursor[2]);
}


void printByte(byte column, byte line, byte data) {
  lcd.setCursor(column, line);
  if (data < 100) lcd.print('.');
  if (data <  10) lcd.print('.');
  lcd.print(data);
}
