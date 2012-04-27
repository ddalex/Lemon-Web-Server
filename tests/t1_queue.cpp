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
	for (i = 0; i < 50; i++ )
	{
		LockedElement<void> *le = new LockedElement<void>;
		le->SetPayload((void *)i);
		queue.Push(le);
		printf("Pushed %lx! %x\n", (long unsigned int) ptr, i);
		usleep(1);
	}
	return NULL;
}

void* destroyer(void *ptr)
{
	int i = 0;
	do {
		    LockedElement<void> *le = queue.Pop();
			printf("Popped %lx! %lx ", (long unsigned int) ptr, (long unsigned int)le->GetPayload());
			printf("size: %lu\n", queue.GetSize());
			delete le;
			i++;
			usleep(1);
	} while (i < 50);
}

int main(int argc, char**argv)
{
	pthread_t producer[2], consumer[2];
	pthread_create(&producer[0], NULL, creator, (void *)1);
	pthread_create(&producer[1], NULL, creator, (void *)2);
    pthread_create(&consumer[0], NULL, destroyer, (void *)1);
    pthread_create(&consumer[1], NULL, destroyer, (void *)2);
    pthread_join(producer[0], NULL);
    pthread_join(producer[1], NULL);
    pthread_join(consumer[0], NULL);
    pthread_join(consumer[1], NULL);
	return 0;
}

