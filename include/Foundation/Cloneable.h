/**
 * Cloneable.h
 * @author Izaak Schroeder
 */

#ifndef _I_CLONEABLE_H_
#define _I_CLONEABLE_H_

namespace I
{
	template <class T> class Cloneable {
	public:
		virtual T* Clone() const = 0;
	};
};

#endif

