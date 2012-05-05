/*
 * NetBinder.cpp
 *
 *  Created on: Apr 30, 2012
 *      Author: ddalex
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "NetBinder.h"
#include "NetManager.h"
#include "NetConnection.h"

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
	struct sockaddr_in my_addr, peer_addr;
	socklen_t peer_addr_size;

	int mysocket, retval;
	// set up listening

	mysocket = socket(AF_INET, SOCK_STREAM, 0);

	if (mysocket == -1) {
		runState = STATE_STOPPED;
		EXCEPTION(strerror(errno));
	}

	memset( &my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(localport);
	// my_addr.sin_addr is already set to 0.0.0.0
	// TODO: add sin_addr capability

	if (-1 == bind(mysocket, (const struct sockaddr*)&my_addr, sizeof(my_addr))) {
		runState = STATE_STOPPED;
		EXCEPTION(strerror(errno));
	}

	if (-1 == listen(mysocket, 128)) {	// horrible, horrible magic number
		runState = STATE_STOPPED;
		EXCEPTION(strerror(errno));
	}


	// while running
	while (runState == STATE_RUNNING)
	{
		// accept connections
		retval = accept(mysocket, (struct sockaddr*)&peer_addr, &peer_addr_size);
		if (retval == -1)
		{
			fprintf(stderr, "Error accepting socket: %s", strerror(errno));
			continue;
		}
		// we have the connection ready
		netmanager->cbNewConnection(new NetConnection(retval, peer_addr, peer_addr_size));
	}

	close(mysocket);

	return NULL;
}

}
