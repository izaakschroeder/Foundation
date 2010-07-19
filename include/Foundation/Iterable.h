/**
 * Iterable.h
 * @author Izaak Schroeder
 */

#ifndef _I_ITERABLE_H_
#define _I_ITERABLE_H_

#include <Foundation/Core.h>
#include <Foundation/Iterator.h>

#define _foreachvar(var) TOKENPASTE2(__i##var, __LINE__)
#define _foreachvar2(var) TOKENPASTE2(__iptr##var, __LINE__)

#define iterate(type, var, obj) \
for(type& var = *(obj); var.Valid() ? true : (delete &var, false); var.Next())

#define foreach(type, var, obj) \
for( \
	I::Iterator<type>* _foreachvar(var) = (obj).GetIterator(); \
	_foreachvar(var)->Valid() ? true : (delete _foreachvar(var), false); \
	_foreachvar(var)->Next() \
) { \
	type& var = **_foreachvar(var); 

#define endforeach }


namespace I
{
	template <class T> class Iterable 
	{
	public:
		virtual Iterator<T>* GetIterator() const = 0;
	};
};

#endif
