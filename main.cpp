#include <GL/glut.h>
#include <iostream>
#include "interface.h"
#include "graph.h"

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

    grafo.push_edge('A', 'B');
    grafo.push_edge('A', 'C');
    grafo.push_edge('A', 'E');
    grafo.push_edge('D', 'B');
    grafo.push_edge('C', 'B');
    grafo.push_edge('C', 'D');
    grafo.push_edge('C', 'F');
    grafo.push_edge('C', 'E');
    grafo.push_edge('E', 'H');
    grafo.push_edge('E', 'G');
    grafo.push_edge('G', 'I');
    grafo.push_edge('H', 'I');

    grafo.print();
    
    //grafo.on_render(interface);

    cout << "kruskal" << endl;
    kruskal = grafo.kruskal();
    kruskal->print();

    cout << "BFS" << endl;
    bfs = grafo.BFS();
    bfs->print();

    cout << "DFS" << endl;
    dfs = grafo.DFS();
    dfs->print();

    //interface.init(argc, argv);
    //interface.display_func();

    

    //glutMainLoop ();
    //g++ graph.h node.h edge.h main.cpp -o main -lGL -lGLU -lglut


    return EXIT_SUCCESS;
}