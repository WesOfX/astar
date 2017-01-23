#pragma once

#include <vector>
#include <limits>
#include <queue>

namespace astar{
	template<typename cost_type>
	struct node;
	template<typename cost_type>
	using edge = std::pair<node<cost_type>*, cost_type>;
	template<typename cost_type>
	struct node{		
		std::vector<edge<cost_type>> edges;
		cost_type tentative, heuristic;
		node(
			decltype(edges) edges = {},
			decltype(tentative) tentative
			= std::numeric_limits<decltype(tentative)>::max(),
			decltype(heuristic) heuristic = 0
		): edges(edges), tentative(tentative), heuristic(heuristic){}
	};
	template<typename cost_type>
	cost_type path(node<cost_type>& start, decltype(start) goal){
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
			if(n == &goal) return goal.tentative;
			open_set.pop();
			for(auto& i: n->edges){
				if(i.first->tentative
				== std::numeric_limits<cost_type>::max()
				){
					i.first->tentative = n->tentative + i.second;
					open_set.push(i.first);
				}
			}
		}	
		return std::numeric_limits<cost_type>::max();
	}
};
