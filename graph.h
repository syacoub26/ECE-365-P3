#ifndef _GRAPH_H
#define _GRAPH_H

#include <string>
#include <list>
#include <climits>

#include "hash.h"

class graph {

	class edge;

	class vertex{
	public:
		std::string id;
		std::list<edge> adj;
		std::list<std::string> path;
		int dv = INT_MAX;
		bool known = false;

		vertex(std::string &s) : id(s) {};
	};

	class edge{
	public:
		vertex *vdest;
		int cost;

		edge(vertex *v, int c) : vdest(v), cost(c) {};
	};

	std::list<vertex> data;
	hashTable mapping;

public:
	graph();
	void insert(const std::string &line);
	void dijkstra(const std::string &str);
	void write(std::string *out);
};

#endif
