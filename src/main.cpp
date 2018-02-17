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
#include <sys/_stdint.h>

#include "Button.h"
#include "ByteDisplay.h"
#include "CurrentSource.h"
#include "Settings.h"
#include "Temperature.h"
#include "TimeUtils.h"

int main(void) {

	Temperature temperature;
	CurrentSource current;
	Button bUp(GPIOA, GPIO_Pin_1, GPIO_PuPd_UP);
	Button bDown(GPIOA, GPIO_Pin_2, GPIO_PuPd_UP);
	Button bOK(GPIOA, GPIO_Pin_3, GPIO_PuPd_UP);
	Button bCancel(GPIOA, GPIO_Pin_4, GPIO_PuPd_UP);

	const float DELTA = 0.001F;

//MODE0 - Start Or Stop
//MODE1 - Set Max temperature
//MODE3 - Set Time
//MODE4 - Set Current Temperature
#define MODE_STARTSTOP 0
#define MODE_MAXTEMP 1
#define MODE_SETTIME 3
#define MODE_SETCURTEMP 4
	uint8_t mode = 0;

	ByteDisplay& display = ByteDisplay::instance();
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
					display.show(current.getPower() * 255.0f);
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
