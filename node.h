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

    public:
        E num_dominated; // veces que es dominado
        E status; // 0 blanco , 1 azul, 2 rojo
        E num_choise ;


        Node(N new_data) {
            data = new_data;
            status = 0;

        }

        void addNum_choise(E num){
            num_choise = this->num_choise + num;
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

        E degree() {
            return edges.size();
        }

        ~Node() {
            for (auto&& it : edges) {
                it->edgePair(this)->removeEdge(it);
                delete it;
            }   edges.clear();
        }

};

#endif
