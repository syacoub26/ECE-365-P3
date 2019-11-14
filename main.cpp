#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

#include "graph.h"

using namespace std;

int main(){

	//input file that describes a graph
	string line;
	cout << "Enter name of graph file: ";
	getline(cin, line);
	ifstream input(line);

	//graph g to store vertices and edges from input file
	graph g;
	
	//loading graph
	while(!input.eof()){
		getline(input, line);
		g.insert(line);
	}

	//Dijkstra's algorithm
	cout << "Enter a valid vertex id for the starting vertex: ";
	getline(cin, line);
	clock_t t1 = clock();
	g.dijkstra(line);
	clock_t t2 = clock();
	double diff = ((double)(t2-t1))/CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << diff << "\n";

	//output file to write the path lengths
	cout << "Enter name of output file: ";
	getline(cin, line);
	ofstream output(line);
	line = "";
	g.write(&line);
	output << line;

	return 0;
}
