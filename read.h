#ifndef READ_H
#define READ_H
#include <fstream>
#include <string>
#include "graph.h"

/**
 * Clase de ayuda para leer el grafo desde un archivo,
 * no es necesario que la utilicen, podrían implementar su lector
 * desde su grafo o algún otro lado
 **/
template <typename G>
class Read {
	typedef typename G::N N;
	typedef typename G::E E;
	private:
		ifstream inFile;

	public:
		Read(char* file) {
			inFile.open(file);
			inFile>> numLines;
        }
		
		graph& getGraph() {
			string line, value;
            graph ans;
		
			stringstream lineStream(line);

			while(getline(inFile, line)){
				if (line.size() > 1) break;
				ans.push_node(line);
			}

			while(getline(inFile, line)) {
			}

        }
};

#endif