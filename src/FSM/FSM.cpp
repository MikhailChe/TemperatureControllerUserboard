/*
 * FSM.cpp
 *
 *  Created on: 17 февр. 2018 г.
 *      Author: Mikhail
 */

#include "FSM.h"

FsmNode* switchNode(FsmNode* current, FsmNode* next) {
	if (current != nullptr)
		current->NodeExitFunction();
	if (next != nullptr)
		next->NodeEnterFunction();
	return next;
}
FSM::FSM() {
	current = nullptr;
}

void FSM::run(void) {
	FsmNode& newNode = current->NodeSwitchFunction();
	if (&newNode != current) {
		current = switchNode(current, &newNode);
	}
}

FsmNode* FSM::getCurrentNode(void) {
	return current;
//	return NULL;
}
