#include <GL/glut.h>
#include <iostream>
#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    graph grafo;

    grafo.push_node('A');
    grafo.push_node('B');
    grafo.push_node('C');
    grafo.push_node('D');
    grafo.push_node('E');
    grafo.push_node('F');

//    grafo.dir_graph();
    grafo.push_edge('B', 'A');
    grafo.push_edge('A', 'E');
    grafo.push_edge('E', 'B');
    grafo.push_edge('C', 'B');
    grafo.push_edge('D', 'C');
    grafo.push_edge('E', 'F');
    grafo.push_edge('C', 'F');

    int deg = grafo.node_degree('A');
    std::cout<< deg <<endl;
    std::cout << grafo.max_degree() <<endl;
//    grafo.push_node(1);
//    grafo.push_node(2);
//    grafo.push_node(3);
//    grafo.push_node(4);
//
//    grafo.dir_graph();
//    grafo.push_edge(2, 1);
//    grafo.push_edge(1, 4);
//    grafo.push_edge(4, 2);
//    grafo.push_edge(3, 2);
//    grafo.push_edge(4, 3);

//    grafo.push_node('A');
//    grafo.push_node('B');
//    grafo.push_node('C');
//    grafo.push_node('D');
//    grafo.push_node('E');
//    grafo.push_node('F');
//    grafo.push_node('G');
//    grafo.push_node('H');
//
//    grafo.push_edge('A', 'B');
//    grafo.push_edge('E', 'A');
//    grafo.push_edge('B', 'C');
//    grafo.push_edge('C', 'D');
//    grafo.push_edge('D', 'C');
//    grafo.push_edge('B', 'E');
//    grafo.push_edge('B', 'F');
//    grafo.push_edge('F', 'G');
//    grafo.push_edge('G', 'F');
//    grafo.push_edge('G', 'H');
//    grafo.push_edge('D', 'H');
//    grafo.push_edge('C', 'G');
//    grafo.push_edge('E', 'F');

    grafo.print();





    return EXIT_SUCCESS;
}