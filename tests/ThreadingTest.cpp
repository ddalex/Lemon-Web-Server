/*
 * ThreadingTest.cpp
 *
 *  Created on: May 12, 2012
 *      Author: ddalex
 */

#include "ThreadingTest.h"

#include <stdio.h>

ThreadingTest::ThreadingTest() {
	// TODO Auto-generated constructor stub

}

ThreadingTest::~ThreadingTest() {
	// TODO Auto-generated destructor stub
}

void *ThreadingTest::run() {
	unsigned long long i = 0;
	while (runState == lemon::Thread::STATE_RUNNING)
	{
		usleep(10000);
		printf("Running %llu\n", i++);
	}
	return NULL;
}
