/**
 * HashSet.h
 * @author Izaak Schroeder
 */

#ifndef _HASHSET_H_
#define _HASHSET_H_

#include <Foundation/EqualityComparator.h>
#include <Foundation/Hashable.h>
#include <Foundation/HashMap.h>
#include <Foundation/MapSet.h>
#include <cstdarg>

namespace I
{
	template <typename T, template<typename> class C = EqualityComparator, class H = HashableHashGenerator<T> > class HashSet 
		: public MapSet< HashMap<T,T,C,H> , T, C>
	{
	public:
		
		HashSet()  : MapSet< HashMap<T,T,C,H> , T, C>() {
			
		}
		
		HashSet(const HashSet<T,C,H>& Other) : MapSet< HashMap<T,T,C,H> , T, C>() 
		{
			foreach(T, i, Other)
				Add(i);
			endforeach
		}
		
		HashSet(const Set<T,C>& Other) : MapSet< HashMap<T,T,C,H> , T, C>() 
		{
			foreach(T, i, Other)
				Add(i);
			endforeach
		}
		
		HashSet<T, C, H>& operator = (const HashSet<T, C, H>& Other)
		{
			MapSet< HashMap<T,T,C,H> , T, C>::operator = (Other);
			return *this;
		}
		
		HashSet<T, C, H>& operator = (const Set<T, C>& Other)
		{
			MapSet< HashMap<T,T,C,H> , T, C>::operator = (Other);
			return *this;
		}
		
		static HashSet<T,C,H> FromValues(const T& first, ...) {
			va_list ap;
			HashSet<T,C,H> r;
			va_start(ap, first);
			for (const T& i = first; &i != NULL; va_arg(ap, const T&))
				r.Add(i);
			return r;
		};
	};
};

#endif