/*
 * Temperature.h
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: Mikhail
 */

#pragma once
#include <sys/_stdint.h>

class Temperature {
public:
	Temperature();
	virtual ~Temperature();

	float getDegrees();
	int16_t getDegreesInt();
};
