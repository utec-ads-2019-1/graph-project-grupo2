#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "graph.hpp"

#define PI 3.14159265
#define TWOPI 2 * PI

#define NUM_NODES 9

using namespace std;

int main(int argc, char **argv)
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Graph");
	
	graph g;

	float r = 300;
	float center_x = 500;
	float center_y = 350;

	char nodes[NUM_NODES] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};

	/*
	g.add_node('a', center_x + r, center_y);
	g.add_node('b', center_x + r * cos(TWOPI / 9), center_y - r * sin(2 * PI / 9));
	g.add_node('c', center_x + r * cos(2 * TWOPI / 9), center_y - r * sin(2 * TWOPI / 9));
	g.add_node('d', center_x + r * cos(3 * TWOPI / 9), center_y - r * sin(3 * TWOPI / 9));
	g.add_node('e', center_x + r * cos(4 * TWOPI / 9), center_y - r * sin(4 * TWOPI / 9));
	g.add_node('f', center_x + r * cos(5 * TWOPI / 9), center_y - r * sin(5 * TWOPI / 9));
	g.add_node('g', center_x + r * cos(6 * TWOPI / 9), center_y - r * sin(6 * TWOPI / 9));
	g.add_node('h', center_x + r * cos(7 * TWOPI / 9), center_y - r * sin(7 * TWOPI / 9));
	g.add_node('i', center_x + r * cos(8 * TWOPI / 9), center_y - r * sin(8 * TWOPI / 9));
	*/

	for (int i = 0; i < NUM_NODES; ++i)
	{
		g.add_node(nodes[i], center_x + r * cos(i * TWOPI / 9), center_y - r * sin(i * TWOPI / 9));
	}

	g.add_edge('a', 'b', 4, true);
	g.add_edge('a', 'h', 8, true);
	g.add_edge('b', 'h', 11, true);
	g.add_edge('h', 'i', 7, true);
	g.add_edge('h', 'g', 1, true);
	g.add_edge('b', 'c', 8, true);
	g.add_edge('i', 'c', 2, true);
	g.add_edge('i', 'g', 6, true);
	g.add_edge('g', 'f', 2, true);
	g.add_edge('c', 'd', 7, true);
	g.add_edge('c', 'f', 4, true);
	g.add_edge('d', 'f', 14, true);
	g.add_edge('d', 'e', 9, true);
	g.add_edge('f', 'e', 10, true);

	g.print_nodes();
	g.print_edges();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();
		// TODO Draw circles
		
		g.draw(window);

		window.display();
	}
	return (0);
}
