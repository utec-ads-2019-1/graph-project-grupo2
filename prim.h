#ifndef PRIM_H
#define PRIM_H


#include <map>
#include <random>
#include <limits>
#include <iterator>

#include "graph.h"

class Prim : public graph
{
	private:
		typedef std::uniform_int_distribution<std::mt19937::result_type> r_int; 
		typedef std::map<node*, std::pair<int, node*>> table_type; 
		int total_edge_weight;
		int inf = std::numeric_limits<int>::max();
		graph g;
		graph prim_g;
		table_type table;

	public:
		Prim(graph g) : g(g)
		{
			prim_g.nodes = g.nodes;
			create_table();
			select_random_node();
			while (table.empty() != true)
			{
				auto min_node = extract_min(table);
				for (auto edge : min_node->edges)
				{
					auto adj_node = edge->nodes[1];
					auto found = table.find(adj_node); 
					if (found != table.end())
					{
						if (edge->get_data() < table.at(adj_node).first)
						{
							table.at(adj_node).second = min_node;
							table.at(adj_node).first = edge->get_data();
						}
					}
				}
			}
		}
		~Prim() = default;


		void create_table()
		{
			for (auto node : g.nodes)
				table[node] = std::make_pair(inf, nullptr);
		}
		
		void select_random_node()
		{
			std::random_device rd;
			std::mt19937 rng(rd());
			r_int dist(0, g.nodes.size() - 1);
			int number = dist(rng);
			auto it = table.begin();
			std::advance(it, number);
			std::cout << "Initial node: " << (*it).first->get_data() << '\n';
			table[(*it).first] = std::make_pair(0, nullptr);
		}

        void print()
		{
			total_edge_weight = 0;
			std::cout << "nodes: ";
			for (auto node : prim_g.nodes)
				std::cout << node->get_data() << ' ';
			std::cout << '\n';
			int edges_size = prim_g.list_edges().size();
			int i = 1;
			std::cout << "edges: {";
			for (auto edge : prim_g.list_edges())
			{
				total_edge_weight = total_edge_weight + edge->get_data();
				std::cout << '{' << edge->nodes[0]->get_data() << ", " <<
					edge->nodes[1]->get_data() << '}';
				if (i != edges_size)
					std::cout << ", ";
				++i;
			}
			std::cout << "}\n";
			std::cout << "Total edge weight is " << total_edge_weight << '\n';
		}

		node* extract_min(table_type &t)
		{
			EdgeIte it;

			node *min_n = t.begin()->first;
			for (auto row : t)
			{
				if (row.second.first < t.at(min_n).first)
					min_n = row.first;
			}
			
			if (t.at(min_n).second != nullptr)
			{   
                NodeIte n, m;
				prim_g.find_node(min_n->get_data(), n);
				prim_g.find_node(t.at(min_n).second->get_data(), m);
				
				if (g.find_edge(*n, *m , it))
				    prim_g.push_edge(*it);
			}
			t.erase(t.find(min_n));
			
			return min_n;
		}
};

#endif