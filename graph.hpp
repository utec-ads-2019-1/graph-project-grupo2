#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <iterator>

#include "node.hpp"
#include "edge.hpp"


class Traits {
	public:
		typedef char N;
		typedef int E;
};

template <typename Tr>
class Graph {
    public:
        typedef Graph<Tr> self;
        typedef Node<self> node;
        typedef Edge<self> edge;
        typedef std::vector<node*> NodeSeq;
        typedef std::list<edge*> EdgeSeq;
        typedef typename Tr::N N;
        typedef typename Tr::E E;
        typedef typename NodeSeq::iterator NodeIte;
        typedef typename EdgeSeq::iterator EdgeIte;

    private:
        NodeSeq nodes;
		EdgeSeq edges;
        NodeIte ni;
        EdgeIte ei;
	
	public:
		Graph()
		{
			// TODO
		}

		~Graph()
		{
			// TODO
		}

		
		void add_node(N data)
		{
			node* newNode;
			NodeIte it;

			it = node_exists(data);
			if (it == nodes.end())
			{
				newNode = new node(data);
				nodes.push_back(newNode);
			}
		}

		void remove_node(N data)
		{
			NodeIte it;

			it = node_exists(data);
			if (it == nodes.end())
			{
				return;
			}
			else
			{
				for (auto i = edges.begin(); i != edges.end(); ++i)
				{
					if ((*i)->nodes[0]->get_data() == data ||
							(*i)->nodes[1]->get_data() == data)
					{
						edges.erase(i);
					}
				}
				nodes.erase(it);
			}
		}

		void add_edge(N node1, N node2, bool dir)
		{
			edge *newEdge1, *newEdge2;
			NodeIte it1, it2;
			EdgeIte it3;
			/*
			 * Check nodes existence
			 */
			it1 = node_exists(node1);
			if (it1 == nodes.end())
			{
				return;
			}
			it2 = node_exists(node2);
			if (it2 == nodes.end())
			{
				return;
			}
			/*
			 * Check if this edge already exists
			 */
			it3 = edge_exists(node1, node2);
			if (it3 != edges.end())
			{
				return;
			}
			else
			{
				newEdge1 = new edge(*it1, *it2, dir);
				edges.push_back(newEdge1);
				if (dir)
				{
					newEdge2 = new edge(*it2, *it1, dir);
					edges.push_back(newEdge2);
				}
			}
		}

		void remove_edge(N n1, N n2)
		{
			NodeIte it1, it2;
			EdgeIte it3;

			it1 = node_exists(n1);
			if (it1 == nodes.end())
			{
				return;
			}
			it2 = node_exists(n2);
			if (it2 == nodes.end())
			{
				return;
			}
			it3 = edge_exists(n1, n2);
			if (it3 != edges.end())
			{
				edges.erase(it3);
			}
		}

		void print_nodes()
		{
			std::cout << "Nodes:\n";
			for (auto i : nodes)
			{
				std::cout << i->get_data() << '\n'; 
			}
		}

		void print_edges()
		{
			std::cout << "Edges:\n";
			for (auto i : edges)
			{
				std::cout << 
					i->nodes[0]->get_data() << ' ' << i->nodes[1]->get_data() 
					<< '\n';
			}
		}

	private:
		NodeIte node_exists(N data)
		{
			return std::find_if
				(
					nodes.begin(),
					nodes.end(),
					[data](node *obj) -> bool
					{
						return obj->get_data() == data;
					}
				);
		}

		EdgeIte edge_exists(N node1, N node2)
		{
			return std::find_if
				(
					edges.begin(),
					edges.end(),
					[node1, node2](edge *obj) -> bool
					{
						return obj->nodes[0]->get_data() == node1 &&
						obj->nodes[1]->get_data() == node2;
					}
				);
		}

};

typedef Graph<Traits> graph;

#endif
