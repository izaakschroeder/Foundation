
#ifndef _I_READFILTER_H_
#define _I_READFILTER_H_

#include <Foundation/include/StreamFilter.h>
#include <Foundation/include/Readable.h>

namespace I
{
	template <class OutputType, class InputType = OutputType> class ReadFilter : public StreamFilter< Readable<InputType> >, public Readable<OutputType>
	{
	public:
		ReadFilter(const ReadFilter<OutputType, InputType>& Other) : StreamFilter< Readable<InputType> >(Other), Readable<OutputType>(Other) { }
		ReadFilter(Readable<InputType>& Source) : StreamFilter< Readable<InputType> >(Source), Readable<OutputType>() { }
		virtual OutputType Read() = 0;
	};
};

#endif
