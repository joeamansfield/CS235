#ifndef MY_DEQUE_H
#define MY_DEQUE_H

#include <string>
#include "DequeInterface.h"
using namespace std;

template <typename T>
class MyDeque : public DequeInterface<T> {
private:
	T* mainArray = new T[DEFAULT_CAPACITY];
	size_t arrayCapacity = DEFAULT_CAPACITY;
	size_t numItems = 0;
	size_t arrayFront = 0;
	size_t arrayBack = 0;
	void fixCapacity() {
		if (numItems == arrayCapacity) {
			T* tempArray = new T[arrayCapacity * 2];
			for (int i = 0; i < numItems; i++) {
				tempArray[i] = mainArray[(i + arrayFront) % arrayCapacity];
			}
			arrayFront = 0;
			arrayBack = numItems - 1;
			delete[] mainArray;
			mainArray = tempArray;
			arrayCapacity = arrayCapacity * 2;
		}
		return;
	}
public:
	MyDeque() {}
	~MyDeque(void) {
		delete[] mainArray;
	}
	/** Insert item at front of deque */
	virtual void push_front(const T& value) {
		if (numItems == 0) {
			arrayFront = 0;
			arrayBack = 0;
		}
		else {
			arrayFront = (arrayFront - 1) % arrayCapacity;
			if (arrayFront < 0) { arrayFront = arrayFront * -1; }
		}
		mainArray[arrayFront] = value;
		numItems++;
		fixCapacity();
	}

	/** Insert item at rear of deque */
	virtual void push_back(const T& value) {

		if (numItems == 0) {
			arrayFront = 0;
			arrayBack = 0;
		}
		else {
			arrayBack = (arrayBack + 1) % arrayCapacity;
		}
		mainArray[arrayBack] = value;
		numItems++;
		fixCapacity();
	}

	// Removes front item of deque
	virtual void pop_front(void) {
		arrayFront = (arrayFront + 1) % arrayCapacity;
		numItems--;
	}

	// Removes rear item of deque
	virtual void pop_back(void) {
		arrayBack = (arrayBack - 1) % arrayCapacity;
		if (arrayBack < 0) { arrayBack = arrayBack * -1; }
		numItems--;
	}

	// Returns front item of deque
	virtual T& front(void) {
		return mainArray[arrayFront];
	}

	// Returns rear item of deque
	virtual T& back(void) {
		return mainArray[arrayBack];
	}

	// Returns number of items
	virtual size_t size(void) const {
		return numItems;
	}

	// Returns true if deque is empty
	virtual bool empty(void) const {
		return (numItems == 0);
	}

	// Returns item in deque at index (0 based)
	virtual T& at(size_t index) {
		return mainArray[(index + arrayFront) % arrayCapacity];
	}

	// Returns string of items in deque
	virtual string toString(void) const {
		string outString = "";
		for (size_t i = 0; i < numItems; i++) {
			outString += mainArray[(arrayFront + i) % arrayCapacity];
			outString += " ";
		}
		return outString;
	}
};
#endif // !MY_DEQUE_H
