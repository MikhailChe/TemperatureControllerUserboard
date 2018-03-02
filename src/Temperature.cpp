/*
 * Temperature.cpp
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: Mikhail
 */

#include "Temperature.h"

#include <stm32f30x.h>
#include <stm32f30x_adc.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <sys/_stdint.h>

void adc_init() {

//    (#) select the ADC clock using the function RCC_ADCCLKConfig()
	RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div256);
//    (#) Enable the ADC interface clock using RCC_AHBPeriphClockCmd();
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
//    (#) ADC pins configuration
//        (++) Enable the clock for the ADC GPIOs using the following function:
//             RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOx, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
//        (++) Configure these ADC pins in analog mode using GPIO_Init();
	GPIO_InitTypeDef adc_gpio_init;
	GPIO_StructInit(&adc_gpio_init);
	adc_gpio_init.GPIO_Mode = GPIO_Mode_AN;
	adc_gpio_init.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	adc_gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &adc_gpio_init);
//    (#) Configure the ADC conversion resolution, data alignment, external
//        trigger and edge, sequencer lenght and Enable/Disable the continuous mode
//        using the ADC_Init() function.
	ADC_InitTypeDef adc_init;
	ADC_StructInit(&adc_init);
	ADC_Init(ADC1, &adc_init);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_601Cycles5);

	ADC_RegularChannelSequencerLengthConfig(ADC1, 1);

	ADC_SelectCalibrationMode(ADC1, ADC_CalibrationMode_Single);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1))
		;

//ADC_SelectDifferentialMode(ADC1, ADC_Channel_3, ENABLE);

//    (#) Activate the ADC peripheral using ADC_Cmd() function.
	ADC_Cmd(ADC1, ENABLE);
}

Temperature::Temperature() {
	adc_init();
}
#define ADC_RESOLUTION 12
#define ADC_MAXVAL ((float)((1UL << ADC_RESOLUTION)-1))
#define ADC_VREF 3.3F
#define AMPLIFICATION 3.0F/0.022F  //3V (volts) correspond to real 22mV
#define NORMALIZE_ADCVAL(T) ((((float)T)*ADC_VREF)/ADC_MAXVAL)/AMPLIFICATION

static uint16_t getDegreesInt() {
	ADC_StartConversion(ADC1);
	while (ADC_GetStartConversionStatus(ADC1))
		;
	return ADC_GetConversionValue(ADC1);
}
float Temperature::getDegrees() {

	return (getDegreesInt() / ADC_MAXVAL);
}

