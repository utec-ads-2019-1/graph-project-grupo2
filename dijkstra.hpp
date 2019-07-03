#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "graph.hpp"
#include <map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>


using namespace std;

class Dijkstra : public graph {
private:
    E num_nodos;

    map<node*,int > d ;
    map<node*, node*> pred;
    map<node*, string> color ;


   map<node*, int> cola ;

public:
    Dijkstra(graph g, N s ) {

        nodes = g.nodes;

       for (auto nodo: g.nodes){
           d[nodo] = __INT_MAX__;
           color[nodo] = "W";

           cola[nodo] = d[nodo];
       }

       NodeIte nit(node_exists(s));

        d[*nit] = 0;
        pred[*nit] = NULL;


        cola[*nit] = d[*nit];

        //cola con vertices
        node* ptr_nodo; // u

        while (!cola.empty()){
            //extraigo min d[v]
            std::pair<node*, int> min = *min_element(cola.begin(), cola.end(), compare);

            cola.erase(min.first);
            ptr_nodo = min.first ;

            for (auto arista: ptr_nodo->edges ){ //arista u->v

                if (d[ptr_nodo]+  arista->data < d[arista->nodes[1]] ){
                    d[arista->nodes[1]] = d[ptr_nodo] + arista->data;
                   cola[arista->nodes[1]] = d[arista->nodes[1]];
                   pred[arista->nodes[1]] = ptr_nodo ;
                }
                color[ptr_nodo]  = "B";
            }

        }
        print_d(g);

    }

    static bool compare(std::pair<node* ,int> i, pair<node*, int> j) {
        return i.second < j.second;
    }

    void print_d(graph g){

        cout << "\tvertices\t nodos" << endl;
        cout << "v |";

        for (auto nodos: g.nodes ){
              cout << (*nodos).data<<" ";
        }
        cout << endl;


        cout << "d[v] |";
        for (auto nodos: g.nodes ){
            cout << d[nodos] <<" ";
        }
        cout << endl;

        cout << "pred[v] |";
        for (auto nodos: g.nodes ){
            cout << pred[nodos] << " ";
        }
        cout << endl;

        cout << "color[v] |";
        for (auto nodos: g.nodes ){
            cout << color[nodos] << " ";
        }
        cout << endl;

    }



    ~Dijkstra() = default;
};

#endif