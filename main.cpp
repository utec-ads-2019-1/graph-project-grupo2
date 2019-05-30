#include <GL/glut.h>
#include <iostream>
#include "interface.h"
#include "graph.h"
#include "kuskal.h"
#include "prim.h"

using namespace std;

int main(int argc, char *argv[]) {
    graph grafo;
    graph *kruskal, *bfs, *dfs;
    Interface interface(10, 10, 1280, 720);

    grafo.push_node('A', 200, 200);
    grafo.push_node('B', 100, 100);
    grafo.push_node('C', 300, 300);
    grafo.push_node('D', 300, 300);
    grafo.push_node('E', 100, 100);
    grafo.push_node('F', 100, 100);
    grafo.push_node('G', 100, 100);
    grafo.push_node('H', 100, 100);
    grafo.push_node('I', 100, 100);

    grafo.push_edge('A', 'B', 1);
    grafo.push_edge('A', 'C', 2);
    grafo.push_edge('A', 'E', 3);
    grafo.push_edge('D', 'B', 4);
    grafo.push_edge('C', 'B', 5);
    grafo.push_edge('C', 'D', 6);
    grafo.push_edge('C', 'F', 8);
    grafo.push_edge('C', 'E', 9);
    grafo.push_edge('E', 'H', 8);
    grafo.push_edge('E', 'G', 8);
    grafo.push_edge('G', 'I', 3);
    grafo.push_edge('H', 'I', 8);

    grafo.print();
    
    //grafo.on_render(interface);
    
    //Kruskal k(grafo);
    //cout << "kruskal" << endl;
    //kruskal = grafo.kruskal();
    //kruskal->print();
    //k.print();
    
    cout << "BFS" << endl;
    bfs = grafo.BFS();
    bfs->print();

    cout << "DFS" << endl;
    dfs = grafo.DFS();
    grafo.isConexo();
    dfs->print();
    
    cout << "Prim" << endl;
    kruskal = grafo.prim();
    kruskal->print();

    //interface.init(argc, argv);
    //interface.display_func();

    

    //glutMainLoop ();
    //g++ graph.h node.h edge.h main.cpp -o main -lGL -lGLU -lglut


    return EXIT_SUCCESS;
}