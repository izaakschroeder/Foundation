/**
 *  LinkedListStack.h
 *  @author Izaak Schroeder
 */

#ifndef _I_LINKEDLISTSTACK_H_
#define _I_LINKEDLISTSTACK_H_

#include <Foundation/LinkedList.h>
#include <Foundation/ListStack.h>

namespace I
{
	template <typename T> class LinkedListStack : public ListStack<LinkedList, T>
	{
	};
};

#endif