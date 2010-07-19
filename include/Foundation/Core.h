/*
 *  Core.h
 *  XQL
 *
 *  Created by Izaak Schroeder on 09-11-24.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _CORE_H_
#define _CORE_H_


#include <stdlib.h>
#include <string>


namespace I {
	typedef std::string String;
	typedef int NullType;
	static const NullType Null = 0;
};

#include "Error.h"

#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
#define TOSTR(x) #x
#define TOSTR2(x) TOSTR(x)

#endif
