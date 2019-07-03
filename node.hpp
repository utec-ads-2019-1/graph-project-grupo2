#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>


template <typename G>
class Node
{
	public:
		typedef typename G::N N;
		typedef typename G::E E;
		typedef typename G::edge edge;
		typedef typename G::EdgeSeq EdgeSeq;

	protected:
		N data;
		friend class FloydWarshall;
		friend class BellmanFord;
		friend class Dijkstra;

	private:
		float x;
		float y;
		EdgeSeq edges;
		sf::CircleShape c;
		sf::Text name;
		sf::Font font;

		template <typename T> friend class Edge;
		template <typename T> friend class Graph;

	public:
		Node(N data) : data(data)
		{
			//
		}

		Node(N data, float x, float y) : data(data), x(x), y(y)
		{
			c.setRadius(20);
			c.setPosition(x, y);
			if (!font.loadFromFile("Courier.ttf"))
				std::cout << "error loading font.\n";
			name = sf::Text(data, font);
			name.setFillColor(sf::Color::Black);
			name.setPosition(x + 10, y);
		}

		~Node()
		{
			for (auto it = edges.begin(); it != edges.end(); ++it)
				delete *it;
			edges.clear();
		}

		void draw(sf::RenderWindow &window)
		{
			window.draw(c);
			window.draw(name);
		}
};

#endif
