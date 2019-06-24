#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "graph.hpp"
//#include "aStar.hpp"

#define PI 3.14159265
#define TWOPI 2 * PI

#define NUM_NODES 9

int main(int argc, char **argv)
{
	/*
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Graph");
	sf::Font font;
	sf::Texture exitButtonTexture;
	sf::Sprite exitButton;
	if (!exitButtonTexture.loadFromFile("img/exit-button.png"))
	{
		std::cout << "ERROR loading exit button.\n";
	}

	exitButton.setTexture(exitButtonTexture);
	exitButton.setScale(0.3, 0.3);
	exitButton.setPosition(50, 600);

	float exitButtonWidth = exitButton.getLocalBounds().width;
	float exitButtonHeight = exitButton.getLocalBounds().height;
	
	if (!font.loadFromFile("Courier.ttf"))
	{
		std::cout << "ERROR loading courier ttf\n";
	}

	sf::Text text("Grafo", font);
	text.setPosition(10, 10);

	graph g;

	g.add_node('a', 400, 100);
	g.add_node('b', 600, 50);
	g.add_node('c', 700, 150);
	g.add_node('d', 800, 150);
	g.add_node('e', 600, 200);
	g.add_node('f', 400, 250);
	g.add_node('g', 750, 300);
	g.add_node('h', 450, 350);
	g.add_node('i', 650, 450);


	g.add_edge('a', 'b', 5, true);
	g.add_edge('a', 'e', 6, true);
	g.add_edge('a', 'f', 3, true);
	g.add_edge('b', 'c', 8, true);
	g.add_edge('b', 'd', 7, true);
	g.add_edge('e', 'c', 6, true);
	g.add_edge('c', 'd', 2, true);
	g.add_edge('f', 'e', 2, true);
	g.add_edge('f', 'h', 5, true);
	g.add_edge('h', 'e', 3, true);
	g.add_edge('h', 'g', 7, true);
	g.add_edge('h', 'i', 8, true);
	g.add_edge('e', 'i', 4, true);
	g.add_edge('i', 'g', 4, true);
	g.add_edge('c', 'g', 10, true);
	g.add_edge('d', 'g', 4, true);

	g.print_nodes();
	g.print_edges();

	//aStar path = aStar::get_path(g, 'a', 'g');

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition( window );
				sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
				if ( exitButton.getGlobalBounds().contains( mousePosF ) )
				{
					exitButton.setColor( sf::Color( 250, 20, 20 ) );
				}
				else
				{
					exitButton.setColor( sf::Color( 255, 255, 255 ) );
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition( window );
				sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
				if ( exitButton.getGlobalBounds().contains( mousePosF ) )
				{
					window.close();
				}
			}
		}
		
		window.clear();
		window.draw(exitButton);
		window.draw(text);	
		g.draw(window);

		window.display();
	}
	*/

	graph g;
	g.add_node('a', 100, 100);
	g.add_node('b', 400, 100);
	g.add_edge('a', 'b', 10, false);
	g.print_nodes();
	g.print_edges();
	return (0);
}
