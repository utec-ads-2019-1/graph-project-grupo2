#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "graph.hpp"

#define PI 3.14159265
#define TWOPI 2 * PI

#define NUM_NODES 9

int main(int argc, char **argv)
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Graph");
	sf::Font font;
	if (!font.loadFromFile("Courier.ttf"))
	{
		std::cout << "ERROR\n";
	}

	sf::Text text("Grafo", font);
	text.setPosition(10, 10);

	graph g;

	float r = 300;
	float center_x = 500;
	float center_y = 350;

	char nodes[NUM_NODES] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};

	for (int i = 0; i < NUM_NODES; ++i)
		g.add_node(nodes[i], center_x + r * cos(i * TWOPI / 9), center_y - r * sin(i * TWOPI / 9));

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
		window.draw(text);	
		g.draw(window);

		window.display();
	}
	return (0);
}
