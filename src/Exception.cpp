/*
 * Exception.cpp
 *
 *  Created on: Apr 18, 2012
 *      Author: ddalex
 */

#include "Exception.h"
#include <stdarg.h>
#include <stdio.h>
#include <execinfo.h>


namespace lemon {

Exception::Exception(char *file, int line) {
	// TODO Auto-generated constructor stub
	desc = "Unknown Exception";
	filename = file;
	lineno = line;
	dump();
}

Exception::Exception(char *file, int line, const char *s, ...) {
	va_list ap;
	//std::stringstream ss = std::stringstream(s);
	va_start(ap, s);
	va_end(ap);
	filename = file;
	lineno = line;
	dump();
}

Exception::Exception(char *file, int line, const std::string s) {
	desc = s;
	filename = file;
	lineno = line;
	dump();
}

Exception::~Exception() {
	// TODO Auto-generated destructor stub
}

void Exception::dump() {
      void *array[10];
	  size_t size;

	  fprintf(stderr, "Error: %s at %s:%d\nDumping backtrace:\n", desc.c_str(), filename.c_str(), lineno);
	  // get void*'s for all entries on the stack
	  size = backtrace(array, 10);
	  // print out all the frames to stderr
	  backtrace_symbols_fd(array, size, 2);

}

}
