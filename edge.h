#ifndef EDGE_H
#define EDGE_H

#include "node.hpp"

template <typename G>
class Edge {
    public:
        typedef typename G::E E;
        typedef typename G::node node;

        node* nodes[2];

    private:
        E data;
        bool dir;
<<<<<<< HEAD:edge.hpp

	public:
		Edge(node *n1, node *n2, bool dir) : dir(dir)
		{
			nodes[0] = n1;
			nodes[1] = n2;
		}
=======
    
    public:
        Edge(node* n1, node* n2, E weight, bool is_dir) {
            nodes[0] = n1;
            nodes[1] = n2;
            data = weight;
            dir = is_dir;
        }

        bool isDir() {
            return dir;
        }

        node* edgePair(node* ptr) {
            return ptr == nodes[0] ? nodes[1] : nodes[0];
        }

>>>>>>> 6a6284bee1ea6ec9cf1c179849bc9c47c83bca96:edge.h
};

#endif
