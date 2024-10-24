#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include <string>
#include "MyDeque.h"
using namespace std;

template <typename T>
class MyQueue {
private:
	MyDeque<T> dataDeque;
public:
	MyQueue() {

	}

	~MyQueue() {}

	void push(const T& data) {
		dataDeque.push_back(data);
	}

	void pop() {
		dataDeque.pop_front();
	}

	T& top() {
		return dataDeque.front();
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

#endif // !MY_QUEUE_H

