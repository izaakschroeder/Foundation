/*
 *  Error.h
 *  XQL
 *
 *  Created by Izaak Schroeder on 09-11-24.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _ERROR_H
#define _ERROR_H

namespace I {
	
	
	
	class Error {
		
	};
	
	class OutOfBoundsError : public Error {
	public:
		unsigned int Index;
		OutOfBoundsError(unsigned int i) : Index(i) { }
	};
	
	class KeyNotFoundError : public Error {
		
	};
};

#endif