#ifndef NODE_H
#define NODE_H
#include <math.h>
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
    
    public:
        Node(N new_data) {
            data = new_data;
        }

        Node(N new_data, double mx, double my) {
            data = new_data;
            x = mx;
            y = my;
        }

        void addEdge(edge *new_edge) {
            EdgeIte it;

            if (!findEdge(new_edge, it))
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

        void on_render(Interface &interface) {
            interface.add_nodes(x, y);
        }
};

#endif