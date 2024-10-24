#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include <string>
#include "MazeInterface.h"
using namespace std;

class Maze : public MazeInterface {
private:
	int mazeHeight;
	int mazeWidth;
	int mazeLayers;
	int*** mazeBox;
	enum CellValue { OPEN, BLOCKED, PATH, EXIT, TEMPORARY, LEFT, RIGHT, UP, DOWN, OUT, IN };
public:
	Maze(int h, int w, int d) {
		mazeHeight = h;
		mazeWidth = w;
		mazeLayers = d;
		mazeBox = new int**[mazeHeight];
		for (int i = 0; i < mazeHeight; i++) {
			mazeBox[i] = new int*[mazeWidth];
			for (int j = 0; j < mazeWidth; j++) {
				mazeBox[i][j] = new int[mazeLayers];
				for (int k = 0; k < mazeLayers; k++) {
					mazeBox[i][j][k] = 1;
				}
			}
		}
	}

	~Maze() {
		for (int i = 0; i < mazeHeight; i++) {
			for (int j = 0; j < mazeWidth; j++) {
				delete[] mazeBox[i][j];
			}
			delete[] mazeBox[i];
		}
		delete[] mazeBox;
	}

	void setValue(int height, int width, int layer, int value) {
		mazeBox[height][width][layer] = value;
		return;
	}

	bool maze_path_finder(int height, int width, int layer);

	void add_directions(int height, int width, int layer);

	bool find_maze_path() {
		if (maze_path_finder(0, 0, 0)) {
			add_directions(0, 0, 0);
			return true;
		}
		else { return false; }
	}

	string toString() const;
};
#endif // MAZE_H