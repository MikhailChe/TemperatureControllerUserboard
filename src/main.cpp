/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <sys/_stdint.h>

#include "Button.h"
#include "ByteDisplayclass.h"
#include "CurrentSource.h"
#include "Settings.h"
#include "SPI.h"
#include "Temperatureclass.h"
#include "TimeUtils.h"

static const float DELTA = 0.001F;
/**SPI3
 PC10 SCK
 PC12 MOSI
 PC11 MISO
 PA15 !SS**/

int main(void) {
	CurrentSource current;
	Button bUp(GPIOA, RCC_AHBPeriph_GPIOA, GPIO_Pin_0, GPIO_PuPd_NOPULL);

	for (;;) {
		while (!isPressed(bUp))
			;
		while (isPressed(bUp)) {
			current.setPower(current.getPower() + DELTA);
			Display.show((uint8_t) (current.getPower() * 255.0f));
		}
		while (!isPressed(bUp))
			;
		while (isPressed(bUp)) {
			current.setPower(current.getPower() - DELTA);
			Display.show((uint8_t) (current.getPower() * 255.0f));
		}
	}
	return 0;
}
