#ifndef MY_STACK_H
#define MY_STACK_H

#include <string>
#include "MyDeque.h"
using namespace std;

template <typename T>
class MyStack {
private:
	MyDeque<T> dataDeque;
public:
	MyStack() {

	}

	~MyStack() {}

	void push(const T& data) {
		dataDeque.push_back(data);
	}

	void pop() {
		dataDeque.pop_back();
	}

	T& top() {
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

#endif // !MY_STACK_H

