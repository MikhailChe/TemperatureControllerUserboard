/*
 * FsmNode.h
 *
 *  Created on: 17 февр. 2018 г.
 *      Author: Mikhail
 */

#ifndef FSM_FSMNODE_H_
#define FSM_FSMNODE_H_

class FsmNode {
protected:
	FsmNode() {
	}
	virtual ~FsmNode() {
	}
public:
	virtual void NodeEnterFunction(void);
	virtual void NodeExitFunction(void);

	virtual FsmNode& NodeSwitchFunction(void);
};

#endif /* FSM_FSMNODE_H_ */
