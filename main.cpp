#include <GL/glut.h>
#include <iostream>
#include "interface.h"
#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    graph grafo;
    graph *kruskal, *prim, *bfs, *dfs;

    grafo.push_node('A');
    grafo.push_node('B');
    grafo.push_node('C');
    grafo.push_node('D');
    grafo.push_node('E');
    grafo.push_node('F');
    grafo.push_node('G');
    grafo.push_node('H');
    grafo.push_node('I');
    
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

    //grafo.remove_node('E');

    grafo.print();

    cout << "kruskal" << endl;
    kruskal = grafo.kruskal();
    kruskal->print();
    
    cout << "BFS" << endl;
    bfs = grafo.BFS();
    bfs->print();

    cout << "DFS" << endl;
    dfs = grafo.DFS();
    dfs->print();
    
    cout << "Prim" << endl;
    prim = grafo.prim();
    prim->print();

    grafo.is_strongly_connected();

    //g++ graph.h node.h edge.h main.cpp -o main -lGL -lGLU -lglut

    return EXIT_SUCCESS;
}