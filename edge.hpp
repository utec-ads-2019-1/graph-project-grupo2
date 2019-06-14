#ifndef EDGE_H
#define EDGE_H

#include <SFML/Graphics/Vertex.hpp>

#include "node.hpp"

template <typename G>
class Edge {
    public:
        typedef typename G::E E;
        typedef typename G::node node;

        node* nodes[2];

	sf::Vertex line[2];

    private:
        E data;
        bool dir;

	public:
		Edge(node *n1, node *n2, E data, bool dir) : dir(dir), data(data)
		{
			nodes[0] = n1;
			nodes[1] = n2;

			line[0] = sf::Vertex(sf::Vector2f(n1->x + 20, n1->y + 20));
			line[1] = sf::Vertex(sf::Vector2f(n2->x + 20, n2->y + 20));
		}

		bool get_dir()
		{
			return (dir);
		}

		void draw(sf::RenderWindow &window)
		{
			window.draw(line, 2, sf::Lines);
		}
};

#endif
