/**
 * ListStack.h
 * @author Izaak Schroeder
 */


#ifndef _LISTSTACK_H_
#define _LISTSTACK_H_

#include <Foundation/List.h>
#include <Foundation/Stack.h>

namespace I 
{
	template <template<typename, template <typename> class> class LT, typename T, template<typename> class KC = EqualityComparator> class ListStack : public Stack<T>
	{
	public:
		ListStack() : Stack<T>() 
		{ 
		
		};
		ListStack(const ListStack<LT, T>& Other) : Data(Other.Data)
		{ 
			
		};
		
		virtual ~ListStack() 
		{
			
		};
		
		bool IsEmpty() const
		{
			return Data.IsEmpty();
		}
		
		unsigned int GetSize() const 
		{
			return Data.GetSize();
		};
		
		T& Pop() 
		{
			const unsigned int i = Data.GetSize()-1;
			T& tmp = Data[i];
			Data.Remove(i);
			return tmp;
		};
		
		T& Peek() const
		{
			return Data[Data.GetSize()-1];
		}
		
		void Push(const T& item)
		{
			Data.Append(item);
		};
		
		void Clear()
		{
			Data.Clear();
		}
		
	private:
		LT<T,KC> Data;
	};
};

#endif