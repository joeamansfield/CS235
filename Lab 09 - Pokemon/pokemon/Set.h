#ifndef SET_H
#define SET_H
#include "SetInterface.h"
#include <string>
#include <list>

using namespace std;

template <typename T>
class Set : public SetInterface<T> {
private:
	list<T> setList;
public:
	Set() {}
	~Set() {}

	friend ostream& operator<< (ostream& os, Set& descriptiveToast)
	{
		os << descriptiveToast.toString();
		return os;
	}

	/** Inserts item into the set, if the container doesn't
		already contain an element with an equivalent value.
		@return: pair.first = pointer to item
				 pair.second = true if successfully inserted, else false. */
				 //virtual Pair<T*, bool> insert(const T& item) = 0;
	bool insert(const T& item) {
		setList.push_back(item);
		setList.sort();
		setList.unique();
		return true;
	}

	/** Removes all items from the set. */
	void clear() {
		setList.clear();
	}

	/** @return: the number of elements contained by the Set. */
	size_t size() const {
		return setList.size();
	}

	/** @return: return 1 if contains element equivalent to item, else 0. */
	size_t count(const T& item) {
		for (auto it = setList.begin(); it != setList.end(); it++) {
			if (*it == item) return 1;
		}
		return 0;
	}

	/** @return: string representation of items in Set. */
	string toString() const {
		string outString = "";
		for (auto it = setList.begin(); it != setList.end(); it++) {
			outString = outString + *it + ",";
		}
		outString.pop_back();
		return outString;
	}
};

#endif //SET_H