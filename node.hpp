#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics/CircleShape.hpp>

template <typename G>
class Node
{
	public:
		typedef typename G::N N;
		typedef typename G::E E;
		typedef typename G::edge edge;
		typedef typename G::EdgeSeq EdgeSeq;

		EdgeSeq edges;

		sf::CircleShape c;
	
	private:
		N data;
		float x;
		float y;

	public:
		Node(N data) : data(data)
		{
			//
		}

		Node(N data, float x, float y) : data(data), x(x), y(y)
		{
			c.setRadius(20);
			c.setOutlineThickness(5);
			c.setOutlineColor(sf::Color(250, 150, 100));
			c.setPosition(x, y);
		}

		N get_data()
		{
			return (data);
		}

		void draw(sf::RenderWindow &window)
		{
			window.draw(c);
		}
};

#endif
