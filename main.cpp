//#include <GL/glut.h>
#include <iostream>

#include "graph.hpp"

using namespace std;

<<<<<<< HEAD
int main(int argc, char **argv)
{
	graph g;
	g.add_node('A');
	g.add_node('B');
	g.add_node('C');
	g.add_node('D');
	g.add_edge('B', 'C', false);
	g.add_edge('B', 'A', false);
	g.add_edge('C', 'D', false);
	g.remove_node('B');
	g.print_nodes();
	g.print_edges();
	return (0);
}
=======
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
>>>>>>> 6a6284bee1ea6ec9cf1c179849bc9c47c83bca96
