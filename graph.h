#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <list>
#include <iostream>
#include <map>
#include <queue>
#include <algorithm>
#include <set>
#include <stack>
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

    Graph() {
        dir = false; }

    ~Graph() {
        for (auto&& it : nodes)
            delete it;
        nodes.clear();
    }


    NodeSeq dominating_set(){

        int n_dominated ; // numero de vertices dominados
        int level = 0;

        vector<N> domset;
        vector<N> mindomset;

        for(auto&& it : nodes){
            it->addNum_choise( node_degree( (*it)->get_data()) );
        }

        min_dom_set(level, domset, mindomset, &n_dominated );
    }

    int min_dom_set(E level,vector<N> &domset, vector<N> &mindomset,int *n_dominated ){

        auto n_extra = (size_t)ceil(((nodes.size()-*n_dominated)/(max_degree()+1)) );

        if((domset.size()+n_extra) >= mindomset.size()) {
            return 0;
        }

        if (*n_dominated==nodes.size() || level == nodes.size() ){

            if (domset.size() < mindomset.size()){
                mindomset= domset;
                return 1;

            }
        }

        //pinto azul nodo[level]
        //vecinos nodo[level]

        nodes[level].edges   ;
        //num_choise--
        nodes[it]->addNum_choise(-1) ;
    }

    E max_degree(){
        E max = 0;
        for (auto&& it : nodes) {
            if (node_degree(it->get_data()) > max )
                max = node_degree(it->get_data()) ;

        }
        return max;

    }
    int node_degree(N data) {
        findNode(data, ni);
        return ( (*ni)->degree() );
    }

    bool push_node(N data) {
        if (!find_node(data)){
            nodes.push_back(new node(data));
            return 1;
        }   return 0;
    }

    bool push_node(node *temp) {
        if (!find_node(temp->get_data())) {
            nodes.push_back(new node(temp));
            return 1;
        }   return 0;
    }

    bool push_edge(N node_1, N node_2, E weight = 0) {
        NodeIte it1, it2;
        if (!findNode(node_1, it1) || !findNode(node_2, it2))
            return 0;

        if (findEdge(*it1, *it2, ei))
            return 0;

        edge *temp = new edge(*it1, *it2, weight, dir);

        (*it1)->addEdge(temp);
        if (!dir)
            (*it2)->addEdge(temp);
        return 1;
    }

    bool push_edge(edge* new_edge) {
        NodeIte it1, it2;
        push_node(new_edge->first_node());
        push_node(new_edge->second_node());

        findNode(new_edge->first(), it1);
        findNode(new_edge->second(), it2);

        if (findEdge(*it1, *it2, ei))
            return 0;

        edge *temp = new edge(*it1, *it2, new_edge->get_data(), new_edge->isDir());

        (*it1)->addEdge(temp);

        if (!new_edge->isDir())
            (*it2)->addEdge(temp);
        return 1;
    }

    bool remove_node(N data) {
        if (!findNode(data, ni))
            return 0;
        node *ptr= *ni;
        nodes.erase(ni);

        for (auto eit : list_edges()) {
            if (eit->first_node() == ptr)
                eit->second_node()->removeEdge(eit);

            if (eit->second_node() == ptr)
                eit->first_node()->removeEdge(eit);
        }

        delete ptr;
        return 1;
    }

    bool remove_edge(N node_1, N node_2) {
        NodeIte it_node_1, it_node_2;
        EdgeIte it_edge;
        if (!findNode(node_1, it_node_1) || !findNode(node_2, it_node_2))
            return 0;
        if (!findEdge(*it_node_1, *it_node_2, it_edge))
            return 0;

        (*it_node_1)->removeEdge(*it_edge);

        if (!(*it_edge)->isDir())
            (*it_node_2)->removeEdge(*it_edge);
        return 1;
    }

    bool find_node(N data) {
        return findNode(data, ni);
    }

    bool find_edge(N node_1, N node_2) {
        NodeIte it_node_1, it_node_2;
        if (!findNode(node_1, it_node_1) || !findNode(node_2, it_node_2))
            return false;
        return findEdge(*it_node_1, *it_node_2, ei);
    }

    void print() {
        for (auto&& it : nodes) {
            cout << it->get_data() << endl;
            for (auto e : it->edges)
                cout << "\t" << e->first() << " " << e->second() << endl;
        }
    }

    EdgeSeq list_edges() {
        EdgeSeq edges;

        for(auto&& nit : nodes) {
            for (auto&& eit : nit->edges)
                edges.push_back(eit);
        }
        edges.unique();
        return edges;
    }

    NodeSeq list_nodes() {
        return nodes;
    }


    bool dir_graph() {
        dir = true;
        return dir;
    }

    bool is_dir() {
        return dir;
    }


    E count_nodes() {
        return nodes.size();
    }



    NodeSeq nodes;

private:
    NodeIte ni;
    EdgeIte ei;
    bool dir;


protected:
    bool findNode(N data, NodeIte &it) {
        for (it = nodes.begin(); it != nodes.end(); ++it) {
            if ((*it)->get_data() == data)
                return true;
        }   return false;
    }

    bool findEdge(node *&node_1, node *&node_2, EdgeIte &it) {
        for (it = node_1->edges.begin(); it != node_1->edges.end(); ++it) {
            if ((*it)->edgePair(node_1) == node_2)
                return true;
        }   return false;
    }


};

typedef Graph<Traits> graph;

#endif