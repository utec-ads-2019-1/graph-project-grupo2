#ifndef EDGE_H
#define EDGE_H

#include "node.h"
#include <iostream>

template <typename G>
class Edge {
    public:
        typedef typename G::E E;
        typedef typename G::N N;
        typedef typename G::node node;
        typedef typename G::edge edge;

        node* nodes[2];

    private:
        E data;
        bool dir;
    
    public:
        Edge(node* n1, node* n2, E weight, bool is_dir) {
            nodes[0] = n1;
            nodes[1] = n2;
            data = weight;
            dir = is_dir;
        }

        E get_data() {
            return data;
        }

        bool isDir() {
            return dir;
        }

        N first() {
            return nodes[0]->get_data();
        }


        N second() {
            return nodes[1]->get_data();
        }

        node* first_node() {
            return nodes[0];
        }

        node* second_node() {
            return nodes[1];
        }

        void swap_nodes() {
            std::swap(nodes[0], nodes[1]);
        }
 
        node* edgePair(node* ptr) {
            return ptr == nodes[0] ? nodes[1] : nodes[0];
        }

};

#endif