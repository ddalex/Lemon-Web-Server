/*
 * Exception.h
 *
 *  Created on: Apr 18, 2012
 *      Author: ddalex
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <string>
#include <iostream>

#define EXCEPTION(X...)   do {\
	throw Exception(__FILE__, __LINE__, X); \
	} while (1 == 0);

namespace lemon {

class Exception {
public:
	Exception(const char *file, int line);
	Exception(const char *file, int line, const char *s, ...);
	Exception(const char *file, int line, const std::string s, ...);
	virtual ~Exception();
private:
	std::string desc;
	std::string filename;
	unsigned int lineno;
	void dump();
	void printDemangledLine(char *line);
};

}
#endif /* EXCEPTION_H_ */
