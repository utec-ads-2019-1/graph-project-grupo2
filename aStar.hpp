#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <cmath>
#include <vector>
#include <map>

#include "graph.hpp"

class aStar : public graph
{
	private:
		std::map<N, node*>				nodes_map;
		std::map<int, N>			available_nodes;
		std::vector<std::vector<int>>	table;

	public:
		aStar(graph g)
		{
			for (auto n : g.nodes)
				nodes_map[n->data] == n;
		}
		static aStar get_path(graph g, N start, N finish)
		{
			aStar res(g);
			auto c_node = res.nodes_map[start];
			std::vector<int> f{}

		}

		int heuristic(node *a, node *b)
		{
			auto dx = std::abs(a->x - b->x);
			auto dy = std::abs(a->y - b->y);
			return (dx + dy);
		}
};

#endif
