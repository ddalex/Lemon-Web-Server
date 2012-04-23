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

template <class T> class LockingQueue;

template <class T>
class LockedElement {
public:
	LockedElement() {}
	LockedElement(T *payload) { this->payload = payload; }
	virtual ~LockedElement() {}

	/* TODO: find a way to force type compatibility for all payloads */
	void SetPayload(T* payload) { this->payload = payload; }
	T* GetPayload() { return payload; }

private:
	LockedElement *next, *prev;
	T *payload;
	friend class LockingQueue<T>;
};


}

#endif /* LOCKEDELEMENT_H_ */
