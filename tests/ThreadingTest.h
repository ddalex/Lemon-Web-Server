/*
 * ThreadingTest.h
 *
 *  Created on: May 12, 2012
 *      Author: ddalex
 */

#ifndef THREADINGTEST_H_
#define THREADINGTEST_H_

#include "Thread.h"

class ThreadingTest : public lemon::Thread {
public:
	ThreadingTest();
	virtual ~ThreadingTest();

private:
	virtual void *run();
};

#endif /* THREADINGTEST_H_ */
