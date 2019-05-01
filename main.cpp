//#include <GL/glut.h>
#include <iostream>

#include "graph.hpp"

using namespace std;

int main(int argc, char **argv)
{
	graph g;
	g.add_node('A');
	g.add_node('A');
	g.add_node('A');
	g.add_edge('A', 'B', false);
	g.add_node('B');
	g.add_node('B');
	g.add_edge('A', 'B', false);
	g.add_edge('A', 'B', false);
	g.print_nodes();
	g.print_edges();
	return (0);
}
