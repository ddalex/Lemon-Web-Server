/*
 * NetBinder.h
 *
 *	Provides a utility class that takes listens (blocking) on a port
 *	(and interface?) and returns an open file descriptor.
 *
 *  Created on: Apr 30, 2012
 *      Author: ddalex
 */

#ifndef NETBINDER_H_
#define NETBINDER_H_

#include "Thread.h"



namespace lemon {

class NetManager;

class NetBinder : public Thread {
public:
	NetBinder(NetManager *nm, unsigned short port);
	virtual ~NetBinder();

	void * run(void *);

private:
	NetManager *netmanager;
	unsigned short localport;
};

}

#endif /* NETBINDER_H_ */
