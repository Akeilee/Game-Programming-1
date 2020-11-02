#pragma once
#include <iostream>
#include <vector>

class Maze
{
public:
	Maze();
	void createMaze(int r, int c, int exits);
	void recursion(int r, int c, int rSize, int cSize);
	std::vector<int> randGenerator();
	void middle(int row, int col);
	void printMaze();
	void clearMaze();
	void readFile();
	void writeFile();
	bool inBounds(int r, int c, int rSize, int cSize);
	void createExit(int row, int col, int exits);

private:
	std::vector<std::vector<char>> mazeVect;

};


////most recent
//void Maze::recursion(int r, int c, int height, int width) {
//
//	vector<int>directions = randGenerator();
//	const int up = 0;
//	const int right = 1;
//	const int left = 2;
//	const int down = 3;
//
//	if (mazeVect[r][c] == 'E') {
//		cout << "jere";
//	}
//	else {
//		for (int i = 0; i < 4; i++) {
//			switch (directions[i]) {
//
//			case up:
//				if (r - 1 <= 0) {
//					continue;
//				}
//				if (mazeVect[r - 2][c] != ' ' && mazeVect[r - 2][c] != 'E') {
//					mazeVect[r - 2][c] = ' ';
//					mazeVect[r - 1][c] = ' ';
//					recursion(r - 2, c, height, width);
//				}
//				break;
//			case right:
//				if (c + 1 >= width - 1) {
//					continue;
//				}
//				if (mazeVect[r][c + 2] != ' ' && mazeVect[r][c + 2] != 'E') {
//					mazeVect[r][c + 2] = ' ';
//					mazeVect[r][c + 1] = ' ';
//					recursion(r, c + 2, height, width);
//				}
//				break;
//			case down:
//				if (r + 1 >= height - 1) {
//					continue;
//				}
//				if (mazeVect[r + 2][c] != ' ' && mazeVect[r + 2][c] != 'E') {
//					mazeVect[r + 2][c] = ' ';
//					mazeVect[r + 1][c] = ' ';
//					recursion(r + 2, c, height, width);
//				}
//				break;
//			case left:
//				if (c - 1 <= 0) {
//					continue;
//				}
//				if (mazeVect[r][c - 2] != ' ' && mazeVect[r][c - 2] != 'E') {
//					mazeVect[r][c - 2] = ' ';
//					mazeVect[r][c - 1] = ' ';
//					recursion(r, c - 2, height, width);
//				}
//				break;
//			}
//		}
//	}
//
//
//}