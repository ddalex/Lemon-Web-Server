/*
 * StreamBuffer.h
 *
 *	Implements a buffer abstraction over a file-descriptor.
 *	Each class provides a pointer and size for read()/write()
 *	POSIX functions, and offers a ReadLn() / Write(bytes)
 *
 *
 *  Created on: Apr 30, 2012
 *      Author: ddalex
 */

#ifndef STREAMBUFFER_H_
#define STREAMBUFFER_H_


#include "LockingQueue.h"
#include "LockedElement.h"

/**
 * The default buffer size for input and output.
 *
 */
#define BUFFERSIZE		4*1024

/**
 * The minimum free size on which read/writes are
 * performed in absence of a Flush() call.
 */

#define LIMITSIZE		256

namespace lemon {

class StreamBuffer;

typedef LockingQueue<StreamBuffer> StreamBufferQueue;
typedef LockedElement<StreamBuffer> StreamBufferElement;


class StreamBuffer {
public:
	StreamBuffer(unsigned int fd, StreamBufferQueue *rqueue = NULL, StreamBufferQueue *wqueue = NULL) : thiselement(this)
	{
		int err = 0;
		this->fd = fd;
		this->rqueue = rqueue;
		this->wqueue = wqueue;
		rsrp = rspp = rpap = 0;
		wsrp = wspp = wpap = 0;

		// clear the mutexes
		err = pthread_mutex_init(&readmtx, NULL);
				if (err != 0) {
					EXCEPTION(strerror(err));
				}
		err = pthread_mutex_init(&writemtx, NULL);
				if (err != 0) {
					EXCEPTION(strerror(err));
				}

		// we're our own lord
	}

	virtual ~StreamBuffer();

	/**
	 * Receives data from the network; silently refuses to do so
	 * if less than LIMITSIZE bytes are available in the buffer
	 */
	void NetRead();

	/**
	 * Writes data from buffers to the network; silently refuses to do so
	 * if there are less than LIMITSIZE bytes available; may be forced
	 * by a NetFlush().
	 */
	void NetWrite();

	/**
	 * Empties the outgoing buffers
	 */
	void NetFlush();

	/**
	 * Reads and returns a pointer to the next full-line ('\r\n' - terminated)
	 * Returns NULL if no such line exists. Must be copied if other processing
	 * is needed. Destroys the internal buffer that was read.
	 */
	char *ReadLn();

	/**
	 * Reads and returns a pointer to the next specified bytes. Returns NULL
	 * if the size requested is not available. Destroys the internal buffer that was read.
	 */
	char *ReadBytes(int size);

	/**
	 * Post bytes in the outgoing buffer. Internally adds itself to all the
	 * write() outgoing queues, if registered.
	 */
	void WriteBytes(int size, char* buffer);

	/**
	 * Flushes the outgoing buffers and closes all connections.
	 */
	void NetClose();

	/** Registers itself to a Queue to which the stream will post a notification
	 * that it read bytes and those needs processing.
	 */
	void RegisterReadQueue(StreamBufferQueue *rqueue);

	/**
	 * Registers (optionally) a Queue to which the stream will post a notification
	 * that it has bytes to send. If empty, it will send straight away.
	 */
	void RegisterWriteQueue(StreamBufferQueue *wqueue);


	/**
	 * Returns number of bytes that are available for processing
	 */
	inline ssize_t GetReadSize() {
		if (rspp > rsrp) return rspp - rsrp;
		else return rspp + BUFFERSIZE - rsrp;
	}

	inline StreamBufferElement GetLockedElement() { return thiselement; }

private:
	int fd;
	pthread_mutex_t readmtx, writemtx;
	char readbuffer[BUFFERSIZE];
	char writebuffer[BUFFERSIZE];
	char linebuffer[BUFFERSIZE];

	unsigned int rsrp, rspp, rpap;	// read start, stop and parser pointers in the read buffer
	unsigned int wsrp, wspp, wpap;	// write start, stop and parser pointers in the write buffer

	LockingQueue<StreamBuffer> *rqueue, *wqueue;

	LockedElement<StreamBuffer> thiselement;

	/**
	 * Only for the special sendfile() handler, you might get a fd pointer.
	 */
	int	GetFD();
};

}

#endif /* STREAMBUFFER_H_ */
