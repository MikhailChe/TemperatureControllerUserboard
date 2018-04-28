/*
 * CurrentSource.h
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: Mikhail
 */

#ifndef CURRENTSOURCECLASS_H_
#define CURRENTSOURCECLASS_H_
#include <stdint.h>

class CurrentSource_class {
public:
	CurrentSource_class();
	CurrentSource_class(double);
	void setPower(double);
	float getPower(void);
private:
	void setDAC(uint16_t val);
	uint16_t getDAC();

	double powerVal;
};
extern CurrentSource_class CurrentSource;

#endif /* CURRENTSOURCECLASS_H_ */
