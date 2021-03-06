/*
 *  ArrayList.h
 *  XQL
 *
 *  Created by Izaak Schroeder on 09-11-24.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _ARRAYLIST_H_
#define _ARRAYLIST_H_

#include <Foundation/Core.h>
#include <Foundation/List.h>
#include <Foundation/MutableIterator.h>

#include <memory.h>
#include <iostream>
#include <cstdarg>

namespace I 
{
	template <typename T, template<typename> class KC = EqualityComparator> class ArrayList : public List <T,KC>
	{
	public:
		
		class LocalIterator : public Iterator<T>
		{
		public:
			LocalIterator(const LocalIterator& z) { C = z.C; L = z.L; } ;
			LocalIterator(const ArrayList<T>& l) : C(0), L(l) { }
			T& Current() const {
				return L[C];
			}
			void Next() {
				++C;
			}
			bool Valid() const {
				return C < L.Size;
			}
		protected:
			unsigned int C;
			const ArrayList<T>& L;
		};
		
		class MutableLocalIterator : public LocalIterator, public MutableIterator<T>
		{
		public:
			MutableLocalIterator(ArrayList<T>& l) : InLimbo(false), L2(l), LocalIterator(l) { };
			void Remove() 
			{
				L2.Remove(this->C);
				InLimbo = true;
			}
			
			bool Valid() const {
				return !InLimbo && LocalIterator::Valid();
			}
			
			void Next() {
				if (!InLimbo)
					LocalIterator::Next();
				else
					InLimbo = false;
			}
			
			T& Current() const {
				return LocalIterator::Current();
			}
			
		private:
			bool InLimbo;
			ArrayList<T>& L2;
		};
		
		
		
		ArrayList(unsigned int InitialSize = 37) : Size(0), DataSize(InitialSize), List<T>() 
		{
			Data = (T*)malloc(sizeof(T)*InitialSize); //Create the initial pool
		};
		
		ArrayList(const List<T>& L) 
		{
			ArrayList(L.GetSize());
			foreach(T, i, L)
				Append(*i);
		};
		
		static ArrayList<T> FromElements(const T* first, ...)
		{
			va_list args;
			size_t n = 0;
			va_start(args, first);
			for (const T *S = first; S != NULL; S = va_arg(args, const T*))
				++n;//
			ArrayList<T> r = ArrayList<T>(n);
			
			va_start(args, first);
			for(const T *S = first; S != NULL; S = va_arg(args, const T*))
				r.Append(*S);
			va_end(args);
			
			return n;
		};
		
		~ArrayList() 
		{
			//delete[] Data;
		};
		
		Iterator<T>* GetIterator() const
		{
			return new LocalIterator(*this);
		}
		
		MutableIterator<T>* GetMutableIterator()
		{
			return new MutableLocalIterator(*this);
		}
		
		unsigned int GetSize() const
		{
			return Size;
		};
		
		ArrayList<T>& operator = (const List<T>& L)
		{
			if (this != &L) 
			{
				Resize(L.GetSize());
				Size = 0;
				foreach(T, i, L)
					Append(*i);
			}
			return *this;
		}
		
		ArrayList<T>& operator = (const ArrayList<T>& L)
		{
			if (this != &L) 
			{
				Resize(L.Size);
				Size= 0;
				for(unsigned int i=0; i<L.Size; ++i)
					Append(L.Data[i]);
			}
			return *this;
		}
		
		void Clear()
		{
			
		}
		
		void operator += (T item)
		{
			Append(item);
			return;
		}
		
		unsigned int IndexOf(const T& Item) const
		{
			for(unsigned int i=0; i<Size; ++i)
				if (KCmp(Data[i], Item))
					return i;
			throw Error();
		}
		
		List<T>& operator + (T item)
		{
			ArrayList<T> n = *this;
			n.Append(item);
			return n;
		}
		
		ArrayList<T> Slice(unsigned int Offset, unsigned int Length) const
		{
			if (Offset+Length > Size)
				throw OutOfBoundsError(Offset+Length);
			ArrayList Result = ArrayList(Length);
			Result.Size = Length;
			memcpy(Result.Data, &Data[Offset], Length*sizeof(T));
			return Result;
		}
		
		ArrayList<T> Slice(unsigned int Offset) const
		{
			return Slice(Offset, Size-Offset);
		}
		
		/*
		const List<T>& Window(unsigned int Offset)
		{
			return Window(Offset, Size);
		}
		
		const List<T>& Window(unsigned int Offset, unsigned int Length)
		{
			ArrayList* Result = new ArrayList(0);
			Result->Data = &Data[Offset];
			return Result;
		}*/
		
		T& operator [] (unsigned int index) const
		{
			if (index >= Size)
				throw new Error();
			return Data[index];
		}
		
		void Insert(const T& item, unsigned int position = 0)
		{
			if (position > Size)
				throw new OutOfBoundsError(position);
			if (Size >= DataSize)
				Resize();
			for(unsigned int i=Size; i>position; --i)
				memcpy(&Data[i], &Data[i-1], sizeof(T)); //Don't invoke the = operator
			new (&Data[position]) T(item);
			++Size;
		}
		
		void Append(const T& Item) 
		{
			if (Size >= DataSize)
				Resize();
			//Data[Size++] = Item;
			new (&Data[Size++]) T(Item); //?
		};
		
		void Remove(unsigned int position) 
		{
			if (position > Size)
				throw new OutOfBoundsError(position);
			for(unsigned int i=position; i<Size-1; ++i)
				Data[i] = Data[i+1];
			--Size;
		}
		
		bool IsEmpty() const
		{
			return Size == 0;
		}
		
		ArrayList<T> operator , (const ArrayList<T>& Other)
		{
			ArrayList<T> r = ArrayList<T>(Size + Other.Size);
			const size_t offset = sizeof(T)*Size;
			memcpy(r.Data, Data, offset);
			memcpy(&r.Data[offset], Other.Data, sizeof(T)*Other.Size);
			return r;
		}
		
		ArrayList<T> operator , (const Iterable<T>& Other)
		{
			ArrayList<T> r = ArrayList<T>(*this);
			foreach(T, i, Other)
				r.Append(*i);
			return r;
		}
		
	private:
		void Resize(unsigned int sz) {
			Data = (T*)realloc(Data, sizeof(T) * sz);
			if (NULL == Data)
				throw new Error();
			DataSize = sz;
		}
		
		void Resize() {
			Resize(DataSize * 2);
			
		}
		unsigned int Size;
		unsigned int DataSize;
		T* Data;
		
	};
};

#endif

