#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "heap.h"

heap::heap(int capacity): mapping(capacity) {
	data.resize(capacity+1);
	size = 0;
}

int heap::getPos(node *pn){
	return pn - &data[0];
}

void heap::perUp(int i){
	node tmp = data[i];

	while(i > 1 && tmp.key < data[i/2].key){
		data[i] = data[i/2];
		mapping.setPointer(data[i].id, &data[i]);
		i = i/2;
	}
	data[i] = tmp;
	mapping.setPointer(data[i].id, &data[i]);
}

void heap::perDown(int i){
	node tmp = data[i];

	while(2*i <= size){

		int next = 2*i;
		if(next != size && data[next+1].key < data[next].key){
			next++;
		}

		if(data[next].key < tmp.key){
			data[i] = data[next];
			mapping.setPointer(data[i].id, &data[i]);
		}else{
			break;
		}

		i = next;
	}

	data[i] = tmp;
	mapping.setPointer(data[i].id, &data[i]);
}

int heap::insert(const string &id, int key, void *pv){

	if(data.size() == size + 1){
		return 1;
	}else if(mapping.contains(id)){
		return 2;
	}

	size++;

	int i = size;

	data[i].id = id;
	data[i].key = key;
	data[i].pData = pv;
	mapping.insert(id, &data[i]);

	perUp(i);

	return 0;
}

int heap::setKey(const string &id, int key){
	
	if(!mapping.contains(id)){
		return 1;
	}

	node *pn = static_cast<node *> (mapping.getPointer(id));
	int i = getPos(pn);

	if(data[i].key < key){
		data[i].key = key;
		perDown(i);
	}else if(data[i].key > key){
		data[i].key = key;
		perUp(i);
	}

	return 0;
}

int heap::deleteMin(string *pId, int *pKey, void *ppData){
	if(size == 0){
		return 1;
	}

	if(pId != nullptr) {*pId = data[1].id;}
	if(pKey != nullptr) {*pKey = data[1].key;}
	if(ppData != nullptr) {
		*( static_cast<void **>(ppData)) = data[1].pData;
	}

	mapping.remove(data[1].id);
	data[1] = data[size];
	size--;

	perDown(1);

	return 0;
}

int heap::remove(const string &id, int *pKey, void *ppData){
	if(!mapping.contains(id)){
		return 1;
	}

	node *pn = static_cast<node *> (mapping.getPointer(id));
	int i = getPos(pn);
	
	if(pKey != nullptr) {*pKey = data[i].key;}
	if(ppData != nullptr) {
		*( static_cast<void **>(ppData)) = data[1].pData;
	}

	int k = data[i].key;
	mapping.remove(data[i].id);	
	data[i] = data[size];
	size--;

	if(k < data[i].key){
		perDown(i);
	}else if(k > data[i].key){
		perUp(i);
	}

	return 0;
}
