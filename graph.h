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

        void push_node(N data) {
            if (!find(data))
                nodes.push_back(new node(data));
        }

        void push_node(N data, double x, double y) {
            if (!find(data))
                nodes.push_back(new node(data, x, y));
        }

        void push_edge(N node_1, N node_2, E weight = 0) {
            NodeIte it1, it2;
            if (!find_node(node_1, it1) || !find_node(node_2, it2))
                return;
            
            if (find(node_1, node_2))
                return;
            
            edge *temp = new edge(*it1, *it2, weight, dir);

            (*it1)->addEdge(temp);
            if (!dir)
                (*it2)->addEdge(temp);
            //TODO: corregir duplicados
        }

        void push_node(node *temp) {
            if (!find(temp->get_data()))
                nodes.push_back(new node(temp));
        }

        void push_edge(edge* new_edge) {
            NodeIte it1, it2;
            push_node(new_edge->first_node());
            push_node(new_edge->second_node());

            find_node(new_edge->first(), it1);
            find_node(new_edge->second(), it2);

            edge *temp = new edge(*it1, *it2, new_edge->get_data(), new_edge->isDir());            

            (*it1)->addEdge(temp);

            if (!new_edge->isDir())
                (*it2)->addEdge(temp);

            //Corregir duplicados
        }

        void remove_node(N data) {
            if (!find_node(data, ni))
                return;
            node *ptr= *ni;
            nodes.erase(ni);
            //falta remover de anexos
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

        EdgeSeq list_edges() {
            EdgeSeq edges;
            for(auto&& nit : nodes) {
                for (auto&& eit : nit->edges)
                    edges.push_back(eit);
            }
            return edges;
        }

        NodeSeq list_nodes() {
            return nodes;
        }

        bool isConexo() {
            map<N, N> reg;
            
            for(auto&& nit : nodes) {
                for (auto&& eit : nit->edges)
                    disjoint_set(reg, eit->first(), eit->second());
            }
            set<N> parents;
            for (auto it : reg) {
                parents.insert(get_parent(reg, it.first));
            }
            return parents.size() == 1;
        }


        void on_render(Interface &interface) {
            for (auto&& it : nodes)
                it->on_render(interface);
        }

        self* prim(N init = 0) {
            map<N, bool> reg;
            set<edge*, cmp> edges;
            
            ni = nodes.begin();

            if (init != 0)
                find_node(init, ni);

            for (auto eit : (*ni)->edges) {
                edges.insert(eit);
            }
            reg[(*ni)->get_data()] = 1;
            
            self* new_graph = new self;
            bool val = 1;
            while (val != 0) {
                val = 0;
                for (auto it : edges) {
                    if (!reg[it->first()] || !reg[it->second()]) {
                        new_graph->push_edge(it);
                        if (!reg[it->first()]) {
                            for (auto eit : it->first_node()->edges)
                                edges.insert(eit);
                            
                            reg[it->first()] = 1;
                        } else {
                            for (auto eit : it->second_node()->edges)
                                edges.insert(eit);
                            
                            reg[it->second()] = 1;
                        }
                        val = 1;
                        break;
                    }
                }
            }
            return new_graph;
        }

        self* kruskal() {
            map<N, N> reg;
            set<edge*, cmp> edges;
            
            for(auto&& nit : nodes) {
                reg[nit->get_data()] = 0;
                for (auto&& eit : nit->edges)
                    edges.insert(eit);
            }

            self* new_graph = new self;
            
            for (auto it : edges) {
                if (disjoint_set(reg, it->first(), it->second()))
                    new_graph->push_edge(it);
            }
            
            edges.clear();
            reg.clear();

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

        bool find(N data) {             //nodes
            return find_node(data, ni);
        }

        bool find(N node_1, N node_2) { //edges
            NodeIte it_node_1, it_node_2;
            if (!find_node(node_1, it_node_1) || !find_node(node_2, it_node_2))
                return false;
            return find_edge(*it_node_1, *it_node_2, ei);
        }

        float density() {
            int num_nodes, num_edges;
            float d;
            
            for (auto n : nodes) {
                ++num_nodes;
                num_edges += n->degree();
            }            
            return num_edges / (num_nodes * (num_nodes - 1));
        }

        void node_degree(N data) {
            find_node(data, ni);
            return ni->degee();
        }

        void type_node(N data) {
            if (!dir)
                return;
            
            if (!find_node(data, ni))
                return;
            //falta
        }

        bool is_bipartito() {
            map<N, E> reg;
            queue<N> priority;

            if (nodes.size() == 0)
                return true;
            
            E color = 1;
            node* temp;
            priority.push(nodes[0]);
            reg[nodes[0]] = color;

            while(priority.size() > 0) {
                reg[priority.front()] = color;
                for (edge e : priority.front()->edges) {
                    temp = e.edgePair(priority.front());
                    if (reg[temp->get_data()] == 0)
                        priority.push(temp);
                    else {
                        if (reg[temp->get_data()] != -color)
                            return false;
                    }
                }
                priority.pop();
                color = -color;
            }
            return true;
        }

        self* DFS(N init = 0) {
            map <N, bool> reg;
            
            stack<node*> priority;

            self *new_graph = new self;

            if (nodes.size() == 0)
                return new_graph;

            node *ptr, *temp;
            int count;

            ni = nodes.begin();

            if (init != 0)
                find_node(init, ni);

            priority.push(nodes[0]);
            reg[(*ni)->get_data()] = 1;
            
            while (priority.size() > 0) {
                count = 0;
                ptr = priority.top();
                
                for (auto e : ptr->edges) {
                    temp = e->edgePair(ptr);
                    if (reg[temp->get_data()] == 0) {
                        reg[temp->get_data()] = 1;
                        priority.push(temp);
                        new_graph->push_edge(e);
                        ++count;
                        break;
                    }
                }
                if (count == 0) {
                    priority.pop();
                }
            }
            reg.clear();
            return new_graph;
        }

        self* BFS() {
            map <N, bool> reg;
            queue<node *> priority;
            self *new_graph = new self;

            if (nodes.size() == 0)
                return new_graph;

            node *ptr, *temp;
            priority.push(nodes[0]);
            reg[nodes[0]->get_data()] = 1;

            while (priority.size() > 0) {             
                for (auto e : priority.front()->edges) {
                    temp = e->edgePair(priority.front());
                    if (!reg[temp->get_data()]) {
                        priority.push(temp);
                        new_graph->push_edge(e);
                        reg[temp->get_data()] = 1;
                    }
                }   priority.pop();
            }
            reg.clear();

            return new_graph;
        }

        E count_nodes() {
            return nodes.size();
        }

        NodeSeq nodes;

    private:
        NodeIte ni;
        EdgeIte ei;
        bool dir;
    
    public:
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

        bool disjoint_set(map<N, N> &reg, N data_1, N data_2) {
            N par_1 = get_parent(reg, data_1);
            N par_2 = get_parent(reg, data_2);
            
            if (par_1 != par_2)
                reg[par_1] = par_2;
            
            return par_1 != par_2;
        }

        N get_parent(map<N, N> &reg, N data) {
            if (reg[data] == 0) {
                reg[data] = data;
                return data;
            }

            N temp = data;
            
            while(temp != reg[temp])
                temp = reg[temp];
            reg[data] = temp;
            return temp;
        }
};

typedef Graph<Traits> graph;


struct cmp {
    bool operator() (Edge<graph> *lhs, Edge<graph> *rhs) const {
        if (lhs->get_data() == rhs->get_data()) {
            if (lhs->first() == rhs->first())
                return lhs->second() < rhs->second();
            else
                return lhs->first() < rhs->first();
        }
        return lhs->get_data() < rhs->get_data();
    }
};

#endif