/*
 * Settings.h
 *
 *  Created on: 17 февр. 2018 г.
 *      Author: Mikhail
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <sys/_stdint.h>

class Settings {
private:
	/**Maximum temperature in Kelvins */
	float maxTemperature; /**Maximum temperature in Kelvins */
	int32_t timeMinutes;
	Settings();
public:
	Settings(Settings const &) = delete;
	void operator =(Settings const&) = delete;

	static Settings& instance() {
		static Settings i;
		return i;
	}

	float getMaxTemperature() const;
	float setMaxTemperature(float val);

	int32_t getTimeMinutes() const;
	int32_t setTimeMinutes(int32_t timeMinutes);
};

#endif /* SETTINGS_H_ */
