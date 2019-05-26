#ifndef NODE_H
#define NODE_H
#include <iostream>
template <typename G>
class Node {
    public:
        typedef typename G::N N;
        typedef typename G::E E;
        typedef typename G::edge edge;
        typedef typename G::EdgeSeq EdgeSeq;
        typedef typename G::EdgeIte EdgeIte;

        EdgeSeq edges;

    private:
        N data;
        double x;
        double y;
<<<<<<< HEAD:node.hpp

	public:
		Node(N data) : data(data)
		{
			//
		}
		Node(N data, double x, double y) : data(data), x(x), y(y)
		{
			//
		}

		N get_data()
		{
			return (data);
		}
=======
    
    public:
        Node(N new_data) {
            data = new_data;
        }

        void addEdge(edge *new_edge) {
            edges.push_back(new_edge);
        }

        bool findEdge(edge *last_edge, EdgeIte &it) {
            it = find(edges.begin(), edges.end(), last_edge);
            return it != edges.end();
        }

        void removeEdge(edge *last_edge) {
            EdgeIte it;

            if (findEdge(last_edge, it))
                edges.erase(it);
        }

        N get_data() {
            return data;
        }

        ~Node() {
            for (auto&& it : edges) {
                it->edgePair(this)->removeEdge(it);
                delete it;
            }   edges.clear();
        }
>>>>>>> 6a6284bee1ea6ec9cf1c179849bc9c47c83bca96:node.h
};

#endif
