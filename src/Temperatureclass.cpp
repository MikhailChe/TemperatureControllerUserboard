/*
 * Temperature.cpp
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: Mikhail
 */

#include "Temperatureclass.h"

#include "SPI.h"

Temperature_class::Temperature_class() {
}

float Temperature_class::getDegrees() {
	return ((float) getDegreesInt()) / 10.0f;
}
volatile bool error = 0;
uint16_t Temperature_class::getDegreesInt() {
	uint16_t temperature = 0;
	uint8_t state = 0;
	while (SPI.dataReady()) {
		SPI.recieveByteBlocking();
	}
	while (true) {
		uint8_t value = SPI.recieveByteBlocking();
		switch (state) {
		case 0:
			if (value == 0xDE)
				state++;
			break;
		case 1:
			if (value == 0xAD)
				state++;
			else
				state = 0;
			break;
		case 2:
			if (value == 0xBE)
				state++;
			else
				state = 0;
			break;
		case 3:
			if (value == 0xEF)
				state++;
			else
				state = 0;
			break;
		case 4:
			temperature = value;
			state++;
			break;
		case 5:
			temperature |= (uint16_t) (((uint16_t) value) << 8);
			return temperature;
		}
	}
	return 0;
}

Temperature_class Temperature;
