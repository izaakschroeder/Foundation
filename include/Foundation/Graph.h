/*
 * Graph.h
 * @author Izaak Schroeder
 */

#ifndef _I_GRAPH_H
#define _I_GRAPH_H

#include "Foundation/include/EqualityComparable.h"
#include "Foundation/include/HashMap.h"
#include "Foundation/include/HashSet.h"
#include "Foundation/include/LinkedList.h"
#include "Foundation/include/LinkedListStack.h"
#include "Foundation/include/LinkedListQueue.h"

namespace I 
{
	
	/**
	 * DepthFirstSearch
	 * Traverse through a finite graph of nodes using depth-first
	 * search.
	 * @see http://en.wikipedia.org/wiki/Depth-first_search
	 */
	template <class T> class DepthFirstSearch : public Iterator<T>
	{
	public:
		/**
		 * DepthFirstSearch
		 *
		 *
		 */
		DepthFirstSearch(const T& Start)
		{
			Nodes.Push(Start);
		}
		
		/**
		 * Current
		 *
		 *
		 */
		T& Current() const 
		{
			return Nodes.Peek();
		}
		
		/**
		 * Next
		 *
		 *
		 */
		void Next()
		{
			T Node = Nodes.Pop();
			if (!Visited.Contains(Node))
			{
				Visited.Add(Node);
				foreach(T, Neighbor, Node.ConnectsTo())
					Nodes.Push(Neighbor);
			}
		}
		
		/**
		 * Valid
		 *
		 *
		 */
		bool Valid() const
		{
			return !Nodes.Empty();
		}
		
	protected:
		/**
		 * Visited
		 *
		 *
		 */
		HashSet<T> Visited;
		
		/**
		 * Nodes
		 *
		 *
		 */
		LinkedListStack<T> Nodes;
	};
	
	/**
	 * BreadthFirstSearch
	 * Traverse through a finite graph of nodes using breadth-first
	 * search.
	 * @see http://en.wikipedia.org/wiki/Breadth-first_search
	 */
	template <class T> class BreadthFirstSearch : public Iterator<T>
	{
	public:
		/**
		 * BreadthFirstSearch
		 *
		 *
		 */
		BreadthFirstSearch(const T& Start)
		{
			Nodes.Push(Start);
		}
		
		/**
		 * Current
		 *
		 *
		 */
		T& Current() const 
		{
			return Nodes.Peek();
		}
		
		/**
		 * Next
		 *
		 *
		 */
		void Next()
		{
			T Node = Nodes.Pop();
			if (!Visited.Contains(Node))
			{
				Visited.Add(Node);
				foreach(T, Neighbor, Node.ConnectsTo())
					Nodes.Push(Neighbor);
			}
		}
		
		/**
		 * Valid
		 *
		 *
		 */
		bool Valid() const
		{
			return !Nodes.Empty();
		}
		
	protected:
		/**
		 * Visited
		 *
		 *
		 */
		HashSet<T> Visited;
		
		/**
		 * Nodes
		 *
		 *
		 */
		LinkedListQueue<T> Nodes;
	};
	
	/**
	 * LexicographicBreadthFirstSearch
	 * 
	 *
	 */
	template <class T> class LexicographicBreadthFirstSearch : public Iterator<T>
	{
		/**
		 * LexicographicBreadthFirstSearch
		 *
		 *
		 */
		LexicographicBreadthFirstSearch(const T& Start)
		{
			
		}
		
		/**
		 * Current
		 *
		 *
		 */
		T& Current() const 
		{
			return NULL;
		}
		
		/**
		 * Next
		 *
		 *
		 */
		void Next()
		{
			
		}
		
		/**
		 * Valid
		 *
		 *
		 */
		bool Valid() const
		{
			return false;
		}
	};
	
	/**
	 * Graph
	 *
	 *
	 */
	template <class T, class W> class Graph
	{
	public:
		
		/**
		 * Vertex
		 *
		 *
		 */
		class Vertex : public EqualityComparable<Vertex>
		{
		public:
			Vertex() { }
			Vertex(Graph* g, int i) : Origin(g), ID(i) { }
			Vertex(Graph* g, int i, T d) : Origin(g), ID(i), Data(d) { }
			Vertex(const Vertex& V) : Origin(V.Origin), ID(V.ID), Data(V.Data) { }
			Vertex& operator = (const Vertex& V) { Origin = V.Origin; ID = V.ID; Data = V.Data; return *this; }
			bool operator == (const Vertex& V) const { return ID == V.ID && Origin == V.Origin; }
			Graph* Origin;
			int ID;
			T Data;
			
		};
		
		/**
		 * Edge
		 *
		 *
		 */
		class Edge : public EqualityComparable<Edge>
		{
		public:
			Edge(const Vertex& v1, const Vertex& v2, const W& d) : Source(v1), Destination(v2), Data(d) { }
			bool operator == (const Edge& E) const { return Source == E.Source && Destination == E.Destination; }
			Vertex Source;
			Vertex Destination;
			W Data;
		};
		
		/**
		 * CreateVertex
		 *
		 *
		 */
		Vertex CreateVertex(const T& Data) 
		{
			Vertex v = Vertex(this, Vertices.GetSize(), Data);
			Vertices.Add(v);
			return v;
		}
		
		/**
		 * Connect
		 *
		 *
		 */
		void Connect(const Vertex& v1, const Vertex& v2, W Data)
		{
			GetConnections(v1).Append(Edge(v1, v2, Data));
		}
		
		/**
		 * GetConnections
		 *
		 *
		 */
		List<Edge>& GetConnections(const Vertex& v1)
		{
			return Connections.Get(v1, true);
		}
		
		LinkedList<T> GetConnectionsX(const Vertex& v1) 
		{
			LinkedList<T> r;
			foreach(Edge, i, GetConnections(v1))
				r.Append((*i).Destination.Data);
			return r;
		}
		
		LinkedList<W> GetConnectionsY(const Vertex& v1)
		{
			LinkedList<W> r;
			foreach(Edge, i, GetConnections(v1))
				r.Append((*i).Data);
			return r;
		}
		
		/**
		 * GetDestinations
		 *
		 *
		 */
		LinkedList<Vertex> GetDestinations(const Vertex& v1)
		{
			LinkedList<Vertex> list;
			foreach(Edge, e, GetConnections(v1)) 
				list.append(e.Destination);
			return list;
		}
		
		/**
		 * IsConnected
		 *
		 *
		 */
		bool IsConnected(const Vertex& v1, const Vertex& v2) 
		{
			foreach(Edge, e, GetConnections(v1)) 
				if ((*e).Destination == v2)
					return true;
			return false;
		}

		/**
		 * Connections
		 *
		 *
		 */
		HashMap<Vertex, LinkedList<Edge> > Connections;
		
		/**
		 * Vertices
		 *
		 *
		 */
		HashSet<Vertex> Vertices;
		
	};
	
}

#endif