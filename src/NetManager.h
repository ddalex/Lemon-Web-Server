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

#include "Thread.h"
#include "NetBinder.h"

namespace lemon {

class StreamBuffer;

class NetManager: lemon::Thread {
public:
	NetManager();
	virtual ~NetManager();

	void StartService();

	void cbNewConnection(int fd);
};

}

#endif /* NETMANAGER_H_ */
