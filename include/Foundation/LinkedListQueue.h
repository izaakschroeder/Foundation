/**
 *  LinkedListQueue.h
 *  @author Izaak Schroeder
 */

#include <Foundation/LinkedList.h>
#include <Foundation/ListQueue.h>

namespace I
{
	template <typename T> class LinkedListQueue : public ListQueue<LinkedList,T>
	{
		
	};
};