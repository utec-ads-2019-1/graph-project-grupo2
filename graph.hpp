#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

#include "node.hpp"
#include "edge.hpp"

using namespace std;

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
        typedef vector<node*> NodeSeq;
        typedef list<edge*> EdgeSeq;
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
			// TODO find if node already exists
			
		}

		void add_edge(N node1, N node2, bool dir)
		{
			edge* newEdge;
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
				newEdge = new edge(*it1, *it2, dir);
				edges.push_back(newEdge);

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
};

typedef Graph<Traits> graph;

#endif
