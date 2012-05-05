/*
 * NetManager.h
 *
 *	Tackles the creation and management of the network
 *	interface threads. It will run a number of Binders
 *	and Receivers as specified in the config file. Currently
 *	hardcodes.
 *
 *  Created on: Apr 30, 2012
 *      Author: ddalex
 */

#ifndef NETMANAGER_H_
#define NETMANAGER_H_
#include "LockingQueue.h"
#include "StreamBuffer.h"
#include "Thread.h"

namespace lemon {

class NetConnection;


class NetManager: lemon::Thread {
public:
	NetManager(StreamBufferQueue q) : rqueue(q) {}
	virtual ~NetManager();

	void StartService();

	void NewConnection(NetConnection *nc);

private:
	StreamBufferQueue rqueue;
};

}

#endif /* NETMANAGER_H_ */
