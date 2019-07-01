#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include <set>
#include <map>

#include "graph.hpp"

class Kruskal
{
	private:
		NodeSeq nodes;
		EdgeSeq edges;
		std::set<node*> node_set;
		unsigned int n_nodes;
		std::multimap<E, edge*> edges_dict;

		struct EdgeCmp
		{
			bool operator()(const edge& lhs, const edge& rhs) const
			{
				return lhs.data < rhs.data;
			}
		};

	public:
		Kruskal(graph g) : nodes(g.nodes)
		{
			n_nodes = nodes.size(); 
			std::cout << "n_nodes: " << n_nodes << '\n';
			for (auto i : g.edges)
			{
				edges_dict.insert(std::make_pair(i->data, i));
			}
			operate();
		}

		void print_nodes()
		{
			for (auto i : nodes)
			{
				std::cout << i->get_data() << '\n'; 
			}
		}

		void print_edges()
		{
			for (auto i : edges)
			{
				std::cout << i->nodes[0]->get_data() << " - " << i->nodes[1]->get_data() << '\n';
			}
		}

		void print_result()
		{
			print_nodes();
			print_edges();
		}

		void operate()
		{
			int n = 1;

			for (auto i : edges_dict)
			{
				if (n == n_nodes)
				{
					break;
				}
				if (node_set.find(i.second->nodes[1]) == node_set.end() ||
						node_set.find(i.second->nodes[1]) == node_set.end())
				{
					node_set.insert(i.second->nodes[0]);
					node_set.insert(i.second->nodes[1]);
					edges.push_back(i.second);
					++n;
				}
			}
		}
};

#endif
