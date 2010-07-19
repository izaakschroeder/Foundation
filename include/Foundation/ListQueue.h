/*
 *  ListQueue.h
 *  XQL
 *
 *  Created by Izaak Schroeder on 09-11-24.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _LISTQUEUE_H_
#define _LISTQUEUE_H_

#include "Queue.h"
#include "List.h"

namespace I 
{
	template <template <typename, template <typename> class> class LT, typename T, template<typename> class KC = EqualityComparator> class ListQueue : public Queue<T>
	{
	public:
		ListQueue()
		{
			
		};
		
		ListQueue(const ListQueue<LT, T, KC>& Other) : Data(Other.Data)
		{ 
			
		};

		unsigned int GetSize() const
		{
			return Data.GetSize();
		};
		
		bool IsEmpty() const
		{
			return Data.IsEmpty();
		}
		
		T& Pop() 
		{
			T& tmp = Data[0];
			Data.Remove(0);
			return tmp;
		};
		
		T& Peek() const
		{
			return Data[0];
		}
		
		void Push(const T& item)
		{
			Data.Append(item);
		}
		
		Iterator<T>* GetIterator() const 
		{ 
			return Data.GetIterator(); 
		}
		
		void Clear()
		{
			Data.Clear();
		}
		
	private:
		LT<T, KC> Data;
	};
};

#endif
