/*
 * Exception.cpp
 *
 *  Created on: Apr 18, 2012
 *      Author: ddalex
 */

#include <stdarg.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <execinfo.h>
#include <cxxabi.h>
#include "Exception.h"

namespace lemon {

Exception::Exception(const char *file, int line) {
	// TODO Auto-generated constructor stub
	desc = "Unknown Exception";
	filename = file;
	lineno = line;
	dump();
}

Exception::Exception(const char *file, int line, const char *s, ...) {
	va_list ap;

	char *printederr;
	va_start(ap, s);
	vasprintf(&printederr, s, ap);
	va_end(ap);
	desc = printederr;
	free(printederr);
	filename = file;
	lineno = line;
	dump();
}

Exception::Exception(const char *file, int line, const std::string s, ...) {
	desc = s;
	filename = file;
	lineno = line;
	dump();
}

Exception::~Exception() {
	// TODO Auto-generated destructor stub
}

void Exception::dump() {
      void *array[32];
	  size_t size;

	  fprintf(stderr, "Error: %s \n      at %s:%d\n\nDumping backtrace:\n", desc.c_str(), filename.c_str(), lineno);
	  // get void*'s for all entries on the stack
	  size = backtrace(array, 32);
	  char **symbols = backtrace_symbols(array, size);

	  for (unsigned int i = 0; i < size; i++ )
		  printDemangledLine(symbols[i]);
//	  backtrace_symbols_fd(array, size, 2);

}

void Exception::printDemangledLine(char *line) {
	int status;
	char *s = strchr(line, '(');

	if (s != NULL)
	{
		*s = '\0';
		printf("%s(", line);
		*s = '(';
		char *end = strchr(s, '+');
		if (end == NULL) {
			printf("%s\n", line);
			return;
		}
		*end = 0;
		char *c = abi::__cxa_demangle(++s, 0, 0, &status);
		*end = '+';
		if (c!=NULL) {
			printf("%s", c);
			printf("%s\n", end);
			free(c);
		}
		else
		{
			printf("%s\n", s);
		}
	}
	else
		printf("%s\n", line );

}

}
