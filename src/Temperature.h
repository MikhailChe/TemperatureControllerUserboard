/*
 * Temperature.h
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: Mikhail
 */

#pragma once

class Temperature {
private:
	Temperature();
public:
	static Temperature& instance() {
		static Temperature t;
		return t;
	}

	Temperature(Temperature const&) = delete;
	void operator =(Temperature const&) = delete;

	float getDegrees();
};
