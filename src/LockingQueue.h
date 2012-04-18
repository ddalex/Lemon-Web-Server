/*
 * LockingQueue.h
 *
 *  Created on: Apr 18, 2012
 *      Author: ddalex
 */

#ifndef LOCKINGQUEUE_H_
#define LOCKINGQUEUE_H_

#include <pthread.h>
#include <semaphore.h>

namespace lemon {

class LockedElement;

class LockingQueue {
public:
	LockingQueue();
	~LockingQueue();

	void Push(LockedElement *t);
	LockedElement* Pop();
	size_t GetSize();
private:
	LockedElement *first, *last;
	size_t 	length;

	LockedElement* doLockedPop();

	pthread_mutex_t opmtx; /* guards queue operations */
	sem_t semtx;
};

}

#endif /* LOCKINGQUEUE_H_ */
