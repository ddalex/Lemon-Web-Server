/*
 * ThreadingManager.h
 *
 *  Created on: May 5, 2012
 *      Author: ddalex
 */

#ifndef THREADINGMANAGER_H_
#define THREADINGMANAGER_H_

#include <cstddef>
#include <set>

namespace lemon {

class Thread;

class ThreadingManager {
private:
	ThreadingManager();
	virtual ~ThreadingManager();

	static ThreadingManager* manager;

public:
	static ThreadingManager *getThreadingManager() {
		if (ThreadingManager::manager == NULL)
		{
			ThreadingManager::manager = new ThreadingManager();
		}
		return ThreadingManager::manager;
	}

	void addManagedThread(Thread *thread);

	void removeManagedThread(Thread *thread);

	void signalThreadStop(Thread *thread);

	void signalThreadAllStop();

private:
	std::set<Thread *> threadSet;
};

}

#endif /* THREADINGMANAGER_H_ */
