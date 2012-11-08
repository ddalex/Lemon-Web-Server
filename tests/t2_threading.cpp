#define MAX_THREADS 20

#include <stdlib.h>
#include <stdio.h>
#include "ThreadingTest.h"

int main(int argv, char **argc) {
	ThreadingTest t;
	ThreadingTest tx[MAX_THREADS] = { 1, 2 } ;
	int tests = 1;
	int i = 0;

	if (argv >= 2)
		tests = atoi(argc[1]);

	tests = tests < 1 ? 1 : tests > 3 ? 3 : tests;

	printf("Running test %d\n", tests);

	switch (tests) {
	case 1:
		t.Start();
		sleep(1);
		t.Stop();
		break;
	case 2:
		t.Start();
		sleep(1);
		lemon::ThreadingManager::getThreadingManager()->signalThreadAllStop();
		break;
	case 3:
		for (i = 0; i < MAX_THREADS; i++)
		{
			tx[i].Start();
		}
		sleep(1);
		lemon::ThreadingManager::getThreadingManager()->signalThreadAllStop();
		break;
	}
}
