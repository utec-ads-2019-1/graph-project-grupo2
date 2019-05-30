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

#ifndef NDEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif

class Traits {
	public:
		typedef char N;
		typedef int E;
};

enum tipo_nodo {
    Fuente,
    Hundido,
    Aislado,
    Hoja,
    Normal
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

        ~Graph() {
            for (auto&& it : nodes)
                delete it;
            nodes.clear();
        }

        bool push_node(N data) {
            if (!find_node(data)){
                nodes.push_back(new node(data));
                return 1;
            }   return 0;
        }

        bool push_node(N data, double x, double y) {
            if (!find_node(data)) {
                nodes.push_back(new node(data, x, y));
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

        bool is_conexo() {
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

        bool is_strongly_connected() {
            self *dfs = DFS();

            for (auto eit : dfs->list_edges()) {
                eit->swap_nodes();
            }
            self *temp = dfs->DFS();

            return temp->count_nodes() != dfs->count_nodes();
        }

        bool dir_graph() {
            dir = true;
            return dir;
        }

        bool is_dir() {
            return dir;
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

        E count_nodes() {
            return nodes.size();
        }

        int node_degree(N data) {
            if (dir)
                return degree_in(data) + degree_out(data);
            return degree_out(data);
        }

        int degree_in(N data) {
            if (!dir)
                return 0;
            int count = 0;
            for (auto eit : list_edges()) {
                if (eit->second() == data)
                    ++count;
            }
            return count;
        }

        int degree_out(N data) {
            if (!dir)
                return 0;
            findNode(data, ni);
            return ni->degee();
        }
        
        int type_node(N data) {
            if (!dir) {
                switch (node_degree(data)) {
                case 0: return Aislado;
                case 1: return Hoja;
                default: return Normal;
                }
            }
            
            if (!findNode(data, ni))
                return 0;
            
            if (degree_in() != 0) {
                if (degree_out() == 0)
                    return Hundido;                    
            } else {
                if (degree_out() != 0)
                    return Fuente;
                else
                    return Aislado;
            } return Normal;            
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

        self* prim(N init = 0) {
            ASSERT(is_conexo(), "El grafo no es conexo");

            map<N, bool> reg;
            set<edge*, cmp> edges;
            
            ni = nodes.begin();

            if (init != 0)
                findNode(init, ni);

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
            ASSERT(is_conexo(), "El grafo no es conexo");

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
                findNode(init, ni);

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

        self* BFS(N init = 0) {
            map <N, bool> reg;
            queue<node *> priority;
            self *new_graph = new self;

            if (nodes.size() == 0)
                return new_graph;
            
            ni = nodes.begin();
            if (init != 0)
                findNode(init, ni);

            node *ptr, *temp;
            
            priority.push(*ni);
            
            reg[(*ni)->get_data()] = 1;

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
        
        void on_render(Interface &interface) {
            for (auto&& it : nodes)
                it->on_render(interface);
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