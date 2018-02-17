/*
 * TimeUtils.cpp
 *
 *  Created on: 17 февр. 2018 г.
 *      Author: Mikhail
 */

#include "TimeUtils.h"

#include <system_stm32f30x.h>

void delay_ticks(uint64_t numTicks) {
	asm("nop");
	for (volatile uint64_t i = 0; i < numTicks; i++) {
		asm("nop");
	}
	asm("nop");
}

void delay_ms(uint64_t num) {
	const uint64_t clk = SystemCoreClock;
	delay_ticks((clk / 1000) * num);
}
