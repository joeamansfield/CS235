#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

#include <iostream>
#include <fstream>
#include "LinkedListInterface.h"
#include "LinkedList.h"

using namespace std;

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
	bool appendNow = false;
	LinkedList<string> smallList;
	for (currentString; inFile >> currentString;)
	{
		// After "Insert" is entered, continue inserting until another command is entered
		if (currentString == "Insert")
		{
			insertNow = true;
			appendNow = false;
			outFile << "Insert ";
		}
		// After "Append" is entered, continue appending until another command is entered
		else if (currentString == "Append")
		{
			insertNow = false;
			appendNow = true;
			outFile << "Append ";
		}
		else if (currentString == "Delete")
		{
			if (insertNow || appendNow) outFile << endl;
			insertNow = false;
			appendNow = false;
			if (!smallList.empty())
			{	
				smallList.pop_front();
				outFile << "Delete OK" << endl;
			}
			else { outFile << "Delete Empty!" << endl; }
		}
		else if (currentString == "First")
		{
			if (insertNow || appendNow) outFile << endl;
			insertNow = false;
			appendNow = false;
			outFile << "First ";
			if (smallList.empty()) { outFile << "Empty!" << endl; }
			else { outFile << smallList.front() << endl; }
		}
		else if (currentString == "Empty")
		{
			if (insertNow || appendNow) outFile << endl;
			insertNow = false;
			appendNow = false;
			outFile << "Empty ";
			if (smallList.empty()) outFile << "true" << endl;
			else outFile << "false" << endl;
		}
		else if (currentString == "Remove")
		{
			if (insertNow || appendNow) outFile << endl;
			insertNow = false;
			appendNow = false;
			string removeThis;
			inFile >> removeThis;
			smallList.remove(removeThis);
			outFile << "Remove " << removeThis << endl;
		}
		else if (currentString == "Clear")
		{
			if (insertNow || appendNow) outFile << endl;
			insertNow = false;
			appendNow = false;
			smallList.clear();
			outFile << "Clear OK" << endl;
		}
		else if (currentString == "Reverse")
		{
			if (insertNow || appendNow) outFile << endl;
			insertNow = false;
			appendNow = false;
			smallList.reverse();
			if (smallList.empty()) { outFile << "Reverse Empty!" << endl; }
			else { outFile << "Reverse OK" << endl; }
		}
		else if (currentString == "Size")
		{
			if (insertNow || appendNow) outFile << endl;
			insertNow = false;
			appendNow = false;
			outFile << "Size " << smallList.size() << endl;
		}
		else if (currentString == "PrintList")
		{
			if (insertNow || appendNow) outFile << endl;
			insertNow = false;
			appendNow = false;
			outFile << "PrintList " << smallList.toString() << endl;
		}
		else if (currentString == "PrintList")
		{
			if (insertNow || appendNow) outFile << endl;
			insertNow = false;
			appendNow = false;
			outFile << "PrintList " << smallList.toString() << endl;
		}
		else if (currentString == "Last")
		{
			if (insertNow || appendNow) outFile << endl;
			insertNow = false;
			appendNow = false;
			outFile << "Last ";
			if (smallList.empty()) { outFile << "Empty!" << endl; }
			else { outFile << smallList.back() << endl; }
		}
		else if (currentString == "Drop")
		{
			if (insertNow || appendNow) outFile << endl;
			insertNow = false;
			appendNow = false;
			if (!smallList.empty())
			{
				smallList.pop_back();
				outFile << "Drop OK" << endl;
			}
			else { outFile << "Drop Empty!" << endl; }
		}
		// Insert happens here
		if (insertNow && currentString != "Insert")
		{
			smallList.push_front(currentString);
			outFile << currentString << " ";
		}
		// Append Happens here
		if (appendNow && currentString != "Append")
		{
			smallList.push_back(currentString);
			outFile << currentString << " ";
		}
	}
	smallList.clear();
	return 0;
}