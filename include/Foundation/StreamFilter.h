
#ifndef _I_STREAMFILTER_H_
#define _I_STREAMFILTER_H_

#include <Foundation/include/Stream.h>

namespace I
{
	/**
	 * StreamFilter
	 * Class used for manipulating the behavior of streams
	 * including, but not limited to, reading, writing and
	 * seeking-related actions.
	 */
	template <class T> class StreamFilter : public Stream
	{
	public:	
		StreamFilter(T& p) : Parent(p) 
		{
			
		}
		
		/**
		 * Chain
		 * Use jQuery-style chainability to enable the concise
		 * writing of filters
		 * @example Filter->Chain(AnotherFilter)->Chain(AThirdFilter);
		 */
		StreamFilter<T>& Chain(StreamFilter<T>& f) 
		{
			f.Parent = this;
			return f;
		}
		
	protected:
		/**
		 * Parent
		 * The parent of this filter. It must implement the same
		 * operation as the filter does (i.e. a read filter must
		 * have a parent that is also "Readable")
		 */
		T& Parent;
		
	};
};

#endif

