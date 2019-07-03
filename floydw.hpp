#ifndef FLOYDW_HPP
#define FLOYDW_HPP

#include "graph.hpp"
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

class FloydWarshall : public graph {
private:
	E **path, **weight;
	E num_nodes;
	map<N, E> reg;
	map<E, N> reg_nodes;
	//clang++ -std=c++17 main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system

public:
	FloydWarshall(graph g) {
		nodes = g.nodes
		edges = g.edges;

		num_nodes = g.nodes.size();

		path = new E*[num_nodes];
		weight = new E*[num_nodes];

		for (int i = 0; i < num_nodes; ++i) {
			path[i] = new E[num_nodes];
			weight[i] = new E[num_nodes];
			
			fill_n(weight[i], num_nodes, __INT_MAX__);
			
			for (int j = 0; j < num_nodes; ++j) {
				path[i][j] = j + 1;
			}

			path[i][i] = weight[i][i] = 0;

			reg[g.nodes[i]->data] = i + 1;
			reg_nodes[i + 1] = g.nodes[i]->data;
		}

		E n1, n2, val_temp;

		for (edge *e : edges) {
			n1 = reg[e->nodes[0]->data] - 1; 
			n2 = reg[e->nodes[1]->data] - 1;
			
			weight[n1][n2] = e->data;

			if (!e->dir) weight[n2][n1] = e->data;
		}

		for (int i = 0; i < num_nodes; ++i) {
			for (int j = 0; j < num_nodes; ++j) {
				if (i == j) continue;
				for (int k = 0; k < num_nodes; ++k) {
					if (i == k) continue;
					if (j == k) continue;
					
					if (weight[j][i] == __INT_MAX__ || weight[i][k] == __INT_MAX__)
						continue;
					
					val_temp = weight[j][i] * weight[i][k];

					if (val_temp < weight[j][k]) {
					/* For show all changes
						cout << "Change [" << reg_nodes[j + 1] << "][" << reg_nodes[k + 1] << "] ";
						cout << weight[j][k] << " by " << val_temp;
						cout << " - Node: "<< reg_nodes[i + 1] << endl;
					*/
						weight[j][k] = val_temp;
						path[j][k] = i + 1;
					}
				}
			}
		}
		print_matrix();
	}

	void print_matrix() {
		cout << "Matrix de pesos" << endl;

		for (int i = -1; i < num_nodes; ++i) {
			if (i == -1) cout << "\t";
			else cout << "\t" << reg_nodes[i + 1];
			for (int j = 0; j < num_nodes; ++j) {
				if (i == -1) {
					cout << "\t"<< reg_nodes[j + 1] << " ";
					continue;
				}

				if (__INT_MAX__ == weight[i][j])
					cout << "\tINF ";
				else
					cout << "\t"<< weight[i][j] << " ";
			}
			cout << endl;
		}

		cout << endl << "Matrix de caminos" << endl;

		for (int i = -1; i < num_nodes; ++i) {
			if (i == -1) cout << "\t";
			else cout << "\t" << reg_nodes[i + 1];
			for (int j = 0; j < num_nodes; ++j) {
				if (i == -1) {
					cout << "\t"<< reg_nodes[j + 1] << " ";
					continue;
				}
				if (i == j)
					cout << "\t0";
				else
					cout << "\t"<< reg_nodes[path[i][j]] << " ";
			}
			cout << endl;
		}
	}

	~FloydWarshall() = default;
};

#endif