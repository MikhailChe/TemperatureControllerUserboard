/*
 * TimeUtils.h
 *
 *  Created on: 17 февр. 2018 г.
 *      Author: Mikhail
 */

#ifndef TIMEUTILS_H_
#define TIMEUTILS_H_

#include <sys/_stdint.h>

void delay_ticks(uint64_t numTicks);
void delay(uint32_t num);
uint32_t millis();

#endif /* TIMEUTILS_H_ */
