/*
 * Temperature.cpp
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: Mikhail
 */

#include "Temperature.h"

#include <stm32f3_discovery_lsm303dlhc.h>
#include <stm32f30x.h>
#include <stm32f30x_adc.h>
#include <stm32f30x_dma.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>

void adc_init() {
// ==============================================================================
//                             ##### How to use this driver #####
//  ==============================================================================
//    [..]
//    (#) select the ADC clock using the function RCC_ADCCLKConfig()
	RCC_ADCCLKConfig(RCC_ADC34PLLCLK_Div256);
	//    (#) Enable the ADC interface clock using RCC_AHBPeriphClockCmd();
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
//    (#) ADC pins configuration
//        (++) Enable the clock for the ADC GPIOs using the following function:
//             RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOx, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
//        (++) Configure these ADC pins in analog mode using GPIO_Init();
	GPIO_InitTypeDef adc_gpio_init;
	adc_gpio_init.GPIO_Mode = GPIO_Mode_AN;
	adc_gpio_init.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	adc_gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	adc_gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &adc_gpio_init);
//    (#) Configure the ADC conversion resolution, data alignment, external
//        trigger and edge, sequencer lenght and Enable/Disable the continuous mode
//        using the ADC_Init() function.
	ADC_InitTypeDef adc_init;
	adc_init.ADC_AutoInjMode = ADC_AutoInjec_Enable;
	adc_init.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
	adc_init.ADC_DataAlign = ADC_DataAlign_Right;
	adc_init.ADC_NbrOfRegChannel = 2;
	adc_init.ADC_OverrunMode = ADC_OverrunMode_Enable;
	adc_init.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init(ADC1, &adc_init);
//    (#) Activate the ADC peripheral using ADC_Cmd() function.
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_601Cycles5);
	ADC_RegularChannelSequencerLengthConfig(ADC1, 1);

	ADC_SelectDifferentialMode(ADC1, ADC_Channel_3 | ADC_Channel_4, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	ADC_GetConversionValue(ADC1);

	ADC_DMAConfig(ADC1, ADC_DMAMode_Circular);
	ADC_DMACmd(ADC1, ENABLE);

	DMA_InitTypeDef adc_dma_init;
	DMA_StructInit(&adc_dma_init);

	DMA_Init(DMA1_Channel1, &adc_dma_init);
	//
//    *** ADC channels group configuration ***
//    ========================================
//    [..]
//    (+) To configure the ADC channels features, use ADC_Init(), ADC_InjectedInit()
//        and ADC_RegularChannelConfig() functions or/and ADC_InjectedChannelConfig()
//    (+) To activate the continuous mode, use the ADC_ContinuousModeCmd()
//        function.
//    (+) To activate the Discontinuous mode, use the ADC_DiscModeCmd() functions.
//    (+) To activate the overrun mode, use the ADC_OverrunModeCmd() functions.
//    (+) To activate the calibration mode, use the ADC_StartCalibration() functions.
//    (+) To read the ADC converted values, use the ADC_GetConversionValue()
//        function.
//
//    *** DMA for ADC channels features configuration ***
//    ===================================================
//    [..]
//    (+) To enable the DMA mode for ADC channels group, use the ADC_DMACmd() function.
//    (+) To configure the DMA transfer request, use ADC_DMAConfig() function.
// * */

}

Temperature::Temperature() {
	LSM303DLHCMag_InitTypeDef mtd;
	mtd.Temperature_Sensor = LSM303DLHC_TEMPSENSOR_ENABLE;
	mtd.MagOutput_DataRate = LSM303DLHC_ODR_220_HZ;
	mtd.MagFull_Scale = LSM303DLHC_FS_8_1_GA;
	mtd.Working_Mode = LSM303DLHC_CONTINUOS_CONVERSION;

	LSM303DLHC_MagInit(&mtd);
}

Temperature::~Temperature() {

}

float Temperature::getDegrees() {
	float tempint = getDegreesInt();
	volatile float trueValue = 21.0F + ((float) tempint / 128.0F);

	return trueValue;
}

int16_t Temperature::getDegreesInt() {

	uint8_t tRegHigh;
	uint8_t tRegLow;

	LSM303DLHC_Read(MAG_I2C_ADDRESS, LSM303DLHC_TEMP_OUT_H_M, &tRegHigh, 1);
	LSM303DLHC_Read(MAG_I2C_ADDRESS, LSM303DLHC_TEMP_OUT_L_M, &tRegLow, 1);

	int16_t tempint = (int16_t) (((tRegHigh << 8) | tRegLow) & 0xFFF0);

	return tempint;
}
