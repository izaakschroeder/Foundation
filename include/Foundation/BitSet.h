
#ifndef _I_BITSET_H_
#define _I_BITSET_H_

#include <Foundation/Set.h>
#include <xmmintrin.h>
#include <string.h> //memset

#include <iostream>

namespace I {
	
	template <typename From, typename To> class Mapper 
	{
	public:
		virtual To& operator() (const From& f) const = 0;
	};
	
	/**
	 * BitSet
	 *
	 *
	 */
	template <typename T, class M1, class M2 > class BitSet : public Set<T,EqualityComparator>
	{
	public:
		/**
		 * BitSet
		 *
		 *
		 */
		BitSet(const M1& m1, const M2& m2, unsigned int ae = 31) : Set<T,EqualityComparator>(), Data(NULL), DataBlockSize(0), AllocatedElements(0), AllocatedSize(0), GetBitPositionForItem(m1), GetItemForBitPosition(m2)
		{
			Resize(ae);
			Clear();
		}
		
		BitSet(unsigned int ae = 31) : Set<T,EqualityComparator>(), Data(NULL), DataBlockSize(0), AllocatedElements(0), AllocatedSize(0)
		{
			Resize(ae);
			Clear();
		}
		
		/**
		 * BitSet
		 *
		 *
		 */
		BitSet(const BitSet<T,M1,M2>& Other) : Set<T,EqualityComparator>(), Data(NULL), DataBlockSize(Other.DataBlockSize), AllocatedElements(Other.AllocatedElements), AllocatedSize(Other.AllocatedSize), GetBitPositionForItem(Other.GetBitPositionForItem), GetItemForBitPosition(Other.GetItemForBitPosition)
		{
			Data = (StorageType*)malloc(AllocatedSize);
			memcpy(Data, Other.Data, AllocatedSize);
		}
		
		/**
		 * operator=
		 *
		 *
		 */
		BitSet<T,M1,M2>& operator= (const BitSet<T,M1,M2>& Other)
		{
			if (this != &Other) 
			{
				if (Other.AllocatedSize > AllocatedSize)
					Data = realloc(Data, Other.AllocatedSize);
				else
					memset(&Data[Other.DataBlockSize], 0, Other.DataBlockSize - DataBlockSize);
				memcpy(Data, Other.Data, Other.AllocatedSize);
				GetBitPositionForItem = Other.GetBitPositionForItem;
				GetItemForBitPosition = Other.GetItemForBitPosition;
			}
			return *this;
		}
		
		/**
		 * ~BitSet
		 *
		 *
		 */
		~BitSet()
		{
			free(Data);
		}
		
		/**
		 * GetSize
		 *
		 *
		 */
		unsigned int GetSize() const 
		{
			return Size;
		};
		
		/**
		 * Get
		 *
		 *
		 */
		T& Get(const T& Item) const
		{
			return GetItemForBitPosition(GetBitPositionForItem(Item));
		};
		
		/**
		 * Add
		 *
		 *
		 */
		bool Add(const T& Item) 
		{
			const unsigned int p = GetBitPositionForItem(Item);
			const unsigned int o = GetLocalOffsetForBitPosition(p);
			const unsigned int b = GetBlockForBitPosition(p);
			static const StorageType InitialValue = 1;
			
			Resize(p);
			
			//const StorageType tmpA = initb(p);
			const StorageType tmpA = InitialValue << o;
			//const StorageType tmpB = _mm_xor_si128(tmpA, Data[b]);
			const StorageType tmpB = tmpA ^ Data[b];
			//if (!bool128(_mm_and_si128(tmpA, tmpB))) 
			if (tmpA & tmpB)
			{
				Data[b] = tmpB;
				++Size;
				return true;
			}
			return false;
			
			
		}
		
		/**
		 * Remove
		 *
		 *
		 */
		bool Remove(const T& Item)
		{
			const unsigned int p = GetBitPositionForItem(Item);
			const unsigned int o = GetLocalOffsetForBitPosition(p);
			const unsigned int b = GetBlockForBitPosition(p);
			static const StorageType InitialValue = 1;
			
			Resize(p);
			
			//const StorageType tmpA = initb(p);
			const StorageType tmpA = InitialValue << o;
			//const StorageType tmpB = _mm_xor_si128(tmpA, Data[b]);
			const StorageType tmpB = tmpA ^ Data[b];
			//if (bool128(_mm_and_si128(tmpA, tmpB)))
			if (tmpA & tmpB)
				return false;
			Data[b] = tmpB;
			--Size;
			return true;
			
		}
		
		/**
		 * Contains
		 *
		 *
		 */
		bool Contains(const T& Item) const
		{
			const unsigned int p = GetBitPositionForItem(Item);
			const unsigned int o = GetLocalOffsetForBitPosition(p);
			const unsigned int b = GetBlockForBitPosition(p);
			static const StorageType InitialValue = 1;
			
			//const StorageType tmpA = initb(p);
			const StorageType tmpA = InitialValue << o;
			//return bool128(_mm_and_si128(tmpA, Data[b]));
			return tmpA & Data[b];
		}
		
		/**
		 * Clear
		 *
		 *
		 */
		void Clear() 
		{
			memset(Data, 0, AllocatedSize);
			Size = 0;
		}
		
		/**
		 * operator ==
		 *
		 *
		 */
		bool operator == (const BitSet<T,M1,M2>& Other) const 
		{
			if (Other.Size != Size)
				return false;
			for(int i=0; i<Other.DataBlockSize; ++i)
				// if (bool128(_mm_xor_si128(Data[i], Other.Data[i])))
				if (Data[i] ^ Other.Data[i])
					 return false;
			return true;
		};
		
		/**
		 * Merge
		 *
		 *
		 */
		bool Merge(const BitSet<T,M1,M2>& Other) 
		{
			bool r = false;
			Resize(Other.AllocatedElements);
			for(int i=0; i<Other.DataBlockSize; ++i) 
			{
				//StorageType tmp = _mm_xor_si128(Data[i], Other.Data[i]);
				const StorageType tmp = (Data[i] ^ Other.Data[i]) & Other.Data[i];
				if (tmp) 
				{
					for(int j=0; j<sizeof(StorageType)/sizeof(uint64_t); ++j)
						Size += __builtin_popcountll (((uint64_t*)&tmp)[j]);
					//Data[i] = _mm_or_si128(Data[i], tmp);
					Data[i] |= tmp;
					r = true;
				}
			}
			return r;
		}
		
		/**
		 * Merge
		 *
		 *
		 */
		bool Merge(const BitSet<T,M1,M2>&s, BitSet<T,M1,M2>& y) 
		{
			bool r = false;
			Resize(s.AllocatedElements);
			for(int i=0; i<s.DataBlockSize; ++i) 
			{
				//StorageType tmp = _mm_xor_si128(Data[i], s.Data[i]);
				const StorageType tmp = (Data[i] ^ s.Data[i]) & s.Data[i];
				if (tmp) 
				{
					//Data[i] = _mm_or_si128(Data[i], tmp);
					Data[i] |= tmp;
					//y.Data[i] = _mm_or_si128(y.Data[i], tmp);
					y.Data[i] |= tmp;
					for(int j=0; j<sizeof(StorageType)/sizeof(uint64_t); ++j) 
					{
						const unsigned int p = __builtin_popcountll (((uint64_t*)&tmp)[j]);
						Size += p;
						y.Size += p;
					}
					r = true;
				}
			}
			return r;
		}
		
		/**
		 * GetIterator
		 *
		 *
		 */
		Iterator<T>* GetIterator() const 
		{
			return new BitSetIterator(this);
		}
		
		
	protected:
		
		/**
		 * BitSetIterator
		 *
		 *
		 */
		class BitSetIterator : public Iterator<T>
		{
		public:
			BitSetIterator(const BitSet<T,M1,M2>* O) : Iterator<T>(), Source(O), NextBitPosition(0), BitPosition(0), ItemPosition(0)
			{
				if (Valid()) 
					Cycle();
				 
			}
			
			virtual ~BitSetIterator()
			{
				
			}
			
			T& Current() const
			{
				return Source->GetItemForBitPosition(BitPosition);
			}
			
			void Next()
			{
				Cycle();
				
			}
			
			bool Valid() const
			{
				return ItemPosition <= Source->Size;
			}
		
		protected:
			void Cycle()
			{
				static const StorageType BitMask = -1;
				StorageType tmp;
				do {
					const unsigned int ShiftOffset = Source->GetLocalOffsetForBitPosition(NextBitPosition);
					tmp = __builtin_ffsll(Source->Data[Source->GetBlockForBitPosition(NextBitPosition)] & (BitMask << ShiftOffset));
					NextBitPosition += (!tmp) ? sizeof(StorageType) * 8 - ShiftOffset : tmp - ShiftOffset;
				} while (!tmp);
				BitPosition = NextBitPosition - 1;
				++ItemPosition;
			}
			
			const BitSet<T,M1,M2>* Source;
			unsigned int BitPosition;
			unsigned int NextBitPosition;
			unsigned int ItemPosition;
			
		};
		
		/**
		 * Resize
		 *
		 *
		 */
		void Resize(unsigned int n) 
		{
			if (AllocatedElements < n) {
				unsigned int OldDataBlockSize = DataBlockSize;
				AllocatedElements = n;
				DataBlockSize = GetBlocksRequiredForElements(AllocatedElements);
				AllocatedSize = DataBlockSize * sizeof(StorageType);
				Data = (StorageType*)realloc(Data, AllocatedSize);
				memset(&Data[OldDataBlockSize], 0, (DataBlockSize-OldDataBlockSize) * sizeof(StorageType));
			}
		}
		
		/**
		 * GetBlocksRequiredForElements
		 *
		 *
		 */
		unsigned int GetBlocksRequiredForElements(unsigned int e) const
		{
			return e * 8 / sizeof(StorageType) + 1;
		}
		
		/**
		 * GetBlockForBitPosition
		 *
		 *
		 */
		unsigned int GetBlockForBitPosition(unsigned int b) const
		{
			const unsigned int r =  b / 8 / sizeof(StorageType);
			//std::cout << "Block for bit " << b << " is " << r << "." << std::endl;
			return r;
		}
		
		/**
		 * GetLocalOffsetForBitPosition
		 *
		 *
		 */
		unsigned int GetLocalOffsetForBitPosition(unsigned int b) const
		{
			const unsigned int r = (b % (8 * sizeof(StorageType)));
			//std::cout << "Local offset for bit " << b << " is " << r << "." << std::endl;
			return  r;
		}
		
		/**
		 * StorageType
		 *
		 *
		 */
		typedef uint64_t StorageType;
		
		/**
		 * Data
		 *
		 *
		 */
		StorageType* Data;
		
		/**
		 * DataBlockSize
		 *
		 *
		 */
		unsigned int DataBlockSize;
		
		/**
		 * AllocatedElements
		 *
		 *
		 */
		unsigned int AllocatedElements;
		
		/**
		 * AllocatedSize
		 *
		 *
		 */
		unsigned int AllocatedSize;
		
		/**
		 * Size
		 *
		 *
		 */
		unsigned int Size;
		
		M1 GetBitPositionForItem;
		M2 GetItemForBitPosition;
	};
};

#endif