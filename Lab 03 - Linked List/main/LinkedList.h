#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <string>
#include "LinkedListInterface.h"
using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T>
{
private:
	struct Node
	{
		Node(T newItem)
		{
			data = newItem;
			next = NULL;
			prev = NULL;
		}
		T data;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
public:
	LinkedList()
	{
		head = NULL;
		tail = NULL;
	}
	~LinkedList(void) {}

	//Insert node at beginning of list
	void push_front(const T& value)
	{
		if (head == NULL)
		{
			head = new Node(value);
		}
		else if (tail == NULL)
		{
			tail = head;
			head = new Node(value);
			head->next = tail;
			tail->prev = head;
		}
		else
		{
			Node* temp = head;
			head = new Node(value);
			head->next = temp;
			head->next->prev = head;
		}
	}

	//True if list is empty
	bool empty() const
	{
		return head == NULL;
	}

	//Remove first node from list
	void pop_front()
	{
		Node* temp = head;
		head = head->next;
		head->prev = NULL;
		delete temp;
	}

	//Return reference to first value in list
	T& front()
	{
		return head->data;
	}

	//Remove all Nodes with value from list
	void remove(const T& value)
	{
		Node* currentNode = head;
		while (currentNode != NULL)
		{
			Node* tempNode = currentNode->next;
			if (currentNode->data == value)
			{
				if (currentNode->prev != NULL)
				{
					currentNode->prev->next = currentNode->next;
				}
				else
				{
					head = currentNode->next;
				}
				if (currentNode->next != NULL)
				{
					currentNode->next->prev = currentNode->prev;
				}
				else
				{
					tail = currentNode->prev;
				}
				delete currentNode;
			}
			currentNode = tempNode;
		}
	}

	//Remove all nodes from list
	void clear()
	{
		Node* currentNode = head;
		Node* nextNode = NULL;
		while (currentNode != NULL)
		{
			nextNode = currentNode->next;
			delete currentNode;
			currentNode = nextNode;
		}
		head = NULL;
		tail = NULL;
	}

	//Reverse order of nodes in list
	void reverse()
	{
		Node* currentNode = head;
		while (currentNode != NULL)
		{
			Node* nextNode = currentNode->next;
			currentNode->next = currentNode->prev;
			currentNode->prev = nextNode;
			currentNode = nextNode;
		}
		Node* tempNode = head;
		head = tail;
		tail = tempNode;
	}

	//Return number of nodes in list
	size_t size() const
	{
		Node* currentNode = head;
		int nodeCount = 0;
		while (currentNode != NULL)
		{
			currentNode = currentNode->next;
			nodeCount += 1;
		}
		return nodeCount;
	}

	//Return contents of list as string
	string toString() const
	{
		Node* currentNode = head;
		string listString = "";
		if (currentNode == NULL) listString = "Empty!";
		while (currentNode != NULL)
		{
			listString.append(currentNode->data);
			if (currentNode->next != NULL) listString.append(" ");
			currentNode = currentNode->next;
		}
		return listString;
	}

	T& back(void)
	{
		return tail->data;
	}

	void push_back(const T& value)
	{
		if (tail == NULL)
		{
			tail = new Node(value);
		}
		else if (head == NULL)
		{
			head = tail;
			tail = new Node(value);
			head->next = tail;
			tail->prev = head;
		}
		else
		{
			Node* temp = tail;
			tail = new Node(value);
			tail->prev = temp;
			tail->prev->next = tail;
		}
	}

	void pop_back(void)
	{
		Node* temp = tail;
		tail = tail->prev;
		if (tail != NULL) { tail->next = NULL; }
		else
		{
			head = NULL;
			tail = NULL;
		}
		delete temp;
	}
};
#endif