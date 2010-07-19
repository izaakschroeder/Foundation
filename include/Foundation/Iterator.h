/**
 * Iterator.h
 * @author Izaak Schroeder
 */

#ifndef _I_ITERATOR_H_
#define _I_ITERATOR_H_

#include "Core.h"
	

namespace I
{
	template <class T> class Iterator 
	{
	public:
		virtual T& Current() const = 0;
		virtual void Next() = 0;
		virtual bool Valid() const = 0;
		T& operator *() { return Current(); }
		void operator ++() { Next(); }
	};
};
#endif