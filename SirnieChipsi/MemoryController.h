#ifndef MEMORYCONTROLLER_H
#define MEMORYCONTROLLER_H

#include "AllHeaders.h"

class MemoryController {
private:
	Eeprom24C128_256 *eeprom;

public:
	void MemoryController::writeULong(word address, unsigned long value);
	unsigned long MemoryController::readULong(word address);

	float toFloat(unsigned long value);
	int toInt(unsigned long value);

	unsigned long toULong(int value);
	unsigned long toULong(float value);

	MemoryController(Eeprom24C128_256 &eeprom);
};

#endif