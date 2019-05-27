#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

#include "node.h"
#include "edge.h"

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

    Graph() {}
    void push_node(N data) {
        NodeIte it;

        if (find_node(data, it))
            nodes.push_back(new node(data));

    }

    void push_edge(N node_1, N node_2, E weight = 0, bool dir = 0) {
        NodeIte it1, it2;
        if (!find_node(node_1, it1) || !find_node(node_2, it2))
            return;

        edge *temp = new edge(*it1, *it2, weight, dir);

        (*it1)->addEdge(temp);
        if (!dir)
            (*it2)->addEdge(temp);
        //TODO: corregir duplicados
    }

    void remove_node(N data) {
        NodeIte it;
        if (!find_node(data, it))
            return;
        node *ptr= *it;
        nodes.erase(it);
        delete ptr;
    }

    void remove_edge(N node_1, N node_2) {
        NodeIte it_node_1, it_node_2;
        EdgeIte it_edge;
        if (!find_node(node_1, it_node_1) || !find_node(node_2, it_node_2))
            return;
        if (!find_edge(*it_node_1, *it_node_2, it_edge))
            return;

        (*it_node_1)->removeEdge(*it_edge);

        if (!(*it_edge)->isDir())
            (*it_node_2)->removeEdge(*it_edge);
    }

    void print() {
        for (auto it : nodes) {
            cout << it->get_data() << endl;
            for (auto e : it->edges)
                cout << "\t" << e->nodes[0]->get_data() << " " << e->nodes[1]->get_data() << endl;
        }
    }

    bool isConexo() {
        for (auto&& it : nodes) {
            if (it->edges.empty())
                return false;
        }   return true;
    }

    ~Graph() {
        for (auto&& it : nodes) {
            delete it;
        }   nodes.clear();
    }

private:
    NodeSeq nodes;
    NodeIte ni;
    EdgeIte ei;

    bool find_node(N data, NodeIte &it) {
        for (it = nodes.begin(); it != nodes.end(); ++it) {
            if ((*it)->get_data() == data)
                return true;
        }   return false;
    }

    bool find_edge(node *&node_1, node *&node_2, EdgeIte &it) {
        for (it = node_1->edges.begin(); it != node_1->edges.end(); ++it) {
            if ((*it)->edgePair(node_1) == node_2)
                return true;
        }   return false;
    }
};

typedef Graph<Traits> graph;

#endif