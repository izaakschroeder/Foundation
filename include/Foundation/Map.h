/**
 * Map.h
 * @author Izaak Schroeder
 */

#ifndef _MAP_H_
#define _MAP_H_

#include <Foundation/Core.h>
#include <Foundation/EqualityComparable.h>
#include <Foundation/EqualityComparator.h>
#include <Foundation/Iterable.h>

namespace I 
{
	template <typename KT, typename VT, template<typename> class KC = EqualityComparator> class Map : public Iterable<VT>, public EqualityComparable<Map<KT, VT, KC> >
	{
	public:
		virtual VT& operator [] (const KT& key) const = 0;
		virtual VT& Get(const KT& key) const = 0;
		virtual bool ContainsKey(const KT& key) const = 0;
		virtual bool Set(const KT& key, const VT& value) = 0;
		virtual void Unset(const KT& Key) = 0;
		virtual unsigned int GetSize() const = 0;
		virtual bool IsEmpty() const {
			return GetSize() == 0;
		}
		virtual void Clear() = 0;
	};
};

#endif