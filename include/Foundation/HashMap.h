/**
 * HashMap.h
 * @author Izaak Schroeder
 */

#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <Foundation/Core.h>
#include <Foundation/LinkedList.h>
#include <Foundation/Map.h>
#include <Foundation/Iterable.h>
#include <Foundation/MutableIterator.h>
#include <Foundation/EqualityComparator.h>
#include <Foundation/Hashable.h>

#include <iostream>


namespace I 
{
	template <typename T, template<typename> class C, class H> class HashSet;
	
	template <typename KT, typename VT, template <typename> class KC = EqualityComparator>class KeyValuePair : public EqualityComparable<class KeyValuePair<KT, VT, KC> >
	{
	public:
		KeyValuePair(const KeyValuePair& KV) : Key(KV.Key), Value(KV.Value) 
		{ 
			
		};
		
		KeyValuePair(KT k, VT v) : Key(k), Value(v) 
		{ 
			
		};
		
		KeyValuePair& operator=(const KeyValuePair<KT, VT,KC>& rhs) 
		{
			Key = rhs.Key;
			Value = rhs.Value;
			return *this;
		}
		
		KC<KT> KCmp;
		
		bool operator == (const KeyValuePair<KT,VT,KC>& Other) const 
		{ 
			return ((KCmp)(Key, Other.Key)) && Value == Other.Value; 
		};
		
		KT Key;
		VT Value;
	};
		
