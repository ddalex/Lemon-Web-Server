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

#include <errno.h>
#include <string.h>

#include "Exception.h"

namespace lemon {

template <class T> class LockedElement;

template <class T>
class LockingQueue {
public:
	LockingQueue() {
		int err = 0;

		first = last = NULL;
		length = 0;
		if (sem_init(&semtx, 0, 0) != 0) {
			EXCEPTION(strerror(errno));
		}
		err = pthread_mutex_init(&opmtx, NULL);
		if (err != 0) {
			EXCEPTION(strerror(err));
		}

	}

	~LockingQueue() {
		/* cleanly dump all elements, because they won't be consumed by anybody else */
		while (GetSize() > 0)
			delete Pop();
		sem_destroy(&semtx);
	}

	void Push(LockedElement<T> *l)  {
		pthread_mutex_lock(&opmtx);
		l->prev = last;
		l->next = NULL;
		if (last != NULL) {
			last->next = l;
		}
		if (first == NULL) {
			first = l;
		}
		last = l;
		length ++;
		sem_post(&semtx);
		pthread_mutex_unlock(&opmtx);
	}

	LockedElement<T>* Pop() {
		LockedElement<T>* l = doLockedPop();

		while (l == NULL) {/* make a bet that we have something */
			sem_wait(&semtx);
			l = doLockedPop();
		}
		return l;
	}


	size_t GetSize() {
		int semval;
		int retval = sem_getvalue(&semtx, &semval);
		if (retval != 0)
			EXCEPTION(strerror(retval));
		if ((unsigned int)semval != length)
			EXCEPTION("Inconsistent semaphore: %d length %d semval", length, semval);
		return length;
	}

private:
	LockedElement<T> *first, *last;
	size_t 	length;

	LockedElement<T>* doLockedPop() {
		LockedElement<T>* l = first;
		if (l == NULL) return l;

		pthread_mutex_lock(&opmtx);
		if (first == last)
			last = NULL;
		first = l->next;
		if (first != NULL)
			first->prev = NULL;
		l->prev = NULL;
		l->next = NULL;
		length --;
		pthread_mutex_unlock(&opmtx);

		return l;
	}


	pthread_mutex_t opmtx; /* guards queue operations */
	sem_t semtx;
};

}

#endif /* LOCKINGQUEUE_H_ */
