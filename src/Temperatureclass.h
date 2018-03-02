/*
 * Temperature.h
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: Mikhail
 */

#pragma once
#include <sys/_stdint.h>

class Temperature_class {
public:
	Temperature_class();

	float getDegrees();
	uint16_t getDegreesInt();
};
extern Temperature_class Temperature;
