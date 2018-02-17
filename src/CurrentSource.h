/*
 * CurrentSource.h
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: Mikhail
 */

#ifndef CURRENTSOURCE_H_
#define CURRENTSOURCE_H_
#include <stdint.h>

class CurrentSource {
public:
	CurrentSource();
	CurrentSource(float);
	void setPower(float);
	float getPower(void);
private:
	void setDAC(uint16_t val);
	uint16_t getDAC();

	float powerVal;
};

#endif /* CURRENTSOURCE_H_ */
