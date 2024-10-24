#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

#include <iostream>
#include <string>
#include <fstream>
#include "Station.h"
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
	Station<string> grandCentral;
	string trainCar;
	for (inputString; inFile >> inputString;)
	{
		outFile << inputString << " ";
		if (inputString.substr(0,4) == "Add:") {
			if (inputString.substr(4, 5) == "stack") {
				outFile << grandCentral.addStack();
			}
			else if (inputString.substr(4, 5) == "queue") {
				outFile << grandCentral.addQueue();
			}
			else if (inputString.substr(4, 7) == "station") {
				inFile >> trainCar;
				outFile << trainCar << " " << grandCentral.addCar(trainCar);
			}
		}
		else if (inputString.substr(0,7) == "Remove:") {
			if (inputString.substr(7, 5) == "stack") {
				outFile << grandCentral.removeStack();
			}
			else if (inputString.substr(7, 5) == "queue") {
				outFile << grandCentral.removeQueue();
			}
			else if (inputString.substr(7, 7) == "station") {
				outFile << grandCentral.removeCar();
			}
		}
		else if (inputString.substr(0,4) == "Top:") {
			if (inputString.substr(4, 5) == "stack") {
				outFile << grandCentral.topStack();
			}
			else if (inputString.substr(4, 5) == "queue") {
				outFile << grandCentral.topQueue();
			}
			else if (inputString.substr(4, 7) == "station") {
				outFile << grandCentral.topCar();
			}
		}
		else if (inputString.substr(0,5) == "Size:") {
			if (inputString.substr(5, 5) == "stack") {
				outFile << grandCentral.sizeStack();
			}
			else if (inputString.substr(5, 5) == "queue") {
				outFile << grandCentral.sizeQueue();
			}
		}
		else if (inputString == "Train:") {
			outFile << " " << grandCentral.toString();
		}
		else if (inputString.substr(0,5) == "Find:") {
			inFile >> trainCar;
			outFile << trainCar << " " << grandCentral.find(trainCar);
		}
		outFile << endl;
	}
	inFile.close();
	outFile.close();
	return 0;
}