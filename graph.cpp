//Aidan Glina
//Navid Shamszadeh
//10/29/17

// FILE: graph.cpp (part of the namespace main_savitch_15)
// TEMPLATE CLASS IMPLEMENTED: graph<Item> (See graph.h for documentation.)
// This file is included in the header file and not compiled separately.
// INVARIANT for the graph class:
//   1. The number of vertices in the graph is stored in the member variable
//      many_vertices.
//   1. These vertices are numbered from 0 to many_vertices-1.
//   2. edges is the adjacency matrix for the graph (with true in edges[i][j]
//      to indicate an edge from vertex i to vertex j).
//   3. For each i < many_vertices, labels[i] is the label of vertex i.

#include <cassert>    // Provides assert
#include <cstdlib>    // Provides size_t
#include <set>        // Provides set
using std::size_t;

namespace main_savitch_15
{
  template <class Item>
  graph<Item>::graph (size_t initial_allocation = 10) : many_vertices(0), allocated(initial_allocation)
  {
	 edges = new bool*[allocated];
	 for(size_t i = 0; i < allocated; ++i)
	 {
		edges[i] = new bool[allocated];
	 }
	 labels = new Item*[allocated];
  }

  template <class Item>
  void graph<Item>::add_edge(size_t source, size_t target)
  // Library facilities used: cstdlib
  {
  	edges[source][target] = true;
  }

  template <class Item>
  void graph<Item>::add_vertex(const Item& label)
  // Library facilities used: cassert, cstdlib
  {
	 size_t new_vertex_number;
	 size_t other_number;
	 //first check if we need to allocate more memory
	 new_vertex_number = many_vertices;
	 many_vertices++;
	 if (many_vertices >= allocated) //this might have some bugs
	 {
	 	size_t old_allocated = allocated;
	 	allocated += 1;
	 	bool **new_edges = new bool*[allocated];
	 	for (size_t i = 0; i < allocated; ++i) //create new 2d dynamic array
	 	{
	 		new_edges[i] = new bool[allocated];
	 	}
	 	for (size_t i = 0; i < allocated; ++i) //put values in old array into new one
	 	{
	 		for (size_t j = 0; j < allocated; ++j)
	 		{
	 			if (i < old_allocated && j < old_allocated)  //there may be a quicker way to do this
	 			{
	 				new_edges[i][j] = edges[i][j];
	 			}else
	 			{
	 				new_edges[i][j] = false;
	 			}
	 		}
	 	}
	 	delete [] edges;
	 	edges = new_edges;
	 	//allocate more memory for labels array
	 	Item *new_labels = new Item*[allocated];
	 	for (size_t i = 0; i < allocated; ++i)
	 	{
	 		if (i < old_allocated)
	 		{
	 			new_labels[i] = labels[i];
	 		}else
	 		{
	 			new_labels[i] = label;
	 		}
	 	}
	 	delete [] labels;
	 	labels = new_labels;
	 }
	 for (other_number = 0; other_number < many_vertices; ++other_number) //the variable names suck
	 {
		  edges[other_number][new_vertex_number] = false;
		  edges[new_vertex_number][other_number] = false;
	 }
	 labels[new_vertex_number] = label;
  }

  template <class Item>
  bool graph<Item>::is_edge(size_t source, size_t target) const
  // Library facilities used: cassert, cstdlib
  {
	 assert(source < size( ));
	 assert(target < size( ));
	 return edges[source][target];
  }

  template <class Item>
  Item& graph<Item>::operator[ ] (size_t vertex)
  // Library facilities used: cassert, cstdlib
  {
	 assert(vertex < size( ));
	 return labels[vertex];     // Returns a reference to the label
  }

  template <class Item>
  Item graph<Item>::operator[ ] (size_t vertex) const
  // Library facilities used: cassert, cstdlib
  {
	 assert(vertex < size( ));
	 return labels[vertex];     // Returns only a copy of the label
  }

  template <class Item>
  std::set<size_t> graph<Item>::neighbors(size_t vertex) const
  // Library facilities used: cassert, cstdlib, set
  {
	 std::set<size_t> answer;
	 size_t i;

	 assert(vertex < size( ));

	 for (i = 0; i < size( ); ++i)
		{
	if (edges[vertex][i])
	  answer.insert(i);
		}
	 return answer;
  }

  template <class Item>
  void graph<Item>::remove_edge(size_t source, size_t target)
  // Library facilities used: cassert, cstdlib
  {
	 assert(source < size( ));
	 assert(target < size( ));
	 edges[source][target] = false;
  }
}
