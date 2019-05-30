#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <map>
#include <set>
#include "graph.h"

class Kruskal : public graph {

public:
    Kruskal(graph base);
    ~Kruskal() = default;
};

Kruskal::Kruskal(graph base) {
    if (!base.isConexo())
        return;
    
    map<N, N> reg;
    set<edge*, cmp> edges;
    
    for(auto nit : base.list_nodes()) {
        reg[nit->get_data()] = 0;
        for (auto eit : nit->edges)
            edges.insert(eit);
    }
    
    for (auto it : edges) {
        if (disjoint_set(reg, it->first(), it->second()))
            this->push_edge(it);
    }
    reg.clear();
    edges.clear();
}

#endif