/*
 * StreamBuffer.cpp
 *
 *  Created on: Apr 30, 2012
 *      Author: ddalex
 */

#include "StreamBuffer.h"
#include "Exception.h"
#include "errno.h"

namespace lemon {

StreamBuffer::StreamBuffer() : thiselement(this) {
	EXCEPTION("StreamBuffer must be called with the proper open file descriptor and read queue");
}

StreamBuffer::~StreamBuffer() {
	// TODO Auto-generated destructor stub
}

void StreamBuffer::NetRead() {
	int size;		// how much we read
	int maxsize;	// how much space do we have

	// we take two tries; first rspp to end, and if
	// rspp takes over the end, begin to rsrp.

	pthread_mutex_lock(&readmtx);
	maxsize = BUFFERSIZE - rspp;
	size = read(fd, readbuffer+rspp, maxsize);
	if (size == -1)	goto nrexit;
	rspp += size;

	if (rspp >= BUFFERSIZE && rsrp > 0) {	// we're full, but have space at the beginning
		rspp = 0;
		maxsize = rsrp-1;
		size = read(fd, readbuffer, maxsize);
		if (size == -1)	goto nrexit;
		rspp += size;
	}
	// we got data to parse
	rqueue->Push(thiselement);

nrexit:
	pthread_mutex_unlock(&readmtx);

	if (size == -1)
	{
		switch (errno){
		case EAGAIN:
		case EWOULDBLOCK:
				break;
		case EBADF:
		case EIO:
				Close();
		default:
			EXCEPTION(strerror(errno));
		}
	}
}

void StreamBuffer::NetWrite() {
	int size;

	pthread_mutex_lock(&writemtx);
	// first wrap around the buffer
	if (wspp < wsrp) {
		while (wsrp < BUFFERSIZE) {
			size = write(fd, writebuffer + wsrp, BUFFERSIZE - wsrp);
			if (size == -1) goto nwexit; // TODO: handle errors gracefully
			wsrp += size;
		}
		wsrp = 0;
	}

	while (wsrp < wspp) { // straight forward write, start pointer is lower than stop pointer
		size = write(fd, writebuffer + wsrp, wspp - wsrp);
		if (size == -1) goto nwexit; // TODO: handle errors gracefully
		wsrp += size;
	}

nwexit:
	pthread_mutex_unlock(&writemtx);
	if (size == -1)
	{
		switch (errno){
		case EAGAIN:
		case EWOULDBLOCK:
				break;
		case EBADF:
		case EIO:
				Close();
		default:
			EXCEPTION(strerror(errno));
		}
	}
}

void StreamBuffer::NetFlush() {
	// NOOP implementation since we disregard limits, so far....
}

void NetClose()
{
	close(fd);
}



void StreamBuffer::WriteBytes(int size, char* buffer) {
	int sentsize, start = 0;
	if (wqueue)	{ // queue data for deferred sending; it will be sent by NetWrite;
	}
	else { // send straight away
		do {
			sentsize = write(fd, buffer + start, size);
			start += sentsize;
			size  -= sentsize;
		} while (size > 0 && sentsize > 0);
	}
}



void StreamBuffer::ReadLn() {
	int rp;
	int s = 0;
	register char x;
	enum { ST_LINE, ST_END } readstate = ST_LINE;

	pthread_mutex_lock(&readmtx);
	for (rp = rsrp; rp != rspp; rp++)
	{
		if (rp == BUFFERSIZE) rp = 0;

		x = readbuffer[rp];
		switch(readstate) {
		case ST_LINE:
			if ( x == '\r' || x == '\n') { readstate = ST_END; }
		case ST_END:
			linebuffer[s] = x;
			s++;
			if ( x != '\r' || x != '\n') { goto rlexit; }
		}
	}
rlexit:
	pthread_mutex_unlock(&readmtx);
	if (s > 0 && readstate == ST_END)
	{
		linebuffer[s++] = 0;
		return linebuffer;
	}
	else
		return NULL;
}

}
