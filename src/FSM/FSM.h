/*
 * FSM.h
 *
 *  Created on: 17 февр. 2018 г.
 *      Author: Mikhail
 */

#ifndef FSM_FSM_H_
#define FSM_FSM_H_

#include "FsmNode.h"

class FSM {
private:
	FsmNode* current;
public:
	FSM();
	void run(void);
	FsmNode* getCurrentNode(void);
};

#endif /* FSM_FSM_H_ */
