#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>

#include "hash.h"

class heap {
	int size;

	class node{
	public:
		std::string id;
		int key;
		void *pData;

		node() = default;
	};

	std::vector<node> data;
	hashTable mapping;

	int getPos(node *pn);
	void perUp(int i);
	void perDown(int i);

public:
	heap(int capacity);
	int insert(const std::string &id, int key, void *pv = nullptr);
	int setKey(const std::string &id, int key);
	int deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);
	int remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr);
};

#endif
