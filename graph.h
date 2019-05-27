#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <set>
#include <stack>
#include <GL/glut.h>
#include "node.h"
#include "edge.h"

using namespace std;

class Traits {
	public:
		typedef char N;
		typedef int E;
};

struct cmp;

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

        Graph() { dir = false; }
        void push_node(N data, double x, double y) {
            if (!find(data))
                nodes.push_back(new node(data, x, y));
                
        }

        void push_edge(N node_1, N node_2, E weight = 0) {
            NodeIte it1, it2;
            if (!find_node(node_1, it1) || !find_node(node_2, it2))
                return;
            
            edge *temp = new edge(*it1, *it2, weight, dir);

            (*it1)->addEdge(temp);
            if (!dir)
                (*it2)->addEdge(temp);
            //TODO: corregir duplicados
        }

        void push_edge(edge* new_edge) {
            push_node(new_edge->first(), 0,0);// Añadir posiciones
            find_node(new_edge->first(), ni);
            (*ni)->addEdge(new_edge);

            push_node(new_edge->second(), 0,0);// Añadir posiciones
            find_node(new_edge->second(), ni);
            if (!new_edge->isDir())
                (*ni)->addEdge(new_edge);
        }

        void remove_node(N data) {
            if (!find_node(data, ni))
                return;
            node *ptr= *ni;
            nodes.erase(ni);
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
            for (auto&& it : nodes) {
                cout << it->get_data() << endl;
                for (auto e : it->edges)
                    cout << "\t" << e->first() << " " << e->second() << endl;
            }
        }

        bool isConexo() {
            //Falta
        }


        void on_render(Interface &interface) {
            for (auto&& it : nodes)
                it->on_render(interface);
        }

        Graph<Traits>* prim(N data) {
            if (!find_node(data, ni))
                exit(0);
            
            stack<edge*> p;
        }

        Graph<Traits>* kruskal() {
            int size = nodes.size();

            set<edge*, cmp> edges;

            for(auto&& nit : nodes) {
                for (auto&& eit : nit->edges)
                    edges.insert(eit);
            }
            
            Graph<Traits>* new_graph = new Graph<Traits>();
            
            auto e_it = edges.begin();

            while(size > new_graph->nodes.size() && e_it != edges.end()) {
                if (!new_graph->find((*e_it)->first()) || !new_graph->find((*e_it)->second()))
                    new_graph->push_edge(*e_it);
                ++e_it;
            }
            
            edges.clear();

            return new_graph;
        }
        
        ~Graph() {
            for (auto&& it : nodes)
                delete it;
            nodes.clear();
        }

        void dir_graph() {
            dir = true;
        }

        bool is_dir() {
            return dir;
        }

        bool find(N data) {
            return find_node(data, ni);
        }

        bool find(N node_1, N node_2) {
            NodeIte it_node_1, it_node_2;
            if (!find_node(node_1, it_node_1) || !find_node(node_2, it_node_2))
                return false;            
            return find_edge(it_node_1, it_node_2, ei);
        }

        float density() {
            int num_nodes, num_edges;
            float d;
            
            for (auto n : nodes) {
                ++num_nodes;
                num_edges += n->edges.size();
            }
            
            return num_edges / (num_nodes (num_nodes - 1));
        }

        NodeSeq nodes;

    private:
        NodeIte ni;
        EdgeIte ei;
        bool dir;
        
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


struct cmp {
    bool operator() (Edge<graph> *lhs, Edge<graph> *rhs) const {
        return lhs->get_data() < rhs->get_data();
    }
};

#endif