#pragma once
#include <iostream>
#include <vector>
#include<list>

struct Node {
	int x;
	int y;
	int distance;

	int prevx;
	int prevy;

	struct Node* parent;
	int v;

};
class Maze
{
public:

	bool isValid(std::vector<std::vector<char>>& maze, std::vector<std::vector<char>>& visited, int r, int c);
	void algorithm(std::vector<std::vector<char>>& maze, int i, int j, int x, int y);
	void printvisit();
	Maze() ;
	~Maze() ;
	void createMaze(int& r, int& c, int& exits);
	void recursion(int r, int c, int rSize, int cSize);
	std::vector<int> randGenerator();
	void middle(int row, int col);
	void ePos();
	void getEPos();
	bool solveMaze(int row, int col, int rSize, int cSize);
	void printMaze();
	void printshortest();
	void clearMaze();
	void readFile();
	void writeFile();
	void copy1();
	void copyMaze();
	void clearO();
	bool inBounds(int r, int c, int rSize, int cSize);
	void createExit(int row, int col, int exits);

	int tempi;
	int tempj;
	int getTempi() { return tempi; }
	int getTempj() { return tempj; }
	std::vector<std::vector<char>>& getMaze() {return mazeVect;};


private:
	std::vector<std::vector<char>> mazeVect;
	std::vector<std::vector<char>> mazeSol;
	std::vector<std::vector<char>> aaa;
	std::vector<std::vector<char>> visited;
	std::vector<std::vector<char>> overallshortest;
	std::list<int>numberList;

};
