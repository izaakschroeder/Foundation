/*
 *  Set.h
 *  XQL
 *
 *  Created by Izaak Schroeder on 09-11-24.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _SET_H_
#define _SET_H_

#include "Core.h"
#include "Iterable.h"
#include "EqualityComparable.h"
#include "EqualityComparator.h"

namespace I 
{
	template <typename T, template <typename> class EQ = EqualityComparator> class Set : public Iterable<T>, public EqualityComparable<class Set<T,EQ> >
	{
	public:
		virtual unsigned int GetSize() const = 0;
		virtual T& Get(const T& Item) const = 0;
		virtual bool Add(const T& Item) = 0;
		virtual bool Remove(const T& Item) = 0;
		virtual bool Contains(const T& Item) const = 0;
		Set<T,EQ>& operator += (const T& Item) { Add(Item); return *this; };
		Set<T,EQ>& operator -= (const T& Item) { Remove(Item); return *this; };
		
		virtual void Clear() {
			foreach(T, i, *this)
				Remove(i);
			endforeach
		}
		
		virtual bool IsEmpty() const {
			return GetSize() == 0;
		}
		
		virtual bool operator == (const Set<T,EQ>& Other) const {
			if (Other.GetSize() != GetSize())
				return false;
			foreach(T, i, *this)
				if (!Other.Contains(i))
					return false;
			endforeach
			return true;
		};
		
		virtual bool Merge(const Set<T,EQ>& s) {
			bool r = false;
			foreach(T, i, s)
				if (Add(i))
					r = true;
			endforeach
			return r;
		}
		
		virtual bool Merge(const Set<T,EQ>&s, Set<T,EQ>& y) {
			bool r = false;
			foreach(T, i, s)
				if (Add(i))
				{
					y.Add(i);
					r = true;
				}
			endforeach
			return r;
		}
	};
};

#endif