#ifndef STATION_H
#define STATION_H

#include <string>
#include "MyQueue.h"
#include "MyStack.h"
#include "MyVector.h"
using namespace std;

template <typename T>
class Station {
private:
	MyVector<T> train;
	MyStack<T> stackHouse;
	MyQueue<T> queueHouse;
	T turnTable;
	bool isEmpty = true;
public:
	Station() {
		
	}

	~Station() {}

	string addCar(const T& trainCar) {
		if (!isEmpty) { return "Turntable occupied!"; }
		turnTable = trainCar;
		isEmpty = false;
		return "OK";
	}

	string removeCar() {
		if (isEmpty) { return "Turntable empty!"; }
		train.push_back(turnTable);
		isEmpty = true;
		return "OK";
	}

	string topCar() {
		if (isEmpty) { return "Turntable empty!"; }
		return turnTable;
	}

	string addStack() {
		if (isEmpty) { return "Turntable empty!"; }
		stackHouse.push(turnTable);
		isEmpty = true;
		return "OK";
	}

	string removeStack() {
		if (!isEmpty) { return "Turntable occupied!"; }
		if (stackHouse.size() == 0) { return "Stack empty!"; }
		turnTable = stackHouse.top();
		stackHouse.pop();
		isEmpty = false;
		return "OK";
	}

	string topStack() {
		if (stackHouse.size() == 0) { return "Stack empty!"; }
		return stackHouse.top();
	}

	string sizeStack() {
		return to_string(stackHouse.size());
	}

	string addQueue() {
		if (isEmpty) { return "Turntable empty!"; }
		queueHouse.push(turnTable);
		isEmpty = true;
		return "OK";
	}

	string removeQueue() {
		if (!isEmpty) { return "Turntable occupied!"; }
		if (queueHouse.size() == 0) { return "Queue empty!"; }
		turnTable = queueHouse.top();
		queueHouse.pop();
		isEmpty = false;
		return "OK";
	}

	string topQueue() {
		if (queueHouse.size() == 0) { return "Queue empty!"; }
		return queueHouse.top();
	}

	string sizeQueue() {
		return to_string(queueHouse.size());
	}

	string find(T searchValue) {
		bool foundValue = false;
		string returnString = "";
		if (searchValue == turnTable) {
			foundValue = true;
			returnString = "Turntable";
		}
		if (!foundValue) {
			for (int i = 0; i < queueHouse.size(); i++) {
				if (searchValue == queueHouse.at(i)) {
					returnString = "Queue[" + to_string(i) + "]";
					foundValue = true;
				}
			}
		}
		if (!foundValue) {
			for (int i = 0; i < stackHouse.size(); i++) {
				if (searchValue == stackHouse.at(i)) {
					returnString = "Stack[" + to_string(i) + "]";
					foundValue = true;
				}
			}
		}
		if (!foundValue) {
			for (int i = 0; i < train.size(); i++) {
				if (searchValue == train.at(i)) {
					returnString = "Train[" + to_string(i) + "]";
					foundValue = true;
				}
			}
		}
		if (!foundValue) { returnString = "Not Found!"; }
		return returnString;
	}

	string toString() const {
		return train.toString();
	}

};

#endif // !STATION_H

