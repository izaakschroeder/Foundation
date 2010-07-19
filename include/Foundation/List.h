/*
 *  List.h
 *  XQL
 *
 *  Created by Izaak Schroeder on 09-11-24.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _LIST_H_
#define _LIST_H_

#include <Foundation/Core.h>
#include <Foundation/Iterable.h>
#include <Foundation/EqualityComparable.h>
#include <Foundation/EqualityComparator.h>
#include <Foundation/MutableIterator.h>

namespace I 
{
	template <typename T, template<typename> class KC = EqualityComparator> class List : public Iterable<T>, public EqualityComparable<class List<T,KC> >
	{
	
	public:
		virtual unsigned int GetSize() const = 0;
		virtual T& operator [] (unsigned int index) const = 0;
		virtual bool IsEmpty() const = 0;
		virtual void Append(const T& Item) = 0;
		virtual void Insert(const T& Item, unsigned int Position = 0) = 0;
		virtual void Remove(unsigned int Position) = 0;
		virtual void Clear() = 0;
		virtual unsigned int IndexOf(const T&Item) const {
			for (unsigned int i=0; i<GetSize(); ++i)
				if ((KCmp)((*this)[i], Item))
					return i;
			throw Error();
		};
		
		virtual List<T,KC>* Slice(unsigned int) const = 0;
		virtual const List<T,KC>* Window(unsigned int) const = 0;
		
		virtual bool operator == (const List<T,KC>& Other) const {
			if (GetSize() != Other.GetSize())
				return false;
			for (unsigned int i=0; i<GetSize(); ++i)
				if (((KCmp)((*this)[i], Other[i])) == false)
					return false;
			return true;
		}
		
		virtual MutableIterator<T>* GetMutableIterator() = 0;
				
	protected:
		
		
		
		KC<T> KCmp;
		//virtual List<T> operator + (const List<T>&) const = 0;
	};
};

#endif