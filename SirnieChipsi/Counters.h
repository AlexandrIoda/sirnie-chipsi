#ifndef COUNTERS_H
#define COUNTERS_H

#include "AllHeaders.h"

class Counters {
public:
	unsigned long signalsTotal = 0;
	unsigned long signalsDaily = 0;

	unsigned long signalsGRM = 0;
	unsigned long signalsOil = 0;

	unsigned long total = 0;
	float daily = 0.0f;

	int grm;
	int oil;

	void increaseCounters() {
		signalsTotal++;
		signalsDaily++;

		if (signalsGRM > 0)
			signalsGRM--;

		if (signalsOil > 0)
			signalsOil--;
	}

	void recount() {
		total = signalsTotal / 10000;
		daily = signalsDaily / 10000.0f;

		grm = signalsGRM / 10000;
		oil = signalsOil / 10000;
	}
};

#endif