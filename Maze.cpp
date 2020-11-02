#include <iostream>
#include "Maze.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;



Maze::Maze() {
}

void Maze::createMaze(int row, int col, int exits) {

	try {
		if (row > 101 || row < 7) {
			throw(row);
			//cout << "Maze too large, try again ";
		}
		else if (col > 101 || col < 7) {
			throw(col);
		}
		else {
			mazeVect.resize(row, std::vector<char>(col, 'X'));
			int midRow = row / 2;
			int midCol = col / 2;

			recursion(midRow, midCol, row, col);

			int maxExits = (((row * 2) + (col * 2)) - 4) / 2;

			try {
				if (exits > maxExits) {
					throw(exits);
				}
				else
					createExit(row, col, exits);
			}
			catch (...) {
				cout << "Too many exits";
				exit(0);
			}
			//if (exits >= ((row * 2) + (col * 2)) - 4) {
			//	cout << "Too many exits, re-enter no. of exits ";
			//	cin >> exits;
			//	createExit(row, col, exits);
			//}
			//else {
			//	createExit(row, col, exits);
			//}
		}
			

	}
	catch (...) {
		cout << "Maze too large/small";
		exit(0);
	}








}

void Maze::createExit(int row, int col, int exits) {

	for (int i = 1; i <= exits; i++) {
		int rRand = rand() % (row - 2) + 1;
		int cRand = rand() % (col - 2) + 1;

		int randGen = rand() % 4;
		switch (randGen) {
		case 0:
			while (mazeVect[rRand][0] == 'E') {
				rRand = rand() % (row - 2) + 1;
			}
			mazeVect[rRand][0] = 'E';
			mazeVect[rRand][1] = ' ';
			break;
		case 1:
			while (mazeVect[rRand][col - 1] == 'E') {
				rRand = rand() % (row - 2) + 1;
			}
			//if (rRand != col - 1) {
			mazeVect[rRand][col - 1] = 'E';
			mazeVect[rRand][col - 2] = ' ';
			//}
			break;
		case 2:
			while (mazeVect[0][cRand] == 'E') {
				cRand = rand() % (col - 2) + 1;
			}
			//if (cRand != 0) {
			mazeVect[0][cRand] = 'E';
			mazeVect[1][cRand] = ' ';
			//}
			break;
		case 3:
			while (mazeVect[row - 1][cRand] == 'E') {
				cRand = rand() % (col - 2) + 1;
			}
			//if (cRand != row - 1) {
			mazeVect[row - 1][cRand] = 'E';
			mazeVect[row - 2][cRand] = ' ';
			//}
			break;
		}
	}
}

std::vector<int> Maze::randGenerator() {

	vector<int>directions;
	for (int i = 0; i < 4; i++) {
		directions.push_back(i);
	}
	random_shuffle(directions.begin(), directions.end());

	return directions;
}

bool Maze::inBounds(int r, int c, int rSize, int cSize) {
	if (r < 0 || r >= rSize) {
		return false;
	}
	else if (c < 0 || c >= cSize) {
		return false;
	}
	else {
		return true;
	}
}

void Maze::recursion(int r, int c, int rSize, int cSize) {

	const int up = 0;
	const int right = 1;
	const int left = 2;
	const int down = 3;
	vector<int>directions = randGenerator();

	mazeVect[r][c] = ' ';

	for (int i = 0; i < 4; ++i) {
		int x = 0;
		int y = 0;
		switch (directions[i]) {
		case up:
			y = -1;
			break;
		case right:
			x = 1;
			break;
		case down:
			y = 1;
			break;
		case left:
			x = -1;
			break;
		}

		int x2 = r + (x + x);
		int y2 = c + (y + y);

		if (inBounds(x2, y2, rSize, cSize)) {
			if (mazeVect[x2][y2] == 'X') {
				mazeVect[x2 - x][y2 - y] = ' ';
				recursion(x2, y2, rSize, cSize);
			}
		}

	}

}



//void Maze::recursion(int r, int c, int width, int height) {
//
//	vector<int>test;
//	for (int i = 0; i < 4; i++) {
//		test.push_back(i);
//	}
//	random_shuffle(test.begin(), test.end());
//
//
//	for (int i = 0; i < 4; i++) {
//		switch (test[i]) {
//		case 0:
//			if (r - 2 > 0) {
//				if (mazeVect[r - 2][c] != 0) {
//					mazeVect[r - 2][c] = 0;
//					mazeVect[r - 1][c] = 0;
//					recursion(r - 2, c, width, height);
//				}
//			}
//			break;
//		case 1:
//			if (c + 2 < width - 1) {
//				if (mazeVect[r][c + 2] != 0) {
//					mazeVect[r][c + 2] = 0;
//					mazeVect[r][c + 1] = 0;
//					recursion(r, c + 2, width, height);
//				}
//			}
//			break;
//		case 2:
//			if (r + 2 < height - 1) {
//				if (mazeVect[r + 2][c] != 0) {
//					mazeVect[r + 2][c] = 0;
//					mazeVect[r + 1][c] = 0;
//					recursion(r + 2, c, width, height);
//				}
//			}
//			break;
//		case 3:
//			if (c - 2 > 0) {
//				if (mazeVect[r][c - 2] != 0) {
//					mazeVect[r][c - 2] = 0;
//					mazeVect[r][c - 1] = 0;
//					recursion(r, c - 2, width, height);
//				}
//			}
//			break;
//		}
//	}
//
//}




void Maze::middle(int row, int col) {

	int midRow = row / 2;
	int midCol = col / 2;

	mazeVect[midRow][midCol] = 'S';

	mazeVect[midRow - 1][midCol - 1] = ' ';
	mazeVect[midRow - 1][midCol] = ' ';
	mazeVect[midRow - 1][midCol + 1] = ' ';
	mazeVect[midRow][midCol - 1] = ' ';
	mazeVect[midRow][midCol + 1] = ' ';
	mazeVect[midRow + 1][midCol - 1] = ' ';
	mazeVect[midRow + 1][midCol] = ' ';
	mazeVect[midRow + 1][midCol + 1] = ' ';

}

void Maze::printMaze() {
	for (int i = 0; i < mazeVect.size(); i++) {
		for (int j = 0; j < mazeVect[i].size(); j++) {
			cout << mazeVect[i][j] << ' ';
		}
		cout << '\n';
	}

}

void Maze::clearMaze() {
	mazeVect.clear();
}

void Maze::readFile() {

	string input;
	string output;
	cout << "Enter file name to open: ";
	cin >> input;
	cout << '\n';
	ifstream readMaze(input + ".txt");

	if (readMaze.is_open()) {
		while (getline(readMaze, output)) {
			cout << output;
			cout << '\n';
		}
		readMaze.close();
	}
	else {
		cout << '"' << input << "\" file does not exist" << endl;
	}


}

void Maze::writeFile() {

	ofstream mazeTxt;
	string input;
	cout << "Enter file save name: ";
	cin >> input;
	mazeTxt.open(input + ".txt");

	for (const auto& x : mazeVect) {
		copy(x.begin(), x.end(), ostream_iterator<char>(mazeTxt, " "));
		mazeTxt << '\n';
	}

	mazeTxt.close();

	cout << "File saved as " << input << ".txt" << endl;
}



int main() {

	Maze* testM = new Maze();
	int row;
	int col;
	char input;
	int exits;

	cout << " - n = Create new maze\n"
		<< " - s = Save maze to file\n"
		<< " - o = Open file\n"
		<< " - e = Exit program\n\n" << endl;;

	cin >> input;

	while (input != NULL) {
		switch (input) {
		case 'n':
			testM->clearMaze();
			cout << "Enter row size: ";
			cin >> row;
			cout << "Enter column size: ";
			cin >> col;
			cout << "Enter no. exits from 0 to "<< (((row * 2) + (col * 2)) - 4)/2;
			cin >> exits;
			testM->createMaze(row, col, exits);


			testM->middle(row, col);
			testM->printMaze();
			cout << "\nEnter character for next operation ";
			cin >> input;
			break;
		case 's':
			testM->writeFile();
			cout << "\nEnter character for next operation ";
			cin >> input;
			break;
		case 'o':
			testM->readFile();
			cout << "\nEnter character for next operation ";
			cin >> input;
			break;
		case 'e':
			delete testM;
			testM = nullptr;
			return 0;
		case '0': //////////////////////////////////////////////////////////////////
			return 0;
		default:
			cout << "Please try again ";
			cin >> input;
			break;
		}


	}

	return 0;
}