#include "AllHeaders.h"

//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal_I2C lcd(0x27,20,4);
Eeprom24C128_256 eeprom(EEPROM_ADDRESS);

Thread countingThread = Thread();
Thread displayThread = Thread();
Thread buttonThread = Thread();

Counters *counters;
MemoryController *memoryController;

int currentScreen = 0;
int prevScreen = 0;

int prevStatus = 0;
int prevMillis = 0;
bool isProcessed = false;

void recount();
void count();
void display();
void button();

void setup() {
	Serial.begin(9600);
  lcd.init();
  lcd.backlight();
	eeprom.initialize();
	analogReference(DEFAULT);

	pinMode(powerDisplay, OUTPUT);
	pinMode(powerEEPROM, OUTPUT);
	pinMode(buttonPin, INPUT);

	digitalWrite(powerDisplay, 1);
	digitalWrite(powerEEPROM, 1);

	attachInterrupt(digitalPinToInterrupt(2), &count, CHANGE);

	countingThread.onRun(recount);
	countingThread.setInterval(200);

	displayThread.onRun(display);
	displayThread.setInterval(100);

	buttonThread.onRun(button);
	buttonThread.setInterval(100);

	counters = new Counters();
	memoryController = new MemoryController(eeprom);

	counters->signalsGRM = memoryController->readULong(8);
	counters->signalsOil = memoryController->readULong(12);

	counters->signalsTotal = memoryController->readULong(16);
	counters->signalsDaily = memoryController->readULong(20);
}

void loop() {
	if (displayThread.shouldRun())
		displayThread.run();

	if (countingThread.shouldRun())
		countingThread.run();

	if (buttonThread.shouldRun())
		buttonThread.run();
}

void recount() {
	counters->recount();
}

void count() {
	counters->increaseCounters();
}

void display() {
	if (prevScreen != currentScreen) {
		lcd.clear();
		prevScreen = currentScreen;
	}

	switch (currentScreen) {
		case 4: {
			lcd.setCursor(0, 0);
			lcd.print("Total:");
			lcd.setCursor(7, 0);
			lcd.print(counters->total);

			char* floatBuffer = new char[8]();
			dtostrf(counters->daily, -7, 1, floatBuffer);

			lcd.setCursor(0, 1);
			lcd.print("Daily:");
			lcd.setCursor(7, 1);
			lcd.print(floatBuffer);

			delete[]floatBuffer;

			break;
		}
		case 1: {
			lcd.setCursor(0, 0);
			lcd.print("GRM:");
			lcd.setCursor(5, 0);
			lcd.print(counters->grm);

			lcd.setCursor(0, 1);
			lcd.print("Oil:");
			lcd.setCursor(5, 0);
			lcd.print(counters->oil);

			break;
		}
		case 2: {
			lcd.setCursor(0, 0);
			lcd.print(counters->signalsTotal);

			lcd.setCursor(0, 1);
			lcd.print(counters->signalsDaily);
		}
    case 0:{
      lcd.setCursor(0, 0);
      lcd.print(counters->signalsDaily);
      break;
    }
	}
}

void button() {
	int currentStatus = digitalRead(buttonPin);
	int currentMillis = millis();
	int deltaTime = currentMillis - prevMillis;

	if (prevStatus == HIGH && !isProcessed && deltaTime >= 2000) {
		// Here button processing
		Serial.println("Long press");

		isProcessed = true;
	}

	if (prevStatus == HIGH && currentStatus == LOW && !isProcessed && deltaTime < 2000) {
		// Short press
		Serial.println("Shrot press");

		isProcessed = true;
	}

	if (prevStatus == LOW && currentStatus == HIGH) {
		prevMillis = currentMillis;
		isProcessed = false;
	}

	prevStatus = currentStatus;
}
