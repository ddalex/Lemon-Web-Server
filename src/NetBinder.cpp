/*
 * NetBinder.cpp
 *
 *  Created on: Apr 30, 2012
 *      Author: ddalex
 */

#include "NetBinder.h"
#include "NetManager.h"

namespace lemon {

NetBinder::NetBinder(NetManager *nm, unsigned short port) {
	// TODO Auto-generated constructor stub
	netmanager = nm;
	localport = port;
}

NetBinder::~NetBinder() {
	// TODO Auto-generated destructor stub
}

void * NetBinder::run(void *) {

}

}
