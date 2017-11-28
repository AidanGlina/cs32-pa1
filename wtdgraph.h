#ifndef WTDGRAPH_H
#define WTDGRAPH_H
#include "graph.h"
#include <map>
namespace main_savitch_15
{
	template <class Item>
	class wtdgraph : public graph<Item>
	{
	public:
		wtdgraph();
		wtdgraph(size_t initial_allocation);
		wtdgraph(const wtdgraph &source);
		virtual ~wtdgraph(); //why is this supposed to be virtual
		virtual void resize(size_t new_allocation); //why is this supposed to be virtual
		void add_edge(size_t source, size_t target, size_t weight = 0);
		void remove_edge(size_t source, size_t target);
		size_t edge_weight(size_t source, size_t target) const;
		wtdgraph<Item> &operator=(const wtdgraph &source);
	private:
		map<size_t, size_t> *weights;
	};


	//constructor
	template <class Item> 
	wtdgraph<Item>::wtdgraph(size_t initial_allocation) : graph<Item>::graph(initial_allocation)
	{
		//allocate memory for map array
		weights = new map<size_t, size_t>[initial_allocation];
	}


	//default constructor
	template <class Item>
	wtdgraph<Item>::wtdgraph()
	{
		//not sure how to define the default constructor
		weights = new map<size_t, size_t>[graph<Item>::allocated];
	}

	//copy constructor
	template<class Item>
	wtdgraph<Item>::wtdgraph(const wtdgraph &source) : graph<Item>::graph(source)
	{
		//copy weights
		weights = new map<size_t, size_t>[source.allocated];
		for(size_t i = 0; i < source.allocated; ++i)
		{
			weights[i] = source.weights[i];
			for(size_t j = 0; j < )

		}
	}


	//destructor
	template <class Item>
	wtdgraph<Item>::~wtdgraph()
	{
		//parent destructor called automatically at the end
		//weights is a 1-D dynamic array
		delete [] weights;
	}


	//add_edge override
	template <class Item>
	void wtdgraph<Item>::add_edge(size_t source, size_t target, size_t weight)
	{
		graph<Item>::add_edge(source, target);
		//resize map array regardless if we need to, since the resize function checks if it's necessary
		//resize(source);
		weights[source].insert(pair<size_t, size_t>(target, weight)); 

	}


	//resize override
	template <class Item>
	void wtdgraph<Item>::resize(size_t new_allocation)
	{
		//resize map array
		if(new_allocation < graph<Item>::allocated) 
		{
			return;
		}else
		{
			map<size_t, size_t> *new_weights = new map<size_t, size_t>[new_allocation];
			for (size_t i = 0; i < graph<Item>::allocated; ++i) 
			{
				new_weights[i] = weights[i];	
			}
			delete [] weights;
			weights = new_weights;
			graph<Item>::resize(new_allocation);
		}
	}

	//edge_weight
	template <class Item>
	size_t wtdgraph<Item>::edge_weight(size_t source, size_t target) const
	{
		assert(graph<Item>::is_edge(source, target));
		return weights[source][target]; //not sure if this is right
	}

	//assignment operator
	template<class Item>
	wtdgraph<Item>& wtdgraph<Item>::operator=(const wtdgraph<Item> &source)
	{
		//stub
		return *this; 
	}

	template<class Item>
	void wtdgraph<Item>::remove_edge(size_t source, size_t target)
	{
		graph<Item>::remove_edge(source, target);
		weights[source].erase(target);

		return; 
	}




}


#endif