#pragma once

#include <vector>
#include <limits>
#include <queue>

// TODO Remove
#include <iostream>

namespace astar{
	template<typename cost_type>
	struct node;
	template<typename cost_type>
	using edge_type = std::pair<node<cost_type>*, cost_type>;
	template<typename cost_type>
	struct node{		
		std::vector<edge_type<cost_type>> edges;
		cost_type tentative, heuristic;
		node(
			decltype(edges) edges = {},
			decltype(tentative) tentative
			= std::numeric_limits<decltype(tentative)>::max(),
			decltype(heuristic) heuristic = 0
		): edges(edges), tentative(tentative), heuristic(heuristic){}
	};
	
	/* Returns false if no path could be found. Otherwise, a path can be
	traced backwards from the goal by visiting the nodes with the lowest
	tentative cost values */
	template<typename cost_type>
	bool path(node<cost_type>& start, decltype(start) goal){
		auto priority = [](
			const node<cost_type>* lhs,
			const node<cost_type>* rhs
		){
			return lhs->tentative
				 + lhs->heuristic
				 > rhs->tentative
				 + rhs->heuristic;
		};
		
		std::priority_queue<
			node<cost_type>*,
			std::vector<node<cost_type>*>,
			decltype(priority)
		> open_set(priority);
		
		start.tentative = 0;
		open_set.push(&start);
		while(!open_set.empty()){			
			auto n = open_set.top();
			open_set.pop();
			for(auto& i: n->edges){
				auto proposed = n->tentative + i.second;
				if(i.first->tentative > proposed){
					i.first->tentative = proposed;
					open_set.push(i.first);
				}
			}
		}
		if(goal.tentative != std::numeric_limits<cost_type>::max()) return true;		
		return false;
	}
};
