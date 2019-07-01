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
    typedef char	N;
    typedef int		E;
};

template <typename Tr>
class Graph {
public:
    typedef Graph<Tr>	self;
    typedef Node<self>	node;
    typedef Edge<self>	edge;
    typedef std::vector<node*> 	NodeSeq;
    typedef std::list<edge*>	EdgeSeq;
    typedef typename Tr::N N;
    typedef typename Tr::E E;
    typedef typename NodeSeq::iterator NodeIte;
    typedef typename EdgeSeq::iterator EdgeIte;

    friend class dijkstra ;


protected:
    NodeSeq nodes;
    EdgeSeq edges;

public:
    Graph()
    {
        // TODO
    }

    ~Graph()
    {
        unsigned nodes_size;

        nodes_size = nodes.size();
        for (size_t i = 0; i < nodes_size; ++i)
            delete nodes[i];
        nodes.clear();
    }

    void add_node(N data, float x, float y)
    {
        node* newNode;
        NodeIte it;

        it = node_exists(data);
        if ( it == nodes.end())
        {
            newNode = new node(data, x, y);
            nodes.push_back(newNode);
        }
    }

    void remove_node(N data)
    {
        NodeIte it;
        EdgeIte e_it;

        it = node_exists(data);
        if ( it == nodes.end())
            return;
        else
        {
            for (e_it = edges.begin(); e_it != edges.end(); ++e_it)
            {
                if ((*e_it)->nodes[0]->data == data ||
                    (*e_it)->nodes[1]->data == data)
                    edges.erase(e_it);
            }
            nodes.erase(it);
        }
    }

    void add_edge(N node1, N node2, E data, bool dir)
    {
        edge *newEdge1, *newEdge2;
        NodeIte it1, it2;
        EdgeIte it3;

        it1 = node_exists(node1);
        if ( it1 == nodes.end())
            return;
        it2 = node_exists(node2);
        if ( it2 == nodes.end())
            return;
        it3 = edge_exists(node1, node2);
        if ( it3 != edges.end())
            return;
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

        it1 = node_exists(n1);
        if ( it1 == nodes.end())
            return;
        it2 = node_exists(n2);
        if ( it2 == nodes.end())
            return;
        it3 = edge_exists(n1, n2);
        if ( it3 != edges.end())
        {
            for (auto it = (*it1)->edges.begin(); it != (*it1)->edges.end(); ++it)
                if ((*it)->nodes[1]->data == n2)
                    (*it1)->edges.erase(it);
            if ((*it3)->dir)
                for (auto it = (*it2)->edges.begin(); it != (*it2)->edges.end(); ++it)
                    if ((*it)->nodes[1]->data == n1)
                        (*it2)->edges.erase(it);
            edges.erase(it3);
        }
    }

    void print_nodes()
    {
        unsigned nodes_count, nodes_size;;

        nodes_count = 1;
        nodes_size = nodes.size();
        std::cout << "Nodes: {";
        for (auto node : nodes)
        {
            std::cout << node->data;
            if (nodes_count++ < nodes_size)
                std::cout << ", ";
        }
        std::cout << "}\n";
    }

    void print_edges()
    {
        unsigned edges_count, edges_size;

        edges_count = 1;
        edges_size = edges.size();
        std::cout << "Edges: {";
        for (auto edge : edges)
        {
            std::cout << '(';
            std::cout << edge->nodes[0]->data;
            std::cout << ", ";
            std::cout << edge->nodes[1]->data;
            std::cout << ')';

            std::cout << (edges_count++ < edges_size ? ", " : "");
        }
        std::cout << "}\n";
    }

    void draw(sf::RenderWindow &window)
    {
        for (auto edge : edges)
            edge->draw(window);
        for (auto node : nodes)
            node->draw(window);
    }

private:
    NodeIte node_exists(N data)
    {
        return std::find_if
                (
                        nodes.begin(), nodes.end(),
                        [data](node *obj) -> bool
                        {
                            return obj->data == data;
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
                            return obj->nodes[0]->data == node1 &&
                                   obj->nodes[1]->data == node2;
                        }
                );
    }

};

typedef Graph<Traits> graph;

#endif