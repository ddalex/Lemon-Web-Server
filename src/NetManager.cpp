/*
 * NetManager.cpp
 *
 *  Created on: Apr 30, 2012
 *      Author: ddalex
 */

#include "NetManager.h"
#include "NetConnection.h"

namespace lemon {

NetManager::~NetManager() {
	// TODO Auto-generated destructor stub
}

void NetManager::NewConnection(lemon::NetConnection * nc) {
	nc->SetSBRQueue(&rqueue);
}

}
