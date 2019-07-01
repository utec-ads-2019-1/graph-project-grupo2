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

			std::vector<int> init{current, 0, res.heuristic(current, f), -1};
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
                    auto it = res.row_exists(number);
					if ( it != res.table.end())
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
				res.print_table();
			}
			res.print_table();
			return (res);
		}

		std::vector<int> get_current_v(int no)
		{
			for (auto row : table)
				if (row[0] == no)
					return (row);
		}
		
		void print_visited()
		{
			for (auto r : v)
				std::cout << r.first << ": " << (r.second ? "visitado" : "no visitado") << '\n';
		}

		std::vector<std::vector<int>>::iterator row_exists(int n)
		{
			for (auto it = table.begin(); it != table.end(); ++it)
				if ((*it)[0] == n)
					return (it);
			return (table.end());
		}

		int search_n(int dist)
		{
			for (auto row : table)
				if (row[2] == dist)
					return row[0];
		}

		int get_min()
		{
			int ans = get_first_not_visited();
			for (auto row : table)
				if (v[row[0]] == false && row[2] < ans)
					ans = row[2];
			ans = search_n(ans);
			return (ans);
		}
		
		int get_first_not_visited()
		{
			for (auto row : table)
				if (v[row[0]] == false)
					return (row[2]);
		}

		void print_table()
		{
			for (auto row : table)
			{
				for (auto col : row)
					std::cout << col << ' ';
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
