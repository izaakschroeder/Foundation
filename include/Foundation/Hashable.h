/**
 * Hashable.h
 * @author Izaak Schroeder
 */

#ifndef _I_HASHABLE_H_
#define _I_HASHABLE_H_

#include <Foundation/EqualityComparable.h>

namespace I 
{
	template <typename T> class Hashable : public EqualityComparable<T>
	{
	public: 
		virtual unsigned int GetHashCode() const = 0;
	};
	
	template <typename T> class HashGenerator
	{
	public:
		virtual unsigned int GetHashCode(const T& o) const = 0;
	};
	
	template <typename T> class HashableHashGenerator : public HashGenerator< T >
	{
	public:
		virtual unsigned int GetHashCode(const T& o) const {
			return o.GetHashCode();
		}	
	};
	
	template <typename T, class K> class DereferencingHashableHashGenerator : public HashGenerator< T >
	{
	public:
		virtual unsigned int GetHashCode( const T& o ) const {
			return k.GetHashCode(*o);
		}
	private:
		K k;
	};
};

#endif