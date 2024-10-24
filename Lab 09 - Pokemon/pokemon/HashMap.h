#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <string>
#include <iostream>
#include <sstream>
#include "HashMapInterface.h"
#include <math.h>

#define DEFAULT_MAP_HASH_TABLE_SIZE	31
#define HASH_CONSTANT				3
#define LOAD_THRESHOLD				75

using namespace std;

template <typename K, typename V>
class HashMap : public HashMapInterface<K,V> {
private:
	struct Node {
		Node() { occupied = false; }
		bool occupied;
		K key;
		V value;
	};
	Node* hashTable = new Node[DEFAULT_MAP_HASH_TABLE_SIZE];
public:
	HashMap() {}
	~HashMap() {
		delete[] hashTable;
	}

	friend ostream& operator<< (ostream& os, HashMap& descriptiveToast)
	{
		os << descriptiveToast.toString();
		return os;
	}

	size_t calculateIndex(string key) {
		size_t index = 0;
		for (int i = 0; i < key.size(); i++) {
			index += key[i] * round(pow(3.0, key.size() - (1.0 + i)));
		}
		index = index % DEFAULT_MAP_HASH_TABLE_SIZE;
		size_t k = 1;
		size_t originalIndex = index;
		while (hashTable[index].occupied && hashTable[index].key != key) {
			index = (index + k) % DEFAULT_MAP_HASH_TABLE_SIZE;
			k += 2;  
			if (index == originalIndex) {
				cerr << "quadratic probe is looping\n";
			}
		}
		return index;
	}

	/** Read/write index access operator.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	V& operator[](const K& key) {
		size_t index = calculateIndex(key);
		if (!hashTable[index].occupied) {
			hashTable[index].key = key;
			hashTable[index].occupied = true;
		}
		return hashTable[index].value;
	}

	/** @return: the number of elements that match the key in the Map. */
	size_t count(const K& key) {
		size_t index = calculateIndex(key);
		if (hashTable[index].key == key) return 1;
		else return 0;
	}

	/** Removes all items from the Map. */
	void clear(void) {
		delete[] hashTable;
		hashTable = new Node[DEFAULT_MAP_HASH_TABLE_SIZE];
	}

	/** @return: number of Key-Value pairs stored in the Map. */
	size_t size(void) const {
		size_t count = 0;
		for (int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++) {
			if (hashTable[i].occupied) count += 1;
		}
		return count;
	}

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	size_t max_size(void) const {
		return DEFAULT_MAP_HASH_TABLE_SIZE;
	}

	/** @return: string representation of Key-Value pairs in Map. */
	string toString(void) const {
		string outString = "";
		for (int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++) {
			stringstream ss;
			if (hashTable[i].occupied) {
				string tempString;
				outString.append("  ");
				ss << "[" << i << ":" << hashTable[i].key << "->" << hashTable[i].value << "]";
				ss >> tempString;
				outString.append(tempString);
				outString.append("\n");
			}
		}
		return outString;
	}
};
#endif //HASH_MAP_H