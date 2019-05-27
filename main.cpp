#include <GL/glut.h>
#include <iostream>
#include "interface.h"
#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    graph grafo;
    graph *prim;
    Interface interface(10, 10, 1280, 720);

    grafo.push_node('A', 200, 200);
    grafo.push_node('B', 100, 100);
    grafo.push_node('C', 300, 300);
    grafo.push_node('D', 300, 300);
    grafo.push_edge('A', 'B', 2);
    grafo.push_edge('B', 'C', 5);
    grafo.remove_edge('C', 'B');
    grafo.push_edge('B', 'C', 1);
    grafo.push_edge('D', 'C', 3);
    grafo.push_edge('D', 'B', 10);
    grafo.print();
    
    grafo.on_render(interface);

    cout << "Prim" << endl;
    prim = grafo.kruskal();
    prim->print();
    
    //interface.init(argc, argv);
    //interface.display_func();

    

    //glutMainLoop ();
    //g++ graph.h node.h edge.h main.cpp -o main -lGL -lGLU -lglut


    return EXIT_SUCCESS;
}