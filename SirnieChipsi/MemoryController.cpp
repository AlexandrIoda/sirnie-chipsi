#include "MemoryController.h"

void MemoryController::writeULong(word address, unsigned long value) {
	byte buff[4];

	(unsigned long&)buff = value;
	for (byte i = 0; i < 4; i++) {
		eeprom->writeByte(0x0 + i, buff[i]);
		delay(memoryDelay);
	}
}

unsigned long MemoryController::readULong(word address) {
	byte buff[4];

	for (byte i = 0; i < 4; i++) {
		buff[i] = eeprom->readByte(address + i);
		delay(memoryDelay);
	}
	
	return (unsigned long&)buff;
}

float MemoryController::toFloat(unsigned long value) {
	byte buffer[4];
	(unsigned long&)buffer = value;
	return (float&) buffer;
}

int MemoryController::toInt(unsigned long value) {
	byte buffer[4];
	(unsigned long&)buffer = value;
	return (int&) buffer;
}

unsigned long MemoryController::toULong(int value) {
	byte buffer[4];
	(int&)buffer = value;
	return (unsigned long&)buffer;
}

unsigned long MemoryController::toULong(float value) {
	byte buffer[4];
	(float&)buffer = value;
	return (unsigned long&)buffer;
}

MemoryController::MemoryController(Eeprom24C128_256 &eeprom) {
	this->eeprom = &eeprom;
}