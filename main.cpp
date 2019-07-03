#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>


#include "graph.hpp"
#include "bellmanf.hpp"
#include "dijkstra.hpp"

#define PI 3.14159265
#define TWOPI 2 * PI

#define NUM_NODES 9

int main(int argc, char **argv)
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Graph");
	sf::Font font;
	sf::Texture exitButtonTexture;
	sf::Sprite exitButton;
	if (!exitButtonTexture.loadFromFile("exit-button.png"))
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

	float r = 300;
	float center_x = 700;
	float center_y = 350;

	char nodes[NUM_NODES] = {'a', 'b', 'c', 'd', 'e', 'f', 'g','h', 'i'};

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

//	BellmanFord f(g, 'a');
    cout<<"error1"<<endl;
    Dijkstra f(g, 'a');

    cout<<"error2"<<endl;

	g.print_nodes();
	g.print_edges();

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
	return (0);
}
