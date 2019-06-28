#ifndef GRAPH_DIJKSTRA_HPP
#define GRAPH_DIJKSTRA_HPP
#include <iostream>
#include <queue>
#include "graph.hpp"

using namespace std;

class dijkstra : public graph {
private:
    E **path;
    E num_nodes;
    map<E, N> reg_nodes;
    map<N, E> reg;

public:
    dijkstra(graph g, N init) {
        nodes = g.nodes;
        edges = g.edges;

        num_nodes = nodes.size();
        path = new E*[num_nodes];

        for (int i = 0; i < num_nodes; ++i) {
            path[i] = new E[3];
            fill_n(path[i], 3, __INT_MAX__);
        }

        queue<node*> qnode;

        NodeIte nit(node_exists(init));
        if (nit == nodes.end()) exit(1);

        qnode.push(*nit);
        reg[(*nit)->data] = 0;

        path[0][0] = init;
        path[0][1] = 0;
        path[0][2] = init;


        E temp_weight;
        N temp_data, ptr_data;
        node* ptr_node;

        while (qnode.size()) {
            temp_data = qnode.front()->data;
            temp_weight = path[reg[temp_data]][1];

            for (edge *e : qnode.front()->edges) {
                ptr_node = e->edgePair(qnode.front());
                ptr_data = ptr_node->data;

                if (ptr_data == init) continue;

                if (setPathValues(ptr_data, temp_data, temp_weight + e->data))
                    qnode.push(ptr_node);
            }
            qnode.pop();
        }   print_matrix();
    }

    bool setPathValues(N eval, N origin, E weight) {
        if (reg[eval] == 0) {
            E count = reg.size() - 1;
            path[count][0] = eval;
            path[count][1] = weight;
            path[count][2] = origin;
            reg[eval] = count;
            return 1;
        }

        if (path[reg[eval]][1] > weight) {
            path[reg[eval]][1] = weight;
            path[reg[eval]][2] = origin;
        }   return 0;
    }

    void print_matrix() {
        cout << "\tNodos\tPesos\tOrigen" << endl;
        for (int i = 0; i < num_nodes; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (j == 1) cout << "\t" << path[i][j];
                else
                    cout << "\t" << (char)path[i][j];
            } cout << endl;
        }
    }

};

#endif //GRAPH_DIJKSTRA_HPP
