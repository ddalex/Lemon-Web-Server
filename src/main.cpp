#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "LockingQueue.h"
#include "LockedElement.h"
#include "Exception.h"
using namespace lemon;


LockingQueue<void> queue;

void* creator(void *ptr)
{
	int i;
	srand(0);
	for (i = 0; i < 10; i++ )
	{
		sleep(1);
		queue.Push(new LockedElement<void>);
		printf("Pushed!\n");
		queue.Push(new LockedElement<void>);
		printf("Pushed!\n");
		queue.Pop();
	}
	return NULL;
}

int main(int argc, char**argv)
{
	pthread_t producer;
	pthread_create(&producer, NULL, creator, NULL);
	do {
		queue.Pop();
		printf("size: %d\n", queue.GetSize());
	} while (true);
	return 0;
}

