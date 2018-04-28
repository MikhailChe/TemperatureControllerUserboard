/*
 * CurrentSource.cpp
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: Mikhail
 */

#include "CurrentSourceclass.h"

#include <stm32f30x.h>
#include <stm32f30x_dac.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <sys/_stdint.h>

DAC_InitTypeDef dac_init;

CurrentSource_class::CurrentSource_class() :
		CurrentSource_class(0) {
}

CurrentSource_class::CurrentSource_class(double initial) {
	setPower(initial);

	//    (+) DAC APB clock must be enabled to get write access to DAC
	//        registers using RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	/*    (+) Configure DAC_OUTx (DAC_OUT1: PA4, DAC_OUT2: PA5) in analog mode.*/

	GPIO_InitTypeDef dac_analog_gpio;
	GPIO_StructInit(&dac_analog_gpio);
	dac_analog_gpio.GPIO_Mode = GPIO_Mode_AN;
	dac_analog_gpio.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA, &dac_analog_gpio);

	//    (+) Configure the DAC channel using DAC_Init();
	DAC_StructInit(&dac_init);
	DAC_Init(DAC_Channel_1, &dac_init);

	//    (+) Enable the DAC channel using DAC_Cmd();
	DAC_Cmd(DAC_Channel_1, ENABLE);
}

void CurrentSource_class::setPower(double val) {
	if (val < 0)
		val = 0;
	if (val > 1)
		val = 1;
	powerVal = val;
	uint16_t scaled = (uint16_t) ((double) (val * (double) (1 << 12)));
	setDAC(scaled);
}
float CurrentSource_class::getPower(void) {
	return powerVal;
}
void CurrentSource_class::setDAC(uint16_t val) {
	if (val > 4095)
		val = 4095;
	DAC_SetChannel1Data(DAC_Align_12b_R, val);

}
uint16_t CurrentSource_class::getDAC() {
	return DAC_GetDataOutputValue(DAC_Channel_1);
}

CurrentSource_class CurrentSource;

