/*
 * ThreadingTest.cpp
 *
 *  Created on: May 12, 2012
 *      Author: ddalex
 */

#include "ThreadingTest.h"

#include <stdio.h>

void *ThreadingTest::run() {
	unsigned long long i = 0;
	while (runState == lemon::Thread::STATE_RUNNING)
	{
		usleep(10000);
		printf("Running %d: %llu\n", id, i++);
	}
	return NULL;
}
