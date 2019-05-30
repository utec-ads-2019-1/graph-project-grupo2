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

		friend class Kruskal;
		friend class Prim;

	public:
		Edge(node *n1, node *n2, E data, bool dir) : dir(dir), data(data)
		{
			nodes[0] = n1;
			nodes[1] = n2;
		}

		bool get_dir()
		{
			return (dir);
		}
};

#endif
