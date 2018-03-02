<<<<<<< HEAD
/*
 * Button.cpp
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: Mikhail
 */

#include "Button.h"

#include <stm32f30x_rcc.h>

Button::Button(GPIO_TypeDef* gpio, uint32_t clockRegister, uint8_t pinNum) :
		Button(gpio, clockRegister, pinNum, GPIO_PuPd_UP) {

}
Button::Button(GPIO_TypeDef* gpio, uint32_t clockRegister, uint8_t pinNum,
		GPIOPuPd_TypeDef pull) {
	RCC_AHBPeriphClockCmd(clockRegister, ENABLE);

	port = gpio;
	pin = pinNum;
	GPIO_InitTypeDef but_init;
	GPIO_StructInit(&but_init);

	but_init.GPIO_Mode = GPIO_Mode_IN;
	but_init.GPIO_Pin = (1UL << pin);
	but_init.GPIO_PuPd = pull;
	but_init.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(port, &but_init);

//If we are asked to pull up, state might be revesed,
//meaning when button is pressed it goes to GND, and bit will be read as 0.
//Otherwise, if we are asked to pull down or not to pull at all,
//we assume that pushing a button leads to a high state;
	if (pull == GPIO_PuPd_UP)
		inverse = true;
	else
		inverse = false;
}
bool Button::get() {
	return (inverse ?
			!GPIO_ReadInputDataBit(port, pin) : GPIO_ReadInputDataBit(port, pin));
}
bool isPressed(Button& but) {
	int8_t val = 0;
	for (int8_t i = 0; i < 30; i++) {
		if (but.get())
			val++;
		else
			val--;
		delay_ms(1);
	}
	if (val > 0)
		return true;
	return false;
}
bool isClicked(Button& but) {
	if (!isPressed(but))
		return false;
	while (isPressed(but))
		;
	return true;
}
=======
/*
 * Button.cpp
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: Mikhail
 */

#include "Button.h"

Button::Button(GPIO_TypeDef* gpio, uint16_t pinNum) :
		Button(gpio, pinNum, GPIO_PuPd_UP) {

}
Button::Button(GPIO_TypeDef* gpio, uint16_t pinNum, GPIOPuPd_TypeDef pull) {
	port = gpio;
	pin = pinNum;
	GPIO_InitTypeDef but_init;
	GPIO_StructInit(&but_init);

	but_init.GPIO_Mode = GPIO_Mode_IN;
	but_init.GPIO_Pin = pin;
	but_init.GPIO_PuPd = pull;
	but_init.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(port, &but_init);

//If we are asked to pull up, state might be revesed,
//meaning when button is pressed it goes to GND, and bit will be read as 0.
//Otherwise, if we are asked to pull down or not to pull at all,
//we assume that pushing a button leads to a high state;
	if (pull == GPIO_PuPd_UP)
		inverse = true;
	else
		inverse = false;
}
bool Button::get() {
	return (inverse ?
			!GPIO_ReadInputDataBit(port, pin) : GPIO_ReadInputDataBit(port, pin));
}
bool isPressed(Button& but) {
	int8_t val = 0;
	for (int8_t i = 0; i < 30; i++) {
		if (but.get())
			val++;
		else
			val--;
		delay_ms(1);
	}
	if (val > 0)
		return true;
	return false;
}
bool isClicked(Button& but) {
	if (!isPressed(but))
		return false;
	while (isPressed(but))
		;
	return true;
}
>>>>>>> branch 'master' of git@github.com:MikhailChe/TemperatureControllerUserboard.git
