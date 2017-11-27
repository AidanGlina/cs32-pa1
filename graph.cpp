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
#include <iostream>
using namespace std;
using std::size_t;

namespace main_savitch_15
{


  template <class Item>
  graph<Item>::graph () : many_vertices(0), allocated(10)
  {
  	edges = new bool*[allocated];
	for(size_t i = 0; i < allocated; ++i)
	{
		edges[i] = new bool[allocated];
	}
	labels = new Item[allocated];
  }	
  template <class Item>
  graph<Item>::graph (size_t initial_allocation) : many_vertices(0), allocated(initial_allocation)
  {
	 edges = new bool*[allocated];
	 for(size_t i = 0; i < allocated; ++i)
	 {
		edges[i] = new bool[allocated];
	 }
	 labels = new Item[allocated];
  }
	
  template <class Item>
  graph<Item>::graph (const graph &source) : many_vertices(0), allocated(source.allocated)
  {
	 edges = new bool*[allocated];
	 for(size_t i = 0; i < allocated; ++i)
	 {
		edges[i] = new bool[allocated];
		for(size_t j = 0; j < allocated; ++j)
		{
			edges[i][j] = source.edges[i][j];
		}
	 }
	 labels = new Item[allocated];

	 for(size_t i = 0; i < allocated; ++i)
	 {
		labels[i] = source.labels[i];
	 }
	 many_vertices = source.many_vertices;
  }








template <class Item>
graph<Item>& graph<Item>::operator=(const graph<Item> &source)
{
		size_t new_allocated = source.allocated;
		bool **new_edges = new bool*[new_allocated]; //same size as source allocated
		for(size_t i = 0; i < new_allocated; ++i)
		{
			new_edges[i] = new bool[new_allocated];
		}
		for(size_t i = 0; i < new_allocated; ++i)
		{
			for(size_t j = 0; j < new_allocated; ++j)
			{
				new_edges[i][j] = source.edges[i][j]; 
			}
		}
		Item *new_labels = new Item[new_allocated];

		for(size_t i = 0; i < new_allocated; ++i)
		{
			new_labels[i] = source.labels[i];
		}
		for (size_t i = 0; i < allocated; ++i)
		{
			delete [] edges[i];
		}
		delete [] edges;
		delete [] labels;
		allocated = source.allocated;
		edges = new_edges;
		labels = new_labels;
		many_vertices = source.many_vertices;
		return *this;
}



  template <class Item>
  void graph<Item>::resize(size_t new_allocated)
  {
  	if (new_allocated < size())
  	{
  		return;
  	}
  	bool **new_edges = new bool*[new_allocated];
  	for (size_t i =0; i< new_allocated; ++i)
  	{
  		new_edges[i] = new bool[new_allocated];
  	}
	for(size_t i = 0; i < allocated; ++i)
	{
		for(size_t j = 0; j < allocated; ++j)
		{
			new_edges[i][j] = edges[i][j]; 
		}
	}
	Item *new_labels = new Item[new_allocated];

	for(size_t i = 0; i < allocated; ++i)
	{
		new_labels[i] = labels[i];
	}
	for (size_t i = 0; i < allocated; ++i)
	{
		delete [] edges[i];
	}
	delete [] edges;
	delete [] labels;

    allocated = new_allocated;
	edges = new_edges;
	labels = new_labels;
  }


  template <class Item>
  graph<Item>::~graph()
  {
  	//since it's a 2d dynamic array we might have to do this, but im not sure:
  	for (size_t i = 0; i < allocated; ++i)
  	{
  		delete [] edges[i];
  	}
  	delete [] edges;
  	delete [] labels;
  	many_vertices = 0;
  }
  template <class Item>
  void graph<Item>::add_edge(size_t source, size_t target)
  // Library facilities used: cstdlib
  {

  	if(source > allocated)
		resize(source);
	if(target > allocated)
		resize(target);
	
  	edges[source][target] = true;
	//edges[target][source] = false;
  }

  template <class Item>
  void graph<Item>::add_vertex(const Item& label) 
  // Library facilities used: https://my.sa.ucsb.edu/gold/CourseDetailInfo.aspxcassert, cstdlib
  {
	 size_t new_vertex_number;
	 //size_t other_number;
	 //first check if we need to allocate more memory
	 //cout << "many_vertices: " << many_vertices << endl;
	 new_vertex_number = many_vertices;
	 ++many_vertices;
	 if (many_vertices >= allocated) 
	 {
	 	resize(many_vertices);	
	 }
	 for (size_t i = 0; i < many_vertices; ++i)
	 {
	 	edges[i][new_vertex_number] = false;
        edges[new_vertex_number][i] = false;
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
	 if (vertex >= size())
	 {
	 	resize(vertex);
	 }
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

