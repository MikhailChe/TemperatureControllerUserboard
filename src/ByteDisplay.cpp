/*
 * ByteDisplay.cpp
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: Mikhail
 */

#include "ByteDisplay.h"

#include <stm32f3_discovery.h>

ByteDisplay& ByteDisplay::instance() {
	static ByteDisplay display;
	return display;
}

ByteDisplay::ByteDisplay() {
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);
	STM_EVAL_LEDInit(LED7);
	STM_EVAL_LEDInit(LED8);
	STM_EVAL_LEDInit(LED9);
	STM_EVAL_LEDInit(LED10);
}
void ByteDisplay::showDirection(Direction_TypeDef dir) {
	switch (dir) {
	case NORTH:
		break;
	case NORTHWEST:
		break;
	case WEST:
		break;
	case SOUTHWEST:
		break;
	case SOUTH:
		break;
	case SOUTH_EAST:
		break;
	case EAST:
		break;
	case NORTHEAST:
		break;

	}
}
void show123(uint8_t val);
void ByteDisplay::show(uint8_t val) {
	val /= 32;
	uint8_t output = 0;
	for (int i = 0; i < val; i++) {
		output |= (uint8_t) (1 << i);
	}
	show123(output);
}
void show123(uint8_t val) {
	if (val & 0x01) {
		STM_EVAL_LEDOn(LED3);
	} else {
		STM_EVAL_LEDOff(LED3);
	}
	if (val & 0x02) {
		STM_EVAL_LEDOn(LED5);
	} else {
		STM_EVAL_LEDOff(LED5);
	}
	if (val & 0x04) {
		STM_EVAL_LEDOn(LED7);
	} else {
		STM_EVAL_LEDOff(LED7);
	}
	if (val & 0x08) {
		STM_EVAL_LEDOn(LED9);
	} else {
		STM_EVAL_LEDOff(LED9);
	}
	if (val & 0x10) {
		STM_EVAL_LEDOn(LED10);
	} else {
		STM_EVAL_LEDOff(LED10);
	}
	if (val & 0x20) {
		STM_EVAL_LEDOn(LED8);
	} else {
		STM_EVAL_LEDOff(LED8);
	}
	if (val & 0x40) {
		STM_EVAL_LEDOn(LED6);
	} else {
		STM_EVAL_LEDOff(LED6);
	}
	if (val & 0x80) {
		STM_EVAL_LEDOn(LED4);
	} else {
		STM_EVAL_LEDOff(LED4);
	}

}

ByteDisplay::~ByteDisplay() {
// TODO Auto-generated destructor stub
}

