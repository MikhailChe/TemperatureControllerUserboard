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
#define _BV(a,b) (a?(1<<b):(0))

int main4(void) {
	/**SPI3
	 PC10 SCK
	 PC12 MOSI
	 PC11 MISO
	 PA15 !SS**/
	GPIO_InitTypeDef gpio_init;
	GPIO_StructInit(&gpio_init);
	gpio_init.GPIO_Mode = GPIO_Mode_IN;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio_init.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOC, &gpio_init);

	gpio_init.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOA, &gpio_init);
	volatile uint8_t val = 0;
	bool pa15old = false;
	for (;;) {
		if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)) {
			bool pa15new = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12);
			if (pa15new && !pa15old) {
				val++;
				Display.show(val);
			}
			pa15old = pa15new;
		}
	}
	return 0;
}

int main(void) {
	SPI.dataReady();
	while (true) {

//		float temperatureCelsius = Temperature.getDegrees() - 273.25;
		Display.show(
				GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12)
						| (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15))<< 1);
	}
	return 0;
}

void main2(void) {
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
}

void mainsometime(void) {

	Temperature_class temperature;
	CurrentSource current;
	Button bUp(GPIOA, GPIO_Pin_1, GPIO_PuPd_UP);
	Button bDown(GPIOA, GPIO_Pin_2, GPIO_PuPd_UP);
	Button bOK(GPIOA, GPIO_Pin_3, GPIO_PuPd_UP);
	Button bCancel(GPIOA, GPIO_Pin_4, GPIO_PuPd_UP);

	//MODE0 - Start Or Stop
	//MODE1 - Set Max temperature
	//MODE3 - Set Time
	//MODE4 - Set Current Temperature
#define MODE_STARTSTOP 0
#define MODE_MAXTEMP 1
#define MODE_SETTIME 3
#define MODE_SETCURTEMP 4
	uint8_t mode = 0;

	for (;;) {
		if (mode == MODE_STARTSTOP) {
			if (isClicked(bOK)) {
				bool direction = true;
				while (!isClicked(bCancel)) {
					if (direction) {
						if (temperature.getDegrees()
								>= Settings::instance().getMaxTemperature()) {
							direction = false;
						}
					}
					if (direction)
						current.setPower(current.getPower() + DELTA);
					else
						current.setPower(current.getPower() - DELTA);
					Display.show((uint8_t) (current.getPower() * 255.0f));
				}
			} else if (isClicked(bUp)) {
				mode = MODE_MAXTEMP;
			} else if (isClicked(bDown)) {
				mode = MODE_SETCURTEMP;
			}
		} else if (mode == MODE_MAXTEMP) {
			if (isClicked(bOK)) {
				Settings& s = Settings::instance();
				float maxTemp = s.getMaxTemperature();
				while (!isClicked(bCancel)) {
					if (isPressed(bUp)) {
						maxTemp += DELTA;
					} else if (isPressed(bUp)) {
						maxTemp -= DELTA;
					} else if (isClicked(bOK)) {
						s.setMaxTemperature(maxTemp);
						break;
					}
				}
			} else if (isClicked(bUp)) {
				mode = MODE_SETTIME;
			} else if (isClicked(bDown)) {
				mode = MODE_STARTSTOP;
			}
		} else if (mode == MODE_SETTIME) {
			if (isClicked(bOK)) {
				Settings& s = Settings::instance();
				int32_t timeMinutes = s.getTimeMinutes();

				while (!isClicked(bCancel)) {
					if (isPressed(bUp)) {
						timeMinutes++;
						if (timeMinutes > 99) {
							timeMinutes = 99;
						}
						delay_ms(1000);
					} else if (isPressed(bDown)) {
						timeMinutes--;
						if (timeMinutes < 1) {
							timeMinutes = 1;
						}
						delay_ms(1000);
					} else if (isClicked(bOK)) {
						s.setTimeMinutes(timeMinutes);
						break;
					}
				}
			} else if (isClicked(bUp)) {
				mode = MODE_SETCURTEMP;
			} else if (isClicked(bDown)) {
				mode = MODE_MAXTEMP;
			}
		} else if (mode == MODE_SETCURTEMP) {
			if (isClicked(bOK)) {
				float oldPower = current.getPower();
				bool isCanceled = true;
				while (!isClicked(bCancel) || !isClicked(bOK)) {
					if (isPressed(bUp)) {
						current.setPower(current.getPower() + DELTA);
					} else if (isPressed(bDown)) {
						current.setPower(current.getPower() - DELTA);
					} else if (isClicked(bOK)) {
						isCanceled = false;
					}
				}
				if (isCanceled) {
					current.setPower(oldPower);
				}
			} else if (isClicked(bUp)) {
				mode = MODE_STARTSTOP;
			} else if (isClicked(bDown)) {
				mode = MODE_SETTIME;
			}
		}
	}
}

