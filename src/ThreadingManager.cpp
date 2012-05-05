/*
 * ThreadingManager.cpp
 *
 *  Created on: May 5, 2012
 *      Author: ddalex
 */

#include "ThreadingManager.h"
#include "Thread.h"

namespace lemon {


ThreadingManager * ThreadingManager::manager = NULL;


ThreadingManager::ThreadingManager() {
	// TODO Auto-generated constructor stub

}

ThreadingManager::~ThreadingManager() {
	// TODO Auto-generated destructor stub
}

void ThreadingManager::addManagedThread(Thread *thread) {
	threadSet.insert(thread);
}

void ThreadingManager::removeManagedThread(Thread *thread) {
	threadSet.erase(thread);
}

void ThreadingManager::signalThreadAllStop() {
	std::set<Thread *>::iterator i;
	Thread *p;
	for (i = threadSet.begin(); i != threadSet.end(); i++) {
		p = i.operator *();
		p->Stop();
	}

}

}
