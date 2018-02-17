/*
 * Button.h
 *
 *  Created on: 10 февр. 2018 г.
 *      Author: Mikhail
 */

#ifndef BUTTON_H_
#define BUTTON_H_

class Button {
public:
	Button(int);
	virtual ~Button();
	bool isPressed();
private:
	int but;
};

#endif /* BUTTON_H_ */
