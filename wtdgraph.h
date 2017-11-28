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
		//wtdgraph(const wtdgraph &source);
		virtual ~wtdgraph(); //why is this supposed to be virtual
		wtdgraph<Item> &operator=(const wtdgraph &source);

		void add_edge(size_t source, size_t target, size_t weight = 0);

		virtual void resize(size_t new_allocation); //why is this supposed to be virtual

		size_t edge_weight(size_t source, size_t target) const;
	private:
		map<size_t, size_t> *weights;

	};


	//constructor
	template <class Item> 
	wtdgraph<Item>::wtdgraph(size_t initial_allocation)
	: graph(initial_allocation)
	{
		//allocate memory for map array
		weights = new map<size_t, size_t>[initial_allocation];
	}


	//default constructor
	template <class Item>
	wtdgraph<Item>::wtdgraph()
	{
		//not sure how to define the default constructor
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
	void wtdgraph<Item>::add_edge(size_t source, size_t target, size_t weight = 0)
	{
		graph<Item>::add_edge(source, target);
		//resize map array regardless if we need to, since the resize function checks if it's necessary

		weights[source].insert(pair<size_t, size_t>(target, weight)); 

	}


	//resize override
	template <class Item>
	void wtdgraph<Item>::resize(size_t new_allocation)
	{
		//resize map array
		if(new_allocation < graph<Item>::allocated //not sure if size() is the correct thing to use here
		{
			return;
		}else
		{
			map<size_t, size_t> *new_weights = new map<size_t, size_t>[new_allocation];
			for (size_t i = 0; i < graph<Item>::allocated; ++i) //not sure if size() is the correct thing to use here
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
		
	}




}


#endif