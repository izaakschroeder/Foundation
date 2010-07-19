/**
 * LinkedList.h
 * @author Izaak Schroeder
 */

#ifndef _I_LINKEDLIST_H_
#define _I_LINKEDLIST_H_

#include <Foundation/Core.h>
#include <Foundation/List.h>
#include <Foundation/MutableIterator.h>
#include <Foundation/EqualityComparator.h>

#include <iostream>
#include <stdarg.h>

namespace I	
{
	template <typename, template<typename> class = EqualityComparator> class LinkedList;
	
	template <typename T, template<typename> class KC> class LinkedList : public List <T,KC>
	{
	private:
		class Node 
		{
		public:
			Node(const T& d, Node* N) : Next(N), Data(d) { }
			Node* Next;
			T Data;
		};
		
		class LocalIterator : public Iterator<T> 
		{
		public:
			LocalIterator(const LinkedList<T,KC>& l) : C(l.Head) { };
			T& Current() const { return C->Data; }
			void Next() { C = C->Next; };
			bool Valid() const { return C != NULL; };
		protected:
			Node* C;
		};
		
		class MutableLocalIterator : public LocalIterator, public MutableIterator<T>
		{
		public:
			MutableLocalIterator(LinkedList<T,KC>& l) : LocalIterator(l), InLimbo(false), P(NULL), L(l) { };
			T& Current() const { return LocalIterator::Current(); }
			void Next() { if (InLimbo) InLimbo = false; else {
				P = this->C; LocalIterator::Next();
			} };
			bool Valid() const { return InLimbo ? false : LocalIterator::Valid(); };
			void Remove() 
			{ 
				if (!Valid()) throw	Error(); 
				Node *Next = this->C->Next;
				InLimbo = true; 
				if(P) 
					P->Next = Next;
				if (Next == NULL)
					L.Tail = P;
				if (this->C == L.Head)
					L.Head = Next;;
				
				delete this->C;
				this->C = Next; 
				--L.Size;
				L.StateCheck();
			}
		private:
			bool InLimbo;
			Node* P;
			LinkedList<T,KC>& L;
		};
		
		
		unsigned int Size;
		Node* Head;
		Node* Tail;
		
	public:
		void StateCheck()
		{
			return;
			unsigned int i = 0;
			for(Node* n = Head; n != NULL; n = n->Next)
				++i;
			if (i != Size)
			{
				std::cout << "ERROR STATE MISMATCH! List thinks it has " << Size << " elements, when it only has " << i << "!" << std::endl; 
			}
		}
		
		//
		LinkedList() : List <T,KC>(), Size(0), Head(NULL), Tail(NULL)
		{
			
		}
		
		//
		LinkedList(const LinkedList<T,KC>& L) : List<T,KC>(),  Size(0), Head(NULL), Tail(NULL)
		{
			foreach(T, i, L)
				Append(i);
			endforeach
		}
		
		//
		LinkedList(const List<T,KC>& L) : List<T,KC>(), Size(0), Head(NULL), Tail(NULL)
		{
			foreach(T, i, L)
				Append(i);
			endforeach
		}
		
		virtual ~LinkedList()
		{
			
		}
		
		static LinkedList<T,KC> FromElements(T* First, ...)
		{
			va_list args;
			va_start(args, First);
			LinkedList<T,KC> Result;
			for (T* i = First; i != NULL; i = va_arg(args, T*))
				Result.Append(*i); //Add to the RHS of the production
			va_end(args);
			return Result;
		}
		
		void Clear()
		{
			Node *tmp = NULL;
			for(Node* n = Head; n != NULL; n = tmp)
			{
				tmp = n->Next;
				delete n;
			}
			Head = Tail = NULL;
			Size = 0;
			StateCheck();
		}
		
		unsigned int GetSize() const
		{
			return Size;
		};
		
		unsigned int IndexOf(const T& Element) const
		{
			unsigned int i = 0;
			for(Node* n = Head; n != NULL; n = n->Next, ++i)
				if (KCmp(n->Data, Element))
					return i;
			throw new Error();
		}
		
		T& operator [] (unsigned int index) const
		{
			Node* node = Head;
			if (index >= Size)
				throw new Error();
			for (unsigned int i = 0; node != NULL && i < index; node = node->Next, ++i);
			return node->Data;
		};
				
		LinkedList<T,KC> operator , (const Iterable<T>& Other)
		{
			LinkedList<T,KC> r = LinkedList<T,KC>(*this);
			foreach(T, i, Other)
				r.Append(i);
			endforeach
			return r;
		}
		
		bool IsEmpty() const
		{
			return Head == NULL;
		};
		
		void Append(const T& data) 
		{
			Node* n = new Node(data, NULL);
			if (Head == NULL)
				Head = n;
			if (Tail != NULL)
				Tail->Next = n;
			Tail = n;
			++Size;
			StateCheck();
		};
		
		void Insert(const T& data, unsigned int index = 0) 
		{
			Node* node = Head;
			Node* n = new Node(data, NULL);
			if (index == 0 && Size == 0)
			{
				Head = Tail = n;
				++Size;
				StateCheck();
				return;
			}
			else if (index == Size)
			{
				Tail->Next = n;
				Tail = n;
				++Size;
				StateCheck();
				return;
			}
			else if (index > Size)
				throw new Error();
			
			for (unsigned int i = 0; node != NULL && i < index; node = node->Next, ++i);
			Node* tmp = node->Next;
			node->Next = n;
			n->Next = tmp;
			++Size;
			StateCheck();
		}
		
		void Remove(unsigned int index) 
		{
			Node*prev = NULL, *node = Head;
			if (index >= Size)
				throw new Error();
			
			for (unsigned int i = 0; node != NULL && i < index; prev = node, node = node->Next, ++i);
			
			if (prev)
				prev->Next = node->Next;
			else
				Head = node->Next;
			if (node->Next == NULL)
				Tail = prev;
			delete node;
			--Size;
			StateCheck();
		}
		
		LinkedList<T,KC>* Slice(unsigned int Offset, unsigned int Length) const {
			
			if (Offset+Length > Size)
				throw OutOfBoundsError(Offset+Length);
			LinkedList* Result = new LinkedList();
			unsigned int o = 0;
			foreach (T, i, *this)
				if (Length + Offset == o)
					break;
				else if (o++ >= Offset)
					Result->Append(i);
			endforeach
			return Result;
				
		};
		
		LinkedList<T,KC>* Slice(unsigned int Offset) const {
			return Slice(Offset, Size - Offset);
		}
		
		const LinkedList<T,KC>* Window(unsigned int Offset, unsigned int Length) const {
			if (Offset+Length > Size)
				throw OutOfBoundsError(Offset+Length);
			LinkedList* Result = new LinkedList();
			Result->Head = Head;
			for (unsigned int i=0; i<Offset; ++i)
				Result->Head = Result->Head->Next;
			Result->Tail = Result->Head;
			for (unsigned int i=0; i<Length; ++i)
				Result->Tail = Result->Tail->Next;
			Result->Size = Length;
		}
		
		const LinkedList<T,KC>* Window(unsigned int Offset) const {
			if (Offset >= Size)
				throw OutOfBoundsError(Offset);
			LinkedList* Result = new LinkedList();
			Result->Head = Head;
			for (unsigned int i=0; i<Offset; ++i)
				Result->Head = Result->Head->Next;
			Result->Tail = Tail;
			Result->Size = Size - Offset;
			return Result;
		}
		
		
		virtual Iterator<T>* GetIterator() const
		{
			return new LocalIterator(*this);
		}
		
		MutableIterator<T>* GetMutableIterator()
		{
			return new MutableLocalIterator(*this);
		}
		
	
	};
};
#endif