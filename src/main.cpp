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
#include "CurrentSourceclass.h"
#include "SPI.h"
#include "Temperatureclass.h"
#include "TimeUtils.h"
#include <math.h>

static const double DELTA = 0.001F;
/**SPI3
 PC10 SCK
 PC12 MOSI
 PC11 MISO
 PA15 !SS**/

#define POWER_PER_DEGREE 1.0f/2000.0f

double integral = 0;

void safety() {
	uint32_t time = millis();
	while (!SPI.dataReady()) {
		if (millis() - time > 5000) {
			for (;;) {
				//TODO: ERROR. TURN TEMPERATURE DOWN
				CurrentSource.setPower(CurrentSource.getPower() - .01f);
				Display.show((uint8_t) (CurrentSource.getPower() * 255.0f));
				delay(100);
			}
		}
	}
}
void countdown() {
	for (int i = 10; i > 0; i--) {
		Display.show((uint8_t) i);
		delay(1000);
	}
	Display.show(0);
}

int ravnomer() {
	SPI.dataReady();
	CurrentSource.setPower(0);

	countdown();
	uint32_t time = millis();
	double temperature_old = Temperature.getDegrees();
	double temperature = temperature_old;
	double deltaTemperature = 0;
	uint32_t deltaTime = 0;

	delay(10);
	double derivative = 0;

	for (;;) {
		while (temperature < 1600) {
			deltaTime = millis() - time;
			time = millis();
			safety();
			temperature = Temperature.getDegrees();
			deltaTemperature = temperature - temperature_old;
			temperature_old = temperature;

			derivative = deltaTemperature / (deltaTime / 1000.0);

			if (derivative < .8) {
				CurrentSource.setPower(CurrentSource.getPower() + DELTA * 2);
			} else if (derivative > 1.2) {
				CurrentSource.setPower(CurrentSource.getPower() - DELTA * 2);
			}
			Display.show((uint8_t) (CurrentSource.getPower() * 255.0));
		}

		while (temperature > 300) {
			deltaTime = millis() - time;
			time = millis();
			safety();
			temperature = Temperature.getDegrees();
			deltaTemperature = temperature - temperature_old;
			temperature_old = temperature;

			derivative = deltaTemperature / (deltaTime / 1000.0);

			if (derivative > -.8) {
				CurrentSource.setPower(CurrentSource.getPower() - DELTA * 2);
			} else if (derivative < -1.2) {
				CurrentSource.setPower(CurrentSource.getPower() + DELTA * 2);
			}
			Display.show((uint8_t) (CurrentSource.getPower() * 255.0));
		}
	}

	return 0;
}

int main(void){

	ravnomer();
}

int main3(void) {
	SPI.dataReady();
	CurrentSource.setPower(0);

	for (int i = 10; i > 0; i--) {
		Display.show((uint8_t) i);
		delay(1000);
	}
	Display.show(0);
	const double setTemperature = 1000;
	unsigned long lastMeasurementTime = millis();

	const double proportionalCoefficient = POWER_PER_DEGREE * 3.6;
	const double integrationCoefficient = proportionalCoefficient * .11;
	const double differentialCoefficient = 0;

	double smoothPulsations = 0;
	double oldError = NAN;

	while (true) {
		safety();
		double currentTemperature = Temperature.getDegrees();
		double temperatureError = setTemperature - currentTemperature;

		double proportionalImpact = temperatureError * proportionalCoefficient;

		integral += temperatureError
				* ((millis() - lastMeasurementTime) / 1000.0)
				* integrationCoefficient;
		if (integral > .5) {
			integral = .5;
		} else if (integral < -.5) {
			integral = -.5;
		}

		double differentialImpact = 0;
		if (!std::isnan(oldError)) {
			differentialImpact = (temperatureError - oldError)
					* differentialCoefficient;
		}
		oldError = temperatureError;

		lastMeasurementTime = millis();

		double summImpact = proportionalImpact + integral + differentialImpact;
		if (summImpact > 1) {
			summImpact = 1;

		} else if (summImpact < 0) {
			summImpact = 0;
		}
		double powerToRegulatorCurve = std::acos(1 - 2.0 * summImpact)
				/ 3.1416f;

		smoothPulsations = smoothPulsations * .5 + powerToRegulatorCurve * .5;
		CurrentSource.setPower((float) smoothPulsations);
		Display.show((uint8_t) (CurrentSource.getPower() * 255.f));
	}
	return 0;
}

int main2(void) {
	CurrentSource_class current;
	Button bUp(GPIOA, RCC_AHBPeriph_GPIOA, GPIO_Pin_0, GPIO_PuPd_NOPULL);

	for (;;) {
		while (!isPressed(bUp))
			;
		while (isPressed(bUp)) {
			current.setPower((float) (current.getPower() + DELTA));
			Display.show((uint8_t) (current.getPower() * 255.0f));
		}
		while (!isPressed(bUp))
			;
		while (isPressed(bUp)) {
			current.setPower((float) (current.getPower() - DELTA));
			Display.show((uint8_t) (current.getPower() * 255.0f));
		}
	}
	return 0;
}
