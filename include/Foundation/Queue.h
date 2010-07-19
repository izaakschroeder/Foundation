/*
 *  Queue.h
 *  XQL
 *
 *  Created by Izaak Schroeder on 09-11-24.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "Core.h"
#include "EqualityComparable.h"
#include "Iterable.h"

namespace I 
{
	template <typename T> class Queue : public Iterable<T>
	{
	public:
		virtual unsigned int GetSize() const = 0;
		virtual T& Pop() = 0;
		virtual T& Peek() const = 0;
		virtual void Push(const T& item) = 0;
		virtual bool IsEmpty() const {
			return GetSize() == 0;
		};
		virtual void Clear() = 0;
	};
};

#endif