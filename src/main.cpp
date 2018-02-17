/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include <sys/_stdint.h>
#include <system_stm32f30x.h>

#include "Button.h"
#include "ByteDisplay.h"
#include "CurrentSource.h"
#include "Temperature.h"

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

int main(void) {

//	Temperature temperature;
	CurrentSource current(0);
	Button bUp(0);

	float powerValue = 0;
	const float DELTA = 0.001F;
//	const float DEGREES_MAX = 1700;

	bool direction = true;

	ByteDisplay& display = ByteDisplay::Instance();
	for (;;) {
		while (bUp.isPressed()) {
			delay_ms(1);
			if (direction) {
				powerValue += DELTA;
				if (powerValue > 1) {
					powerValue = 1;
				}
			} else {
				powerValue -= DELTA;
				if (powerValue <= 0) {
					powerValue = 0;
				}
			}
			current.setPower(powerValue);
			display.show((uint8_t) (powerValue * 256.0F));
		}
		direction = !direction;
		delay_ms(1);
	}
}
