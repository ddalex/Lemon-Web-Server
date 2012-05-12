#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "LockingQueue.h"
#include "LockedElement.h"
#include "Exception.h"
using namespace lemon;

#define NUM_THREADS	4000
#define NUM_TESTS	1000

LockingQueue<void> queue;

unsigned short int 	marker[NUM_TESTS*NUM_THREADS];
pthread_mutex_t 	marker_mutex = PTHREAD_MUTEX_INITIALIZER;

void* creator(void *ptr)
{
	int id = (long unsigned int) ptr;
	int i;
	srand(0);
	for (i = 0; i < NUM_TESTS; i++ )
	{
		LockedElement<void> *le = new LockedElement<void>((void *)(id*NUM_TESTS+i));
		queue.Push(le);

		pthread_mutex_lock(&marker_mutex);
		marker[id*NUM_TESTS+i] ++;
		pthread_mutex_unlock(&marker_mutex);
	}
	return NULL;
}

void* destroyer(void *ptr)
{
	int i = 0;
	do {
		    LockedElement<void> *le = queue.Pop();
			i++;
			pthread_mutex_lock(&marker_mutex);
			marker[(long unsigned int)le->GetPayload()]--;
			pthread_mutex_unlock(&marker_mutex);

			delete le;
	} while (i < NUM_TESTS);
}

int test_proc()
{
	int id = 0;
	int retval = 0;
	pthread_t producer[NUM_THREADS], consumer[NUM_THREADS];


	for (id = 0; id < NUM_TESTS * NUM_THREADS; id++)
			marker[id] = 0;

	for (id = 0; id < NUM_THREADS; id++) {
		pthread_create(&producer[id], NULL, creator, (void *)id);
		pthread_create(&consumer[id], NULL, destroyer, (void *)id);
	}

	for (id = 0; id < NUM_THREADS; id++) {
		pthread_join(producer[id], NULL);
	    pthread_join(consumer[id], NULL);
	}

	if (queue.GetSize() != 0)
		EXCEPTION("Queue not consumed");

	for (id = 0; id < NUM_TESTS * NUM_THREADS; id++)
		if (marker[id] != 0) {
			fprintf(stderr, "test failed: element id %d val %d\n", id, marker[id]);
			retval ++;
		}

	return retval;
}

int main(int argc, char**argv)
{
	return test_proc();
}

