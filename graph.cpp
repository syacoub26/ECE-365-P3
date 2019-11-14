#include <iostream>
#include <sstream>

#include "heap.h"
#include "graph.h"

using namespace std;

graph::graph(): mapping() {}

void graph::insert(const string &line){
	string svtxs, dvtxs;
	int c;

	vertex *svtxp, *dvtxp;

	istringstream iss(line);
	iss >> svtxs >> dvtxs >> c;

	if(mapping.contains(svtxs)){
		svtxp = static_cast<vertex *> (mapping.getPointer(svtxs));
	}else{
		vertex v(svtxs);
		data.push_back(v);
		auto i = next(data.begin(), data.size()-1);
		svtxp = &(*i);
		mapping.insert(svtxs, svtxp);
	}

	if(mapping.contains(dvtxs)){
		dvtxp = static_cast<vertex *> (mapping.getPointer(dvtxs));
	}else{
		vertex v(dvtxs);
		data.push_back(v);
		auto i = next(data.begin(), data.size()-1);
		dvtxp = &(*i);
		mapping.insert(dvtxs, dvtxp);
	}

	edge e(dvtxp, c);
	svtxp->adj.push_back(e);
}

void graph::dijkstra(const string &str){
	vertex *s = static_cast<vertex *> (mapping.getPointer(str));
	s->dv = 0;
	s->path.push_back(s->id);

	heap dpq(data.size());
	for(auto i = data.begin(); i != data.end(); i++){
		dpq.insert(i->id, i->dv, &(*i));
	}

	vertex *v;
	int j = dpq.deleteMin(nullptr, nullptr, &v);
	while(!j){
		v->known = true;
		for(auto const& i : v->adj){
			if( !(i.vdest->known) && v->dv + i.cost < i.vdest->dv ){
				i.vdest->dv = v->dv + i.cost;
				dpq.setKey(i.vdest->id, i.vdest->dv);
				//update path
				i.vdest->path = v->path;
				i.vdest->path.push_back(i.vdest->id);
			}
		}
		j = dpq.deleteMin(nullptr, nullptr, &v);
	}
}

void graph::write(string *out){
	for(auto const& i: data){
		string str = i.id + ": ";
		if( i.dv == INT_MAX || i.dv < 0){
			str += "NO PATH\n";
		}else{
			str += to_string(i.dv) + " [";
			for(auto const& j: i.path){
				str += j + ", ";
			}
			str.pop_back();
			str.pop_back();
			str += "]\n";
		}
		if (i.id.length() > 0)
			*out += str;
	}
}
