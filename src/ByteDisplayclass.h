/*
 * ByteDisplay.h
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: Mikhail
 */

#ifndef BYTEDISPLAYCLASS_H_
#define BYTEDISPLAYCLASS_H_

#include <sys/_stdint.h>

typedef enum {
	NORTH, NORTHWEST, WEST, SOUTHWEST, SOUTH, SOUTH_EAST, EAST, NORTHEAST
} Direction_TypeDef;

class ByteDisplay_class {
public:
	ByteDisplay_class();
	void show(uint8_t val);
	void showDirection(Direction_TypeDef);
};

extern ByteDisplay_class Display;
#endif /* BYTEDISPLAYCLASS_H_ */
