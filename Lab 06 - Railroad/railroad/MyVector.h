#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <string>
#include "MyDeque.h"
using namespace std;

template <typename T>
class MyVector {
private:
	MyDeque<T> dataDeque;
public:
	MyVector() {

	}

	~MyVector() {}

	void push_back(const T& data) {
		dataDeque.push_back(data);
	}

	void pop_back() {
		dataDeque.pop_back();
	}

	T& back() {
		return dataDeque.back();
	}

	size_t size() {
		return dataDeque.size();
	}

	T& at(size_t index) {
		return dataDeque.at(index);
	}
	string toString() const {
		return dataDeque.toString();
	}
};

#endif // !MY_VECTOR_H

