#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ExpressionManagerInterface.h"
#include "ExpressionManager.h"
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

	string inputString;
	ExpressionManager* manageThis = new ExpressionManager;
	for (inputString; inFile >> inputString;)
	{	
		if (inputString == "Expression:")
		{
			outFile << endl << "Expression: ";
			inFile.ignore();
			getline(inFile, inputString);
			delete manageThis;
			manageThis = new ExpressionManager(inputString);
			outFile << inputString << endl;
		}
		if (inputString == "Infix:")
		{
			outFile << "Infix: ";
			try { outFile << manageThis->infix() << endl; }
			catch (const char* errorText) { outFile << errorText << endl; }
		}
		if (inputString == "Postfix:")
		{
			outFile << "Postfix: " << manageThis->postfix() << endl;
		}
		if (inputString == "Value:")
		{
			outFile << "Value: " << manageThis->value() << endl;
		}
		if (inputString == "Prefix:")
		{
			outFile << "Prefix: " << endl;
		}
		
	}
	delete manageThis;
	return 0;
}