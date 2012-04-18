/*
 * Exception.h
 *
 *  Created on: Apr 18, 2012
 *      Author: ddalex
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <string>

namespace lemon {

class Exception {
public:
	Exception();
	Exception(char *s);
	Exception(std::string s);
	virtual ~Exception();
private:
	std::string desc;
};

}
#endif /* EXCEPTION_H_ */
