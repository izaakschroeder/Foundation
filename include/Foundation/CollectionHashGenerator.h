/**
 * CollectionHashGenerator.h
 * @author Izaak Schroeder
 */

#include <Foundation/EqualityComparator.h>
#include <Foundation/Hashable.h>

#ifndef _I_COLLECTION_HASH_GENERATOR_H_
#define _I_COLLECTION_HASH_GENERATOR_H_

namespace I 
{
	template <typename I, template<class> class C = EqualityComparator, class K = HashableHashGenerator<I> > class CollectionHashGenerator : public HashGenerator< List<I,C> >
	{
	public:
		virtual unsigned int GetHashCode( const List<I,C>& o ) const 
		{
			unsigned int k = 0xced843d;
			//foreach(I, i, o)
			//	k * = g->GetHashCode(i);
			//	k >>= 3;
			//	k ^= 0xdeadbeef;
			//endforeach
			return k;
		}	
	private:
		K g;
	};
}


#endif