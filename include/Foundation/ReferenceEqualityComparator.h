/*
 * ReferenceEqualityComparator.h
 * @author Izaak Schroeder
 */

#ifndef _I_REFERENCEEQUALITYCOMPARATOR_H_
#define _I_REFERENCEEQUALITYCOMPARATOR_H_

#include "EqualityComparator.h"

namespace I {
	template<typename T> class ReferenceEqualityComparator : public EqualityComparator<T>
	{
	public:
		virtual bool operator() (const T& a, const T& b) const {
			return *a == *b;
		};
	};
};

#endif
