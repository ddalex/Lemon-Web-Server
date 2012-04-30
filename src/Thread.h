/*
 * Thread.h
 *
 *  Created on: Apr 30, 2012
 *      Author: ddalex
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

#include "Exception.h"

void * __run_helper(void *p);

namespace lemon {

class Thread {
public:
	inline Thread() {}
	inline virtual ~Thread() {}
	inline void start() { pthread_create( &mythread, NULL, &__run_helper, this);  }

public:
	virtual void * run() = 0;

private:
	void *ptr;
	void *result;
	pthread_t mythread;

	inline void *wait()
	{
		pthread_join(mythread, &result);
		return result;
	}
};

static inline void * __run_helper(void *p) {
	lemon::Thread *thread = (lemon::Thread*)(p);
	// safety check
	lemon::Thread *safe = dynamic_cast<lemon::Thread*>(thread);
	if (safe == NULL)
		EXCEPTION("Trying to run something that is not lemon::Thread");
	return thread->run();
}

}


#endif /* THREAD_H_ */
