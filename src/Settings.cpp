/*
 * Settings.cpp
 *
 *  Created on: 17 февр. 2018 г.
 *      Author: Mikhail
 */

#include "Settings.h"

Settings::Settings() {
	maxTemperature = 1200;
	timeMinutes = 30;
}

float Settings::getMaxTemperature() const {
	return maxTemperature;
}

float Settings::setMaxTemperature(float val) {
	if (val < 0.0F)
		val = 0.0F;

	if (val > 2000.0F)
		val = 2000.0F;
	return maxTemperature = val;
}

int32_t Settings::getTimeMinutes() const {
	return timeMinutes;
}

int32_t Settings::setTimeMinutes(int32_t timeMinutes) {
	if (timeMinutes < 1)
		timeMinutes = 1;
	if (timeMinutes > 99)
		timeMinutes = 99;
	return this->timeMinutes = timeMinutes;
}
