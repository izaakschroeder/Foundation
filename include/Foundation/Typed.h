#ifndef _I_TYPED_H_
#define _I_TYPED_H_

#include <typeinfo>

namespace I {
	class Typed {
	public:
		virtual const std::type_info* GetTypeInfo() const = 0;
	}
}

#endif