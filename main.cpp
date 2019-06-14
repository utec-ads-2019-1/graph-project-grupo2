#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "graph.hpp"

#define PI 3.14159265

using namespace std;

int main(int argc, char **argv)
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Graph");
	
	graph g;

	float r = 300;
	float center = 500;

	g.add_node('a', center + r, 350.0);
	g.add_node('b', center + r * cos(2 * PI / 9), 350.0 - r * sin(2 * PI / 9));
	g.add_node('c', center + r * cos(2 * 2 * PI / 9), 350.0 - r * sin(2 * 2 * PI / 9));
	g.add_node('d', center + r * cos(3 * 2 * PI / 9), 350.0 - r * sin(3 * 2 * PI / 9));
	g.add_node('e', center + r * cos(4 * 2 * PI / 9), 350.0 - r * sin(4 * 2 * PI / 9));
	g.add_node('f', center + r * cos(5 * 2 * PI / 9), 350.0 - r * sin(5 * 2 * PI / 9));
	g.add_node('g', center + r * cos(6 * 2 * PI / 9), 350.0 - r * sin(6 * 2 * PI / 9));
	g.add_node('h', center + r * cos(7 * 2 * PI / 9), 350.0 - r * sin(7 * 2 * PI / 9));
	g.add_node('i', center + r * cos(8 * 2 * PI / 9), 350.0 - r * sin(8 * 2 * PI / 9));

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
