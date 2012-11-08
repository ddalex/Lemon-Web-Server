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
	ThreadingTest(int id = 0) : id(id) {}
	virtual ~ThreadingTest() {}

private:
	int id;
	virtual void *run();
};

#endif /* THREADINGTEST_H_ */