	template <typename KT, typename VT, template <class> class KC = EqualityComparator, class HG = HashableHashGenerator<KT> > class HashMap : public Map<KT, VT, KC>
	{
	public:
		typedef KeyValuePair<KT,VT,KC>* BucketType;
		typedef LinkedList<BucketType> ListType;
		KC<KT> KCmp;
		HG HGen;
		
		HashMap(unsigned int InitialSize = 31) : Map<KT, VT, KC>(), Size(0), BucketSize(InitialSize), Buckets(new ListType[InitialSize])
		{
		};
		
		HashMap(const HashMap<KT, VT, KC>& Other) : Map<KT,VT, KC>(), Size(0), BucketSize(Other.BucketSize), Buckets(new ListType[Other.BucketSize])
		{
			iterate(Iterator<BucketType>, KVP, new BucketIterator(Other))
				Set((*KVP)->Key, (*KVP)->Value);
		}

		HashMap(const Map<KT, VT, KC>& Other) : Map<KT,VT, KC>(), Size(0), BucketSize(Other.BucketSize), Buckets(new ListType[Other.BucketSize])
		{
			std::cout << "FFUUUUU" << std::endl;
		}
		
		~HashMap() 
		{
			delete[] Buckets;
			Buckets = NULL;
		};
		
		unsigned int GetSize() const 
		{ 
			return Size; 
		};
		
		bool operator == (const Map<KT,VT,KC>& Other) const
		{
			if (GetSize() != Other.GetSize())
				return false;
			iterate(Iterator<BucketType>, KVP, this->GetKeyValueIterator())
			{
				if (!Other.ContainsKey((*KVP)->Key))
					return false;
				if (Other[(*KVP)->Key] != (*KVP)->Value)
					return false;
			}
			return true;
		};
		
		VT& operator [] (const KT& Key) const 
		{
			/*
			unsigned int H = Hash(Key);
			ListType& Bucket = Buckets[H];
			foreach(BucketType, KVP, Bucket)
				if ((KVP)->Key == Key)
					return (VT&)(KVP)->Value;
			endforeach;
			BucketType KVP;
			KVP = new KeyValuePair<KT,VT>(Key, VT());
			Bucket.Append(KVP);
			return (VT&)KVP->Value;*/
			const BucketType& KVP = RequireKey(Key);
			return (VT&)KVP->Value;
		};
		
		VT& Get(const KT& Key) const 
		{
			const BucketType& KVP = RequireKey(Key);
			return (VT&)KVP->Value;
		};
		
		VT& Get(const KT& Key, bool autocreate)
		{
			if (!autocreate)
				return Get(Key);
			unsigned int H = Hash(Key);
			ListType& Bucket = Buckets[H];
			foreach(BucketType, KVP, Bucket)
				if (KCmp(Key, KVP->Key))
					return KVP->Value;
			endforeach
			BucketType kv = new KeyValuePair<KT,VT,KC>(Key, VT());
			Bucket.Append(kv);
			++Size;
			return kv->Value;
		};
		
		void Unset(const KT& Key)
		{
			unsigned int H = Hash(Key);
			iterate(MutableIterator<BucketType>, i, Buckets[H].GetMutableIterator()) 
			{
				if ((KCmp)((*i)->Key, Key))
				{
					delete *i;
					i.Remove();
					--Size;
					//std::cout << this << "Unset" << std::endl;
					//VerifyState();
					return;
				}
			}
			throw KeyNotFoundError();
		}
		
		bool Set(const KT& Key, const VT& Value)
		{
			unsigned int H = Hash(Key);
			ListType& Bucket = Buckets[H];
			foreach(BucketType, KVP, Bucket)
				if (KCmp(Key, KVP->Key))
				{
					KVP->Value = Value;
					return false;
				}
			endforeach
			Bucket.Append(new KeyValuePair<KT,VT,KC>(Key, Value));
			++Size;
			return true;
		}
		
		bool ContainsKey(const KT& Key) const
		{
			unsigned int H = Hash(Key);
			foreach(BucketType, KVP, Buckets[H])
				if ((KCmp)(KVP->Key, Key))
					return true;
			endforeach
			return false;
		}
		
		Iterator<VT>* GetIterator() const
		{
			return new ValueIterator(this);
		}
				
		void Clear() 
		{
			for(unsigned int i = 0; i<BucketSize; ++i)
				Buckets[i].Clear();
			Size = 0;
		}
		
		Iterator<BucketType>* GetKeyValueIterator() const
		{
			return new BucketIterator(this);
		}
		
		HashSet<KT,KC,HG> GetKeySet() const
		{
			HashSet<KT,KC,HG> r;
			iterate(Iterator<BucketType>, i, GetKeyValueIterator()) {
				r.Add((*i)->Key);
			}
			return r;
		}
		
		/*
		Iterator<BucketType>& GetIterator()
		{
			return *(new BucketIterator(this));
		}*/
		
		
		Map<KT,VT,KC>& operator = (const HashMap<KT,VT,KC>& Other) 
		{
			if (&Other == this)
				return *this;
			Clear();
			iterate(Iterator<BucketType>, i, Other.GetKeyValueIterator()) {
				Set((*i).Key, (*i).Value);
			}
			return *this;
		}
		
		bool VerifyState()
		{
			unsigned int tSize = 0;
			for (unsigned int i=0; i<BucketSize; ++i)
				tSize += Buckets[i].GetSize();
			if (tSize != Size)
			{
				std::cout << this << " ERROR STATE MISMATCH! Hashmap thinks it has " << Size << " elements, when it only has " << tSize << " ones! " << std::endl;
				return false;
			}
			return true;
		}
		
	private:
		
		class BucketIterator : public Iterator<BucketType>
		{
		public:
			BucketIterator(const HashMap * m) : CurrentBucket(0), M(m), i(NULL), c(0)
			{
				do 
				{
					i = M->Buckets[CurrentBucket].GetIterator();
					if (i->Valid())
						break;
				} while (++CurrentBucket < M->BucketSize);
			};
			
			bool Valid() const
			{
				//std::cout << i << std::endl;
				return c < M->Size;
			}
			
			BucketType& Current() const
			{
				return i->Current();
			}
			
			void Next()
			{
				i->Next();
				if (!i->Valid()) 
				{
					while (CurrentBucket+1 < M->BucketSize) 
					{
						i = M->Buckets[++CurrentBucket].GetIterator();
						if (i->Valid())
							break;
					}
				}
				++c;
			}
			
		private:
			unsigned int CurrentBucket;
			const HashMap* M;
			Iterator<BucketType>* i;
			unsigned int c;
		};
		
		class ValueIterator : public Iterator<VT>
		{
		public:
			ValueIterator(const HashMap* M) : i(M) 
			{ 
				
			};
			
			VT& Current() const
			{
				return i.Current()->Value;
			};
			
			void Next()
			{
				i.Next();
			};
			
			bool Valid() const
			{
				return i.Valid();
			};
		private:
			BucketIterator i;
		};
		
		const BucketType& RequireKey(const KT& Key) const
		{
			unsigned int H = Hash(Key);
			foreach(BucketType, KVP, Buckets[H])
				if (KCmp(KVP->Key, Key))
					return KVP;
			endforeach
			throw KeyNotFoundError();
		}
		
		
		/**
		 * Resize
		 * Change the internal size of the storage allocated to the hash map
		 *
		 */
		void Resize(unsigned int NewBucketSize) 
		{
			Buckets = realloc(Buckets, NewBucketSize*sizeof(BucketType));
			BucketSize = NewBucketSize;
			if (Buckets == NULL)
				throw Error();
			Rehash();
		}
		
		/**
		 * Rehash
		 *
		 *
		 */
		void Rehash() 
		{
			foreach(BucketType, b, (*this))
				Set(b->Key, b->Value);
			endforeach
		};
		
		/**
		 * Hash
		 *
		 *
		 */
		unsigned int Hash(const KT& key) const
		{
			unsigned int code = HGen.GetHashCode(key) % BucketSize;
			return code;
		};
		
		unsigned int Size;
		unsigned int BucketSize;
		ListType* Buckets;
	};
};

#endif
