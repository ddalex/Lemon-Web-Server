#define MAX_THREADS 20

#include <stdio.h>
#include "ThreadingTest.h"

int main(int argv, char **argc) {
	ThreadingTest t;
	ThreadingTest tx[MAX_THREADS];
	int tests = 3;
	int i = 0;

	switch (tests) {
	case 1:
		t.Start();
		sleep(1);
		t.Stop();
		printf("----------\n");
	case 2:
		t.Start();
		sleep(1);
		lemon::ThreadingManager::getThreadingManager()->signalThreadAllStop();
		printf("----------\n");
	case 3:
		for (i = 0; i < MAX_THREADS; i++)
		{
			tx[i].Start();
		}
		sleep(1);
		lemon::ThreadingManager::getThreadingManager()->signalThreadAllStop();
	}
}
