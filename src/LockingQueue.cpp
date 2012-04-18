/*
 * LockingQueue.cpp
 *
 *  Created on: Apr 18, 2012
 *      Author: ddalex
 */

#include "LockingQueue.h"
#include "LockedElement.h"

#include "Exception.h"
#include <errno.h>
#include <string.h>

namespace lemon {

LockingQueue::LockingQueue() {
	int err = 0;

	first = last = NULL;
	length = 0;
	if (sem_init(&semtx, 0, 0) != 0) {
		throw Exception(strerror(errno));
	}
	err = pthread_mutex_init(&opmtx, NULL);
	if (err != 0) {
		throw Exception(strerror(err));
	}

}

LockingQueue::~LockingQueue() {
	/* cleanly dump all elements, because they won't be consumed by anybody else */
	while (first != last)
		delete Pop();
	sem_destroy(&semtx);
}

/**
 * Adds an element to the end of the queue
 */
void LockingQueue::Push(LockedElement* l) {
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


/**
 * Pull an element from the top of the queue
 * Blocks if things nothing available.
 */
LockedElement* LockingQueue::Pop() {
	LockedElement* l = doLockedPop();

	while (l == NULL) {/* make a bet that we have something */
		sem_wait(&semtx);
		l = doLockedPop();
	}
	return l;
}

LockedElement* LockingQueue::doLockedPop() {

	LockedElement* l = first;
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

size_t LockingQueue::GetSize()
{
	int semval;
	int retval = sem_getvalue(&semtx, &semval);
	if (retval != 0)
		throw Exception(strerror(retval));
	if ((unsigned int)semval != length)
		throw Exception(std::string("Inconsistent semaphore"));
	return length;
}

}
