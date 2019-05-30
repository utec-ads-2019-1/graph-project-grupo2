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

		friend class Kruskal;
		friend class Prim;
	
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

			if (it = node_exists(data); it == nodes.end())
			{
				newNode = new node(data);
				nodes.push_back(newNode);
			}
		}

		void remove_node(N data)
		{
			NodeIte it;

			if (it = node_exists(data); it == nodes.end()) 				return;
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

		void add_edge(N node1, N node2, E data, bool dir)
		{
			edge *newEdge1, *newEdge2;
			NodeIte it1, it2;
			EdgeIte it3;
			
			if (it1 = node_exists(node1); it1 == nodes.end()) 			return;
			if (it2 = node_exists(node2); it2 == nodes.end()) 			return;
			if (it3 = edge_exists(node1, node2); it3 != edges.end()) 	return;
			else
			{
				newEdge1 = new edge(*it1, *it2, data, dir);
				edges.push_back(newEdge1);

				(*it1)->edges.push_back(newEdge1);
				if (dir)
				{
					newEdge2 = new edge(*it2, *it1, data, dir);
					edges.push_back(newEdge2);
					(*it2)->edges.push_back(newEdge2);
				}
			}
		}

		void remove_edge(N n1, N n2)
		{
			NodeIte it1, it2;
			EdgeIte it3;

			if (it1 = node_exists(n1); it1 == nodes.end()) 				return;
			if (it2 = node_exists(n2); it2 == nodes.end()) 				return;
			if (it3 = edge_exists(n1, n2); it3 != edges.end())
			{
				for (auto it = (*it1)->edges.begin(); it != (*it1)->edges.end(); ++it)
				{
					if ((*it)->nodes[1]->get_data() == n2)
					{
						(*it1)->edges.erase(it);
					}
				}
				if ((*it3)->get_dir())
				{
					for (auto it = (*it2)->edges.begin(); it != (*it2)->edges.end(); ++it)
					{
						if ((*it)->nodes[1]->get_data() == n1)
						{
							(*it2)->edges.erase(it);
						}
					}
				}
				edges.erase(it3);
			}
		}

		void print_nodes()
		{
			std::cout << "Nodes:\n";
			for (auto node : nodes)
				std::cout << node->get_data() << '\n'; 
		}

		void print_edges()
		{
			std::cout << "Edges:\n";
			for (auto edge : edges)
				std::cout << edge->nodes[0]->get_data() << ' ' <<
				   	edge->nodes[1]->get_data() << '\n';
		}

	private:
		NodeIte node_exists(N data)
		{
			return std::find_if
				(
					nodes.begin(), nodes.end(),
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
					edges.begin(), edges.end(),
					[node1, node2](edge *obj) -> bool
					{
						return obj->nodes[0]->get_data() == node1 &&
						obj->nodes[1]->get_data() == node2;
					}
				);
		}

};

typedef Graph<Traits> graph;
using NodeSeq = typename Graph<Traits>::NodeSeq;
using EdgeSeq = typename Graph<Traits>::EdgeSeq;
using node = typename Graph<Traits>::node;
using edge = typename Graph<Traits>::edge;
using N = typename Graph<Traits>::N;
using E = typename Graph<Traits>::E;

#endif
