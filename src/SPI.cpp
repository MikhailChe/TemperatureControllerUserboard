/*
 * SPI.cpp
 *
 *  Created on: 1 мар. 2018 г.
 *      Author: Mikhail
 */

#include "SPI.h"

#include <stm32f30x.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_spi.h>

SPI_class::SPI_class() {

	/**SPI3
	 PC10 SCK
	 PC12 MOSI
	 PC11 MISO
	 PA15 !SS**/
	// Enable peripheral clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);

	//Enable GPIO for MOSI, MISO, SCK
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	//*** ALTERNATE FUNCTION ***//
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_6);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_6);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_6);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_6);
	//*** END OF ALTERNATE FUNCTION BLOCK ***//

	//*** GPIO CONFIGURATION *** //
	GPIO_InitTypeDef gpio_init;
	GPIO_StructInit(&gpio_init);
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	gpio_init.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOC, &gpio_init);
	gpio_init.GPIO_Pin = GPIO_Pin_15;
	gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &gpio_init);
	//*** END OF GPIO CONFIGURATION ***//

	//** SPI INITIALIZATION **//
	SPI_InitTypeDef cartoshka;
	SPI_StructInit(&cartoshka);
	cartoshka.SPI_NSS = SPI_NSS_Hard;
	cartoshka.SPI_CPOL = SPI_CPOL_High;
	cartoshka.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_Init(SPI3, &cartoshka);
	//** END OF SPI INITIALIZATION **//

	//** SPI FIFO INITIALIZATION **//
	SPI_RxFIFOThresholdConfig(SPI3, SPI_RxFIFOThreshold_QF);
	//** END OF SPI FIFO INITIALIZATION **//

	//** NVIC **//
//	SPI_I2S_ITConfig(SPI3, SPI_I2S_IT_RXNE, ENABLE);
	//** END OF NVIC **//

	SPI_Cmd(SPI3, ENABLE);
}

bool SPI_class::dataReady() {
	return SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE);
}

uint8_t SPI_class::recieveByteBlocking() {
	while (!dataReady()) {
		asm("nop");
	}
	return SPI_ReceiveData8(SPI3);
}

SPI_class SPI;
