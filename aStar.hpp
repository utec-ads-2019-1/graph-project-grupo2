#ifndef ASTAR_HPP
#define ASTAR_HPP
#include <vector>
#include <map>
#include <cmath>

#include "graph.hpp"

class aStar : public graph
{
	private:
		std::map<int, node*>			n;
		std::map<node*, int>			m;
		std::map<N, int>				p;
		std::map<int, bool>				v;
		std::vector<std::vector<int>>	table;

	public:
		aStar()
		{
			//
		}
		aStar(graph g)
		{
			int i = 0;
			for (auto no : g.nodes)
			{
				n[i] = no;
				m[no] = i;
				v[i] = false;
				p[no->data] = i++;
			}
		}
		static aStar get_path(graph g, N start, N finish)
		{
			aStar res(g);

			int current = res.p[start];
			int f = res.p[finish];

			std::vector<int> init{current, 0, res.heuristic(current, f), current};
			auto new_node = new node(res.n[current]->data, res.n[current]->x, res.n[current]->y);
			res.nodes.push_back(new_node);
			res.table.push_back(init);
			while (current != f)
			{
				res.v[current] = true; 
				for (auto neighbour : res.n[current]->edges)
				{
					auto vec = res.get_current_v(current);
					int number = res.m[neighbour->nodes[1]];
					E weight = neighbour->data + vec[1];
					int dist = res.heuristic(number, f) + weight;
					std::vector<int> row{number, weight, dist, current};
					if (auto it = res.row_exists(number); it != res.table.end())
					{
						if (dist < (*it)[2])
						{
							res.table.erase(it);
							res.table.push_back(row);
						}
					}
					else
					{
						res.table.push_back(row);
					}
				}
				current = res.get_min();
				auto new_node = new node(res.n[current]->data, res.n[current]->x, res.n[current]->y);
				res.nodes.push_back(new_node);
			}
			for (auto it = res.nodes.begin(); it != res.nodes.end() - 1; ++it)
			{
				auto new_edge = new edge(*it, *(it + 1), 0, true);
				res.edges.push_back(new_edge);
			}
			res.print_nodes();
			res.print_edges();
			std::cout << '\n';
			return (res);
		}

		std::vector<int> get_current_v(int no)
		{
			for (auto row : table)
			{
				if (row[0] == no)
				{
					return (row);
				}
			}
			return std::vector<int>();
		}
		
		void print_visited()
		{
			for (auto r : v)
			{
				std::cout << r.first << ": " << (r.second ? "visitado" : "no visitado") << '\n';
			}
		}

		std::vector<std::vector<int>>::iterator row_exists(int n)
		{
			for (auto it = table.begin(); it != table.end(); ++it)
			{
				if ((*it)[0] == n)
					return (it);
			}
			return (table.end());
		}

		int search_n(int dist)
		{
			for (auto row : table)
			{
				if (row[2] == dist)
				{
					return row[0];
				}
			}
			return -1;
		}

		int get_min()
		{
			int ans = get_first_not_visited();
			for (auto row : table)
			{
				if (v[row[0]] == false && row[2] < ans)
				{
					ans = row[2];
				}
			}
			ans = search_n(ans);
			return (ans);
		}
		
		int get_first_not_visited()
		{
			for (auto row : table)
			{
				if (v[row[0]] == false)
				{
					return (row[2]);
				}
			}
			return -1;
		}

		void print_table()
		{
			unsigned int i;
			for (auto row : table)
			{
				i = 0;
				for (auto col : row)
				{
					std::cout << col << ' ';
					if (i == 0 || i == 3)
					{
						std::cout << n[col]->data << ' ';
					}
					else
					{
						std::cout << col << ' ';
					}
					++i;
				}
				std::cout << '\n';
			}
			std::cout << '\n';
		}

		int heuristic(int a, int b)
		{
			auto n1 = n[a];
			auto n2 = n[b];
			auto dx = std::abs(n1->x - n2->x);
			auto dy = std::abs(n1->y - n2->y);
			return (dx + dy);
		}
};

#endif
