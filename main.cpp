#include <iostream>
#include <SFML/Graphics.hpp>

#include "graph.hpp"

using namespace std;

int main(int argc, char **argv)
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Graph");
	
	graph g;

	g.add_node('a', 100.0, 100.0);
	g.add_node('b', 200.0, 200.0);
	/*
	g.add_node('c');
	g.add_node('d');
	g.add_node('e');
	g.add_node('f');
	g.add_node('g');
	g.add_node('h');
	g.add_node('i');

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
	*/

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
