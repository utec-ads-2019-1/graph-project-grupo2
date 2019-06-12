#include <GL/glut.h>
#include <iostream>
#include "interface.h"
#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    graph grafo;
    graph *kruskal, *prim, *bfs, *dfs;
/*
    grafo.dir_graph();
    grafo.push_node('A');
    grafo.push_node('B');
    grafo.push_node('C');
    grafo.push_node('D');
    grafo.push_node('E');
    grafo.push_node('F');
    grafo.push_node('G');
    grafo.push_node('H');
    
    grafo.push_edge('A', 'B');
    grafo.push_edge('B', 'E');
    grafo.push_edge('B', 'F');
    grafo.push_edge('B', 'C');
    grafo.push_edge('C', 'G');
    grafo.push_edge('C', 'D');
    grafo.push_edge('D', 'C');
    grafo.push_edge('D', 'H');
    grafo.push_edge('E', 'A');
    grafo.push_edge('E', 'F');
    grafo.push_edge('F', 'G');
    grafo.push_edge('G', 'F');
    grafo.push_edge('G', 'H');
  */  
    /*
    grafo.dir_graph();
    grafo.push_node('A');
    grafo.push_node('B');
    grafo.push_node('C');
    grafo.push_node('D');

    grafo.push_edge('A', 'D');
    grafo.push_edge('D', 'B');
    grafo.push_edge('D', 'C');
    grafo.push_edge('C', 'B');
    grafo.push_edge('B', 'A');
    */
/*    
    grafo.push_node('A');
    grafo.push_node('B');
    grafo.push_node('C');
    grafo.push_node('D');
    grafo.push_node('E');
    grafo.push_node('F');
    grafo.push_node('G');
    grafo.push_node('H');

    grafo.push_edge('A', 'B');
    grafo.push_edge('E', 'A');
    grafo.push_edge('D', 'B');
    grafo.push_edge('D', 'C');
    grafo.push_edge('C', 'A');
    grafo.push_edge('B', 'F');
    grafo.push_edge('D', 'H');
    grafo.push_edge('C', 'G');
    grafo.push_edge('E', 'F');
    grafo.push_edge('H', 'F');
    grafo.push_edge('G', 'H');
    grafo.push_edge('E', 'G');
  */  
    /*
    grafo.push_node('A');
    grafo.push_node('B');
    grafo.push_node('C');
    grafo.push_node('D');
    grafo.push_node('E');
    grafo.push_node('F');
    grafo.push_node('G');
    grafo.push_node('H');
    
    grafo.push_edge('A', 'B', 11);
    grafo.push_edge('A', 'F', 1);
    grafo.push_edge('A', 'C', 24);
    grafo.push_edge('B', 'F', 4);
    grafo.push_edge('B', 'D', 1);
    grafo.push_edge('B', 'H', 17);
    grafo.push_edge('B', 'E', 30);
    grafo.push_edge('C', 'F', 3);
    grafo.push_edge('C', 'D', 21);
    grafo.push_edge('C', 'G', 11);
    grafo.push_edge('D', 'G', 6);
    grafo.push_edge('D', 'F', 9);
    grafo.push_edge('H', 'E', 2);
    grafo.push_edge('E', 'D', 51);
    */
   
    grafo.dir_graph();
    grafo.push_node('A');
    grafo.push_node('B');
    grafo.push_node('C');
    grafo.push_node('D');
    grafo.push_node('E');
    grafo.push_node('F');
    grafo.push_node('G');
    grafo.push_node('H');
    grafo.push_node('I');
    grafo.push_node('J');
    
    grafo.push_edge('A', 'B', 7);
    grafo.push_edge('A', 'E', 1);
    grafo.push_edge('B', 'F', 24);
    grafo.push_edge('C', 'A', 5);


    grafo.push_edge('C', 'E', 16);
    grafo.push_edge('D', 'I', 8);
    grafo.push_edge('E', 'A', 2);
    grafo.push_edge('E', 'B', 10);
    grafo.push_edge('E', 'G', 11);
    grafo.push_edge('E', 'D', 21);
    grafo.push_edge('F', 'E', 3);
    grafo.push_edge('G', 'H', 9);
    grafo.push_edge('G', 'J', 2);
    grafo.push_edge('H', 'J', 41);
    grafo.push_edge('H', 'D', 17);
    grafo.push_edge('I', 'H', 33);
    grafo.push_edge('I', 'D', 24);
    grafo.print();

    cout << "kruskal" << endl;
    kruskal = grafo.kruskal();
    kruskal->print();
    
    cout << "prim" << endl;
    prim = grafo.kruskal();
    prim->print();

    cout << "BFS" << endl;
    bfs = grafo.BFS('C');
    bfs->print();
    
    cout << "DFS" << endl;
    dfs = grafo.DFS('C');
    dfs->print();
 


    //g++ graph.h node.h edge.h main.cpp -o main -lGL -lGLU -lglut

    return EXIT_SUCCESS;
}