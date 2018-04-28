/*
 * TimeUtils.cpp
 *
 *  Created on: 17 февр. 2018 г.
 *      Author: Mikhail
 */

#include "TimeUtils.h"

#include <system_stm32f30x.h>
#include <stm32f30x.h>

volatile uint32_t systickInitSuccess = SysTick_Config(SystemCoreClock / 1000);

volatile uint32_t millisecondsPassed = 0;

extern "C" {
void SysTick_Handler(void) {
	millisecondsPassed++;
}
}

void delay_ticks(uint64_t numTicks) {
	asm("nop");
	for (volatile uint64_t i = 0; i < numTicks; i++) {
		asm("nop");
	}
	asm("nop");
}

uint32_t millis() {
	return millisecondsPassed;
}

void delay(uint32_t num) {
	uint32_t startTime = millisecondsPassed;
	while ((millisecondsPassed - startTime) < num) {
		asm("nop");
	}
}
