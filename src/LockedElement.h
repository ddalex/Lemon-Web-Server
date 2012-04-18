/*
 * LockedElement.h
 *  Defines a type of element that can be stored in a LockedQueue.
 *
 *  The LockedQueue can look inside the element in order to efficientize the operations.
 *  Created on: Apr 18, 2012
 *      Author: ddalex
 */

#ifndef LOCKEDELEMENT_H_
#define LOCKEDELEMENT_H_

namespace lemon {

class LockedElement {
public:
	LockedElement();
	virtual ~LockedElement();

	/* TODO: find a way to force type compatibility for all payloads */
	void SetPayload(void* payload);
	void* GetPayload();

private:
	LockedElement *next, *prev;

	friend class LockingQueue;
};


}

#endif /* LOCKEDELEMENT_H_ */
