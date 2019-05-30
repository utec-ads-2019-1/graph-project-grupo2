#ifndef NODE_H
#define NODE_H
#include <math.h>
template <typename G>
class Node {
    public:
        typedef typename G::N N;
        typedef typename G::E E;
        typedef typename G::edge edge;
        typedef typename G::node node;
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

        Node(N new_data, double mx, double my) {
            data = new_data;
            x = mx;
            y = my;
        }

        Node(node *new_node) {
            data = new_node->get_data();
            x = new_node->get_pos_x();
            y = new_node->get_pos_y();
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

        E get_pos_x() {
            return x;
        }

        E get_pos_y() {
            return y;
        }

        E degree() {
            return edges.size();
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
>>>>>>> carlos:node.h
};

#endif
