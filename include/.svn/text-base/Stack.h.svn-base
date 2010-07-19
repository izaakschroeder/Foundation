/*
 *  Stack.h
 *  XQL
 *
 *  Created by Izaak Schroeder on 09-11-24.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _STACK_H_
#define _STACK_H_

#include "Core.h"

namespace I 
{
	template <typename T> class Stack 
	{
	public:
		virtual unsigned int GetSize() const = 0;
		virtual T& Pop() = 0;
		virtual T& Peek() const = 0;
		virtual void Push(const T& item) = 0;
		virtual bool IsEmpty() const = 0;
		virtual void Clear() = 0;
	};
};

#endif