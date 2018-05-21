#ifndef ALLHEADERS_H
#define ALLHEADERS_H

#include <Thread.h>
#include <Wire.h>
#include <Eeprom24C128_256.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LowPower.h>
#include <LiquidCrystal_I2C.h>
//#include <LiquidCrystal.h>

#define EEPROM_ADDRESS  0x50

#define buttonPin 4
#define startPin 1
#define dataTemperature 10
#define delayTemperature 120000 
#define wakeUpPin 3

#define powerDisplay 11
#define powerEEPROM 12

#define memoryDelay 10

#define rs 10
#define en 9
#define d4 8
#define d5 7
#define d6 6
#define d7 5

#include "MemoryController.h"
#include "Counters.h"

#endif
