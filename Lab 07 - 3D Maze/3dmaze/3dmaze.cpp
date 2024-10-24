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
#include "Maze.h"
using namespace std;

int main(int argc, char** argv) {
	VS_MEM_CHECK;

	if (argc < 3) {
		cerr << "Enter arguments for input and output files";
		return 1;
	}
	cout << "Input file: " << argv[1] << endl;
	ifstream inFile;
	inFile.open(argv[1]);
	if (!inFile) {
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream outFile;
	outFile.open(argv[2]);
	if (!outFile) {
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}
	int inputValue = 0;
	int mazeHeight = 0;
	int mazeWidth = 0;
	int mazeLayer = 0;
	int currentHeight = 0;
	int currentWidth = 0;
	int currentLayer = 0;
	inFile >> mazeHeight >> mazeWidth >> mazeLayer;
	Maze subnautica(mazeHeight, mazeWidth, mazeLayer);
	for (inputValue; inFile >> inputValue;) {
		subnautica.setValue(currentHeight, currentWidth, currentLayer, inputValue);
		currentWidth += 1;
		if (currentWidth == mazeWidth) {
			currentWidth = 0;
			currentHeight += 1;
			if (currentHeight == mazeHeight) {
				currentHeight = 0;
				currentLayer += 1;
			}
		}
	}
	outFile << "Solve Maze: " << endl << subnautica.toString();
	subnautica.setValue(mazeHeight - 1, mazeWidth - 1, mazeLayer - 1, 3);
	if (subnautica.find_maze_path()) {
		outFile << endl << "Solution:" << endl << subnautica.toString();
	}
	else {
		outFile << "No Solution Exists!";
	}
	inFile.close();
	outFile.close();
	return 0;
}