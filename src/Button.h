/*
 * Button.h
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: Mikhail
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <sys/_stdint.h>

#include "TimeUtils.h"

class Button final {
public:
	Button(GPIO_TypeDef* gpio, uint8_t pinNum);
	Button(GPIO_TypeDef* gpio, uint8_t pinNum, GPIOPuPd_TypeDef pull);
	bool get();
private:
	GPIO_TypeDef* port;
	uint8_t pin;
	bool inverse;
};
bool isPressed(Button& but);
bool isClicked(Button& but);
#endif /* BUTTON_H_ */
