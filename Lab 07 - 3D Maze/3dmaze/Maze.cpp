#include "Maze.h"

bool Maze::maze_path_finder(int height, int width, int layer) {
	// edge case
	if (height < 0 || height >= mazeHeight ||
		width < 0 || width >= mazeWidth ||
		layer < 0 || layer >= mazeLayers) {
		return false;
	}
	// positive case
	if (mazeBox[height][width][layer] == EXIT) { return true; }
	// negative case
	if (mazeBox[height][width][layer] != OPEN) { return false; }
	//checks next
	if (mazeBox[height][width][layer] == OPEN) {
		cout << height << width << layer << endl;
		mazeBox[height][width][layer] = PATH;
		if (maze_path_finder(height, width - 1, layer) ||
			maze_path_finder(height, width + 1, layer) ||
			maze_path_finder(height - 1, width, layer) ||
			maze_path_finder(height + 1, width, layer) ||
			maze_path_finder(height, width, layer - 1) ||
			maze_path_finder(height, width, layer + 1)) {
			return true;
		}
	}
	mazeBox[height][width][layer] = TEMPORARY;
	return false;
}

void Maze::add_directions(int height, int width, int layer) {
	mazeBox[mazeHeight - 1][mazeWidth - 1][mazeLayers - 1] = PATH;
	if (width > 0) {
		if (mazeBox[height][width - 1][layer] == PATH || mazeBox[height][width][layer] == EXIT) {
			mazeBox[height][width][layer] = LEFT;
			add_directions(height, width - 1, layer);
		}
	}
	if (width < mazeWidth - 1) {
		if (mazeBox[height][width + 1][layer] == PATH) {
			mazeBox[height][width][layer] = RIGHT;
			add_directions(height, width + 1, layer);
		}
	}
	if (height > 0) {
		if (mazeBox[height - 1][width][layer] == PATH) {
			mazeBox[height][width][layer] = UP;
			add_directions(height - 1, width, layer);
		}
	}
	if (height < mazeHeight - 1) {
		if (mazeBox[height + 1][width][layer] == PATH) {
			mazeBox[height][width][layer] = DOWN;
			add_directions(height + 1, width, layer);
		}
	}
	if (layer > 0) {
		if (mazeBox[height][width][layer - 1] == PATH) {
			mazeBox[height][width][layer] = OUT;
			add_directions(height, width, layer - 1);
		}
	}
	if (layer < mazeLayers - 1) {
		if (mazeBox[height][width][layer + 1] == PATH) {
			mazeBox[height][width][layer] = IN;
			add_directions(height, width, layer + 1);
		}
	}
	mazeBox[mazeHeight - 1][mazeWidth - 1][mazeLayers - 1] = EXIT;
}

string Maze::toString() const {
	string outString = "";
	for (int x = 0; x < mazeLayers; x++) {
		outString += "Layer ";
		outString += to_string(x + 1);
		outString += "\n";
		for (int y = 0; y < mazeHeight; y++) {
			// 0 = open, 1 = closed, 2 = end, 3 = path, 4 = checked
			for (int z = 0; z < mazeWidth; z++) {
				if (mazeBox[y][z][x] == OPEN) { outString += "_"; }
				else if (mazeBox[y][z][x] == BLOCKED) { outString += "X"; }
				else if (mazeBox[y][z][x] == PATH) { outString += "2"; }
				else if (mazeBox[y][z][x] == EXIT) { outString += "E"; }
				else if (mazeBox[y][z][x] == TEMPORARY) { outString += "_"; }
				else if (mazeBox[y][z][x] == LEFT) { outString += "L"; }
				else if (mazeBox[y][z][x] == RIGHT) { outString += "R"; }
				else if (mazeBox[y][z][x] == UP) { outString += "U"; }
				else if (mazeBox[y][z][x] == DOWN) { outString += "D"; }
				else if (mazeBox[y][z][x] == OUT) { outString += "O"; }
				else if (mazeBox[y][z][x] == IN) { outString += "I"; }
				outString += " ";
			}
			outString += "\n";
		}
	}
	return outString;
}