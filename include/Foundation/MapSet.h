/**
 * HashSet.h
 * @author Izaak Schroeder
 */

#ifndef _MAPSET_H_
#define _MAPSET_H_

#include <Foundation/Set.h>
#include <Foundation/Map.h>
#include <Foundation/EqualityComparator.h>

namespace I 
{
	template <class MT, typename T, template<typename> class C = EqualityComparator> class MapSet : public Set<T,C>
	{
	public:
		unsigned int GetSize() const
		{
			return MapData.GetSize();
		};
		
		Iterator<T>* GetIterator() const
		{
			return MapData.GetIterator();
		};
		
		MapSet<MT, T, C>& operator = (const MapSet<MT, T, C>& Other)
		{
			MapData = Other.MapData;
			return *this;
		}
		
		MapSet<MT, T, C>& operator = (const Set<T, C>& Other)
		{
			Clear();
			foreach(T, i, Other)
				Add(*i);
			endforeach
			return *this;
		}
		
		bool Remove(const T& Item)
		{
			if (!Contains(Item))
				return false;
			MapData.Unset(Item);
			return false;
		}
		
		bool Add(const T& Item) 
		{
			if(!Contains(Item))
				return MapData.Set(Item, Item);
			return false;
		};
		
		bool Contains(const T& Item) const
		{
			return MapData.ContainsKey(Item);
		};
		
		T& Get(const T& Item) const {
			return MapData.Get(Item);
		}
		
		virtual void Clear() 
		{
			MapData.Clear();
		}
		
		bool VerifyState() {
			return MapData.VerifyState();
		}
		
	private:
		MT MapData;
	};
};

#endif