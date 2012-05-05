/*
 * NetConnection.h
 *
 *  Created on: May 5, 2012
 *      Author: ddalex
 */

#ifndef NETCONNECTION_H_
#define NETCONNECTION_H_

#include <netinet/in.h>
#include <netinet/ip.h>
#include "StreamBuffer.h"

namespace lemon {

class NetConnection {
public:
	NetConnection(int f, struct sockaddr_in &s, socklen_t l) : sb(f) {
		fd = f;
		peer_addr = s;
		peer_addr_size = l;
	}
	virtual ~NetConnection();

	void SetSBRQueue(StreamBufferQueue *s) {
		sb.RegisterReadQueue(s);
	}

private:
	int fd;
	struct sockaddr_in peer_addr;
	socklen_t peer_addr_size;

	StreamBuffer sb;
};

}

#endif /* NETCONNECTION_H_ */
