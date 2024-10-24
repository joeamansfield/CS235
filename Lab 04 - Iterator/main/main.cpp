#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

#include <iostream>
#include <fstream>

using namespace std;

template<typename T>
class LinkedList
{
private:
	struct Node
	{
		T data;
		Node* next;
		Node(const T& d, Node* n) : data(d), next(n) { }
	};
	Node* head;

public:
	LinkedList() : head(NULL) { }
	~LinkedList() { }
	void push_front(const T& value) { head = new Node(value, head); }

	friend std::ostream& operator<< (std::ostream& os, LinkedList<T>& linkedList)
	{
		for (Iterator iter = linkedList.begin(); iter != linkedList.end(); ++iter)
		{
			os << *iter << " ";
		}
		return os;
	}

	class Iterator
	{
	private:
		Node* iNode;
	public:
		Iterator(Node* head) : iNode(head) { }
		~Iterator() {}

		Node* getNode() { return iNode; }

		friend std::ostream& operator<< (std::ostream& os, Iterator& iterBoi)
		{
			os << *iterBoi;
			return os;
		}

		bool operator!=(const Iterator& rhs) const
		{
			cout << " Iterator::operator!=() ";
			return iNode != rhs.iNode;
		}
		
		Iterator& operator++()
		{
			cout << " Iterator::operator++() ";
			if (iNode)
			{
				iNode = iNode->next;
			}
			else
			{
				iNode = NULL;
			}
			return *this;
		}

		T& operator*() const
		{
			cout << " Iterator::operator*() ";
			return iNode->data;
		}
	};

	/** Return iterator pointing to the first value in linked list */
	Iterator begin(void)
	{
		return LinkedList<T>::Iterator(head);
	}

	/** Return iterator pointing to something not in linked list */
	Iterator end(void)
	{
		return LinkedList<T>::Iterator(NULL);
	}

	/** Return iterator pointing found value in linked list */
	Iterator find(Iterator first, Iterator last, const T& value)
	{
		cout << endl << "find " << value;
		Iterator iter = first;
		while (iter != last)
		{
			if (*iter == value)
			{
				return iter;
			}
			++iter;
		}
		return end();
	}

	/** Return iterator pointing to inserted value in linked list */
	Iterator insert(Iterator position, const T& value)
	{
		cout << endl << "Insert " << value;
		if (position != begin())
		{
			Iterator iter1 = ++begin();
			Iterator iter2 = begin();
			while (iter1 != position)
			{
				++iter1;
				++iter2;
			}
			iter2.getNode()->next = new Node(value, iter1.getNode());
			++iter2;
			return iter2;
		}
		else
		{
			push_front(value);
		}
		return begin();
	}

	/** Return iterator pointing to inserted value in linked list */
	Iterator insert_after(Iterator position, const T& value)
	{
		cout << endl << "insert_after " << value << " after " << *position;
		Iterator iter = position;
		++iter;
		position.getNode()->next = new Node(value, iter.getNode());
		return ++position;
	}

	/** Return iterator pointing to next item after deleted node linked list */
	Iterator erase(Iterator position)
	{
		cout << endl << "erase ";
		if (position != end())
		{
			if (position != begin())
			{
				Iterator iter1 = begin();
				Iterator iter2 = begin();
				while (iter1 != position)
				{
					++iter1;
					if (iter1 != position)
					{
						++iter2;
					}
				}
				iter2.getNode()->next = position.getNode()->next;
				delete iter1.getNode();
				++iter2;
				return iter2;
			}
			else
			{
				head = position.getNode()->next;
				delete position.getNode();
				return begin();
			}
		}
		else
		{
			return end();
		}
	}

	/** Replace first found old_value(s) with new_value */
	void replace(Iterator first, Iterator last, const T& old_value, const T& new_value)
	{
		cout << endl << "replace " << old_value << " with " << new_value;
		Iterator iter = first;
		while (iter != last)
		{
			if (*iter == old_value)
			{
				iter.getNode()->data = new_value;
			}
			++iter;
		}
	}
};


