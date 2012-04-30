/*
 * NetReceiver.h
 *
 *	Implements a epoll-based waiter that blocks on read on opened FDs,
 *	and on resume, posts an event to the reading queue.
 *  Created on: Apr 30, 2012
 *      Author: ddalex
 */

#ifndef NETRECEIVER_H_
#define NETRECEIVER_H_

#include <map>
#include "Thread.h"

namespace lemon {

class NetManager;
class StreamBuffer;

class NetReceiver : Thread {
public:
	NetReceiver(NetManager *nm);
	virtual ~NetReceiver();

	void AddConnection(int fd, StreamBuffer *sb);


	void * run(void *);

private:
	NetManager *netmanager;
	std::map<int, StreamBuffer *> map;
};

}

#endif /* NETRECEIVER_H_ */
