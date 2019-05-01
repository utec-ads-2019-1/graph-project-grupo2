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

	public:
		Edge(node *n1, node *n2, bool dir) : dir(dir)
		{
			nodes[0] = n1;
			nodes[1] = n2;
		}
};

#endif
