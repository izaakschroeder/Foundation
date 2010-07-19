/*
 * EqualityComparable.h
 * @author Izaak Schroeder
 */

#ifndef _I_EQUALITYCOMPARABLE_H_
#define _I_EQUALITYCOMPARABLE_H_

#include <Foundation/Core.h>

namespace I {
	template<typename T> class EqualityComparable
	{
	public:
		virtual bool operator==(const T &Other) const = 0;
		virtual bool operator != (const T& Other) const { return !(*this == Other); }
		
	};
	
	class NullComparable : public EqualityComparable<NullType>
	{
		bool operator == (const NullType& Other) const { 
			return false;
		};
	};
};

#endif