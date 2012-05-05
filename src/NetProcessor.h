/*
 * MsgProcessor.h
 *
 *  Created on: Apr 30, 2012
 *      Author: ddalex
 */

#ifndef MSGPROCESSOR_H_
#define MSGPROCESSOR_H_

#include "Thread.h"
#include "StreamBuffer.h"

namespace lemon {

class NetProcessor: public lemon::Thread {
public:
	NetProcessor();
	virtual ~NetProcessor();

	LockingQueue<StreamBuffer>	*GetProcessorQueue() { return &eventsQueue; }


private:
	LockingQueue<StreamBuffer>	eventsQueue;
};

}

#endif /* MSGPROCESSOR_H_ */
