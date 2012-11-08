#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>

#include "LockingQueue.h"
#include "LockedElement.h"
#include "Exception.h"
using namespace lemon;

#define NUM_THREADS	100
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
		usleep(27);
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
			usleep(47);
			pthread_mutex_lock(&marker_mutex);
			marker[(long unsigned int)le->GetPayload()]--;
			pthread_mutex_unlock(&marker_mutex);

			delete le;
	} while (i < NUM_TESTS);
	return NULL;
}

int test_proc()
{
	int id = 0;
	int retval = 0;
	pthread_t producer[NUM_THREADS], consumer[NUM_THREADS];


	for (id = 0; id < NUM_TESTS * NUM_THREADS; id++)
			marker[id] = 0;

	int max_producer_thread_no, max_consumer_thread_no;
	for (id = 0; id < NUM_THREADS; id++) {
		int error;

		if (0 != (error = pthread_create(&producer[id], NULL, creator, (void *)id))) {
			std::cerr << "failed creating producer thread " << id << ": " << strerror(error) << std::endl;
			memset(&producer[id], 0, sizeof(pthread_t));
		}
		else
			max_producer_thread_no = id;
		if (0 != (error = pthread_create(&consumer[id], NULL, destroyer, (void *)id))) {
			std::cerr << "failed creating consumer thread " << id << ": " << strerror(error) << std::endl;
			memset(&consumer[id], 0, sizeof(pthread_t));
		}
		else
			max_consumer_thread_no = id;
	}

	std::cout << "Created " << max_producer_thread_no << " producers and " << max_consumer_thread_no << " consumers" << std::endl;

	for (id = 0; id < max_producer_thread_no; id++) {
		int error;
		pthread_t nullthread;
		memset(&nullthread, 0, sizeof(pthread_t));
		if ((memcmp(&nullthread, &producer[id], sizeof(pthread_t)) != 0) && 0 != (error = pthread_join(producer[id], NULL))) {
			std::cerr << "failed joining producer thread " << id << ": " << strerror(error) << std::endl;
		}
	}

	std::cout << "Done with producers, " << queue.GetSize() << " elements remaining " << std::endl;
	while (queue.GetSize() != 0) usleep(10);


	for (id = 0; id < max_consumer_thread_no; id++) {
		int error;
		pthread_t nullthread;
		memset(&nullthread, 0, sizeof(pthread_t));
		if ((memcmp(&nullthread, &consumer[id], sizeof(pthread_t)) != 0) && 0 != (error = pthread_join(consumer[id], NULL))) {
	    	std::cerr << "failed joining consumer thread " << id << ": " << strerror(error) << std::endl;
		}
	}


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