int main(int argc, char** argv)
{
	VS_MEM_CHECK;

	if (argc < 3)
	{
		cerr << "Enter arguments for input and output files";
		return 1;
	}
	cout << "Input file: " << argv[1] << endl;
	ifstream inFile;
	inFile.open(argv[1]);
	if (!inFile)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream outFile;
	outFile.open(argv[2]);
	if (!outFile)
	{
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}


	string currentString;
	bool insertNow = false;
	LinkedList<string> smallList;
	for (currentString; inFile >> currentString;)
	{
		// Actual code that inserts is located at end of loop in order to trigger any changes in the bool before running
		// After "insertBefore" is entered, continue inserting until another command is entered
		if (currentString == "Insert")
		{
			if (insertNow) outFile << endl;
			insertNow = true;
			outFile << "Insert";
		}

		// After "insertAfter" is entered, continue inserting until another command is entered
		else if (currentString == "InsertAfter")
		{
			string searchString;
			inFile >> currentString >> searchString;
			insertNow = false;
			outFile << "InsertAfter ";
			outFile << currentString << " " << searchString;
			if (smallList.find(smallList.begin(), smallList.end(), searchString) != smallList.end())
			{
				smallList.insert_after(smallList.find(smallList.begin(), smallList.end(), searchString), currentString);
				outFile << " OK" << endl;
			}
			else
			{
				outFile << " Not Found" << endl;
			}
		}

		else if (currentString == "InsertBefore")
		{
			string searchString;
			inFile >> currentString >> searchString;
			insertNow = false;
			outFile << "InsertBefore ";
			outFile << currentString << " " << searchString;
			if (smallList.find(smallList.begin(), smallList.end(), searchString) != smallList.end())
			{
				smallList.insert(smallList.find(smallList.begin(), smallList.end(), searchString), currentString);
				outFile << " OK" << endl;
			}
			else
			{
				outFile << " Not Found" << endl;
			}
		}

		else if (currentString == "PrintList")
		{
			if (insertNow) outFile << endl;
			insertNow = false;
			outFile << "PrintList " << smallList << endl;
		}

		else if (currentString == "Iterate")
		{
			if (insertNow) outFile << endl;
			insertNow = false;
			outFile << "Iterate";
			LinkedList<string>::Iterator iter = smallList.begin();
			if (smallList.begin() != smallList.end())
			{
				while (iter != smallList.end())
				{
					outFile << endl << " [" << iter << "]";
					++iter;
				}
			}
			else
			{
				outFile << " Empty!";
			}
			outFile << endl;
		}

		else if (currentString == "Erase")
		{
			if (insertNow) outFile << endl;
			insertNow = false;
			string searchString;
			inFile >> searchString;
			insertNow = false;
			outFile << "Erase ";
			outFile << searchString;
			if (smallList.find(smallList.begin(), smallList.end(), searchString) != smallList.end())
			{
				smallList.erase(smallList.find(smallList.begin(), smallList.end(), searchString));
				outFile << " OK" << endl;
			}
			else
			{
				outFile << " Not Found" << endl;
			}
		}

		else if (currentString == "Find")
		{
			if (insertNow) outFile << endl;
			insertNow = false;
			if (insertNow) outFile << endl;
			insertNow = false;
			string searchString;
			inFile >> searchString;
			insertNow = false;
			outFile << "Find ";
			outFile << searchString;
			if (smallList.find(smallList.begin(), smallList.end(), searchString) != smallList.end())
			{
				outFile << " OK" << endl;
			}
			else
			{
				outFile << " Not Found" << endl;
			}
		}

		else if (currentString == "Clear")
		{
			if (insertNow) outFile << endl;
			insertNow = false;
			LinkedList<string>::Iterator iter = smallList.begin();
			outFile << "Clear OK" << endl;
			while (iter != smallList.end())
			{
				iter = smallList.erase(iter);
			}
		}

		else if (currentString == "Replace")
		{
			if (insertNow) outFile << endl;
			insertNow = false;
			string oldString = "";
			string newString = "";
			inFile >> oldString >> newString;
			outFile << "Replace ";
			outFile << oldString << " " << newString;
			if (smallList.find(smallList.begin(), smallList.end(), oldString) != smallList.end() && oldString != newString)
			{
				while (smallList.find(smallList.begin(), smallList.end(), oldString) != smallList.end())
				{
					smallList.replace(smallList.begin(), smallList.end(), oldString, newString);
					outFile << " OK" << endl;
				}
			}
			else if (oldString == newString)
			{
				outFile << " OK" << endl;
			}
			else
			{
				outFile << " Not Found" << endl;
			}
		}

		// insert happens here
		if (insertNow && currentString != "Insert")
		{
			outFile << " " << currentString;
			smallList.insert(smallList.begin(), currentString);
		}
	}
	LinkedList<string>::Iterator iter = smallList.begin();
	while (iter != smallList.end())
	{
		iter = smallList.erase(iter);
	}
	return 0;
}