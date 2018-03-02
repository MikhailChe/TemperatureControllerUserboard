/*
 * SPI.h
 *
 *  Created on: 1 мар. 2018 г.
 *      Author: Mikhail
 */

#ifndef SPI_H_
#define SPI_H_

#include <sys/_stdint.h>

class SPI_class {
public:
	SPI_class();
	bool dataReady();
	uint8_t recieveByteBlocking();
};
extern SPI_class SPI;

#endif /* SPI_H_ */
