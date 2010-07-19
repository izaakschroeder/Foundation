
#ifndef _I_TREE_H_
#define _I_TREE_H_

#include <Foundation/LinkedList.h>

namespace I
{
	template <class T> class Tree
	{
	public:
		
		class Node;
		
		Tree() : Root(NULL) 
		{
			
		}
		
		Tree(Node* n) : Root(n) 
		{
			
		}
		
		virtual ~Tree()
		{
			
		}
		
		class Node
		{
		public:
			Node(const T& D) : Data(D) 
			{
				
			}
			
			Node(const Node& Other)
			{
				Data = Other.Data;
			}
			
			Node& operator = (const Node& Other)
			{
				if (this != &Other)
					Data = Other.Data;
				return *this;
			}
			
			T Data;
			
			void AddChild(Node* N)
			{
				Children.Append(N);
			}
			
			void AddChild(Node* N, unsigned int i)
			{
				Children.Insert(N, i);
			}
			
			void RemoveChild(unsigned int i)
			{
				Children.Remove(i);
			}
			
			Node* operator [] (unsigned int i) const
			{
				return Children[i];
			}
			
		protected:
			LinkedList<Node*> Children;
		};
	
		
	protected:
		
		Node* Root;	
	};
};

#endif

