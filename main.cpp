//#include <GL/glut.h>
#include <iostream>

#include "graph.hpp"

using namespace std;

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
