//#include <GL/glut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    graph grafo;
    grafo.push_node('A');
    grafo.push_node('B');
    grafo.push_node('C');
    grafo.push_edge('A', 'B');
    grafo.push_edge('B', 'C');
    grafo.remove_edge('C', 'B');
    grafo.print();
    return EXIT_SUCCESS;
}