/*
 * Button.cpp
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: Mikhail
 */

#include "Button.h"

#include <stm32f3_discovery.h>

Button_TypeDef buttonDef = BUTTON_USER;
Button::Button(int val) {
	but = val;
	if (but == 0)
		STM_EVAL_PBInit(buttonDef, BUTTON_MODE_GPIO);

}

Button::~Button() {
}

bool Button::isPressed() {
	if (but == 0)
		return (STM_EVAL_PBGetState(buttonDef) != 0 ? true : false);
	return false;
}
