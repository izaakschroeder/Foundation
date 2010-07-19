
#ifndef _I_READABLE_H_
#define _I_READABLE_H_

namespace I 
{
	template<class T> class Readable : public Stream
	{
	public:
		Readable() : Stream() { }
		Readable(const Readable<T>& r) : Stream(r) { }
		virtual T Read() = 0;
	};
};

#endif
