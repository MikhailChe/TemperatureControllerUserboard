/*
 * ByteDisplay.h
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: Mikhail
 */

#ifndef BYTEDISPLAY_H_
#define BYTEDISPLAY_H_

#include <sys/_stdint.h>
typedef enum {
	NORTH, NORTHWEST, WEST, SOUTHWEST, SOUTH, SOUTH_EAST, EAST, NORTHEAST
} Direction_TypeDef;

class ByteDisplay {
public:
	static ByteDisplay& instance();
	void show(uint8_t val);
	void showDirection(Direction_TypeDef);

private:
	ByteDisplay();
	~ByteDisplay();
};
#endif /* BYTEDISPLAY_H_ */
