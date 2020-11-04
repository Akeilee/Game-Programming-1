#include <iostream>
#include "Maze.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Block.cpp"
#include<list>


using namespace std;
int row;
int col;
int rowarr[] = { -1, 0, 0, 1 };
int colarr[] = { 0, -1, 1, 0 };
std::vector<std::vector<int>>* Epos = new vector<vector<int>>;
int lowest =INT_MAX;


bool Maze::isValid(vector<vector<char>>& maze, vector<vector<char>>& visited, int r, int c){
	if ((r >= 0) && (r < row) && (c >= 0) && (c < col) && maze[r][c]  && visited[r][c] != 'o' && visited[r][c] != 'X') {
		return true;
	}
	else
		return false;
	/*return (r >= 0) && (r < row) && (c >= 0) && (c < col)
		&& maze[row][col] && visited[row][col] != '0' ;*/
}

void Maze::algorithm(vector<vector<char>>& maze, int i, int j, int x, int y) {


	visited.resize(row, std::vector<char>(col, ' '));
	aaa.resize(row, std::vector<char>(col, ' '));
	aaa = mazeVect;
	int ax;
	int ay;

	for (int i = 0; i < mazeVect.size(); i++) {
		for (int j = 0; j < mazeVect[i].size(); j++) {
			if (mazeVect[i][j] == 'S') {
				visited[i][j] = ' ';
			}
			if (mazeVect[i][j] == 'E') {
				visited[i][j] = 'E';
			}
			if (mazeVect[i][j] == 'X') {
				visited[i][j] = 'X';
			}
		}

	}

	for (int i = 0; i < visited.size(); i++) {
		for (int j = 0; j < visited[i].size(); j++) {
			cout << visited[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << endl;


	list<Node>* l1 = new list<Node>;
	vector<Node>* l2 = new vector<Node>;


	

	visited[i][j] = 'o';
	l1->push_back({ i, j, 0 });

	int min_dist = INT_MAX;
	Node* node = new Node;
	Node* current = new Node;

	

	while (!l1->empty()) {

		*node = l1->front();
		l1->pop_front();
		
		int i = node->x;
		int j = node->y;
		int dist = node->distance;

		

		if (i == x && j == y) {
			ax = i;
			ay = j;
			min_dist = dist;
			break;
		}

		int v = 0;
		for (int k = 0; k < 4; ++k) {

			if (i == x && j == y) {
				break;
			}

			if (isValid(maze, visited, i + rowarr[k], j + colarr[k])) {
				visited[i + rowarr[k]][j + colarr[k]] = 'o';
				

				int a = node->x;
				int b = node->y;

				l1->push_back({ i + rowarr[k], j + colarr[k], dist + 1,a ,b, node, v++});
				l2->push_back(l1->back());
				
				
			/*	for (int i = 0; i < visited.size(); i++) {
					for (int j = 0; j < visited[i].size(); j++) {
						cout << visited[i][j] << ' ';
					}
					cout << '\n';

				}*/
				
			}
		}

		
	}
	

	if (min_dist != INT_MAX) {

	cout << "The shortest path from source to destination "
		"has length " << min_dist << endl;
	


	//while (l2->size()>1) {
	//	if (l2->back().v == 0) {
	//		int a = l2->back().x;
	//		int b = l2->back().y;
	//		cout << a;
	//		cout << b;
	//		aaa[a][b] = 'o';
	//		cout << endl;
	//		l2->pop_back();
	//	}
	//	else break;
	//}


	//while (l2->size() > 1) {
	//	if (l2->front().x == ax && l2->front().y == ay) {
	//		int a = l2->front().x;
	//		int b = l2->front().y;
	//		aaa[a][b] = 'o';
	//		l2->pop_front();
	//	}
	//	else if (l2->front().x != ax && l2->front().y != ay) {
	//		l2->push_front(l2->back());
	//		//l2->pop_back();
	//	}

	//	
	//}

	//aaa[l2->back().x][l2->back().y] = 'E'; //64
	


	list<Node>* aa = new list<Node>;
	//auto pred = [ax, ay](const Node& item) {
	//	if (item.x == ax && item.y == ay) {
	//		
	//		return item.x;
	//	}
	//	//return item.x == ax && item.y == ay;
	//};
	//std::find_if(l2->begin(), l2->end(), pred) != l2->end();

	for (int i = 0; i < min_dist; i++) {
		vector<Node>::iterator findxy = find_if(l2->begin(), l2->end(), [ax, ay, aa](Node& item) { if (item.x == ax && item.y == ay)
			aa->push_back(item);
		return item.x == ax && item.y == ay; });


		std::list<Node>::iterator it;
		for (it = aa->begin(); it != aa->end(); ++it) {
			aaa[it->prevx][it->prevy] = 'o';
			//aaa[it->x][it->y] = 'o';
			ax = it->prevx;
			ay = it->prevy;
		}
	}




	aaa[row / 2][col / 2] = 'S';

	if (min_dist <= lowest) {
		lowest = min_dist;
		overallshortest = aaa;
	}


	for (int i = 0; i < aaa.size(); i++) {
		for (int j = 0; j < aaa[i].size(); j++) {
			cout << aaa[i][j] << ' ';
		}
		cout << '\n';
	}

	}
	else cout << "fail";

	visited.clear();
}	




void Maze::printvisit() {
	for (int i = 0; i < mazeVect.size(); i++) {
		for (int j = 0; j < mazeVect[i].size(); j++) {
			cout << mazeVect[i][j] << ' ';
		}
		cout << '\n';
	}
}


Maze::Maze() {
}

Maze::~Maze() {
}

void Maze::createMaze(int& row, int& col, int& exits) {

	bool validMaze = false;
	bool validExits = false;
	int r2 = row;
	int c2 = col;
	int e2 = exits;

	while (!validMaze) {

		if ((row <= 101 && row >= 7) && (col <= 101 && col >= 7)) {
			mazeVect.resize(row, std::vector<char>(col, 'X'));
			int midRow = row / 2;
			int midCol = col / 2;

			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					mazeVect[0][j] = 'X';
					mazeVect[i][0] = 'X';
					mazeVect[row - 1][j] = 'X';
					mazeVect[i][col - 1] = 'X';
				}
			}

			recursion(midRow, midCol, row, col);



			while (!validExits) {
				int maxExits = (((row * 2) + (col * 2)) - 4) / 2;
				if (exits <= maxExits) {
					createExit(row, col, exits);
					validExits = true;
				}

				else {
					cout << "Too many exits, re-enter no. of exits:" << endl;
					cin >> e2;
					exits = e2;
				}
			}

			validMaze = true;
		}
		else {
			cout << "Maze too large/small, re-enter row size: ";
			cin >> r2;
			cout << "Re-enter column size: ";
			cin >> c2;
			row = r2;
			col = c2;

			validExits = false;
			cout << "Enter no. exits from 0 to " << (((row * 2) + (col * 2)) - 4) / 2 << ": ";
			cin >> e2;
			exits = e2;

		}

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
			mazeVect[rRand][2] = ' ';
			break;
		case 1:
			while (mazeVect[rRand][col - 1] == 'E') {
				rRand = rand() % (row - 2) + 1;
			}
			//if (rRand != col - 1) {
			mazeVect[rRand][col - 1] = 'E';
			mazeVect[rRand][col - 2] = ' ';
			mazeVect[rRand][col - 3] = ' ';
			//}
			break;
		case 2:
			while (mazeVect[0][cRand] == 'E') {
				cRand = rand() % (col - 2) + 1;
			}
			//if (cRand != 0) {
			mazeVect[0][cRand] = 'E';
			mazeVect[1][cRand] = ' ';
			mazeVect[2][cRand] = ' ';
			//}
			break;
		case 3:
			while (mazeVect[row - 1][cRand] == 'E') {
				cRand = rand() % (col - 2) + 1;
			}
			//if (cRand != row - 1) {
			mazeVect[row - 1][cRand] = 'E';
			mazeVect[row - 2][cRand] = ' ';
			mazeVect[row - 3][cRand] = ' ';
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
	if (r <=0 || r >= rSize-1) {
		return false;
	}
	else if (c <= 0 || c >= cSize-1) {
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


void Maze::ePos() {
	

	for (int i = 0; i < mazeVect.size(); i++) {
		Epos->push_back(std::vector<int>());
		for (int j = 0; j < mazeVect[i].size(); j++) {
			if (mazeVect[i][j] == 'E') {
				//tempi = i;
				//tempj = j;
				//cout << tempi << ',' <<tempj<< endl;
				//(*Epos)[i].push_back(j);

				numberList.push_back(i);
				numberList.push_back(j);
			}
			
		}
		
	}

}

void Maze::getEPos() {

	cout << "GETEPOS";
	cout << numberList.size()<<endl;
	while (!numberList.empty()) {
			tempi = numberList.front();
			numberList.pop_front();
			tempj = numberList.front();
			numberList.pop_front();
			break;
	}

}

bool Maze::solveMaze(int row, int col, int rSize, int cSize) {


	if (mazeVect[row][col] == 'E') {
			cout << "Solved" << endl;
			return true;
		}

		if (row >= 0 && col >= 0 && row <= rSize && col <= cSize && (mazeVect[row][col] == ' ' || mazeVect[row][col] == 'S')) {
			mazeVect[row][col] = 'o';

			if (solveMaze(row + 1, col, rSize, cSize)) {
				//if (mazeVect[row + 1][col] == 'E') {
				//	return true;
				//}
				//else
					mazeVect[row + 1][col] = 'o';
				return true;
			}
			if (solveMaze(row, col + 1, rSize, cSize)) {
				//if (mazeVect[row][col + 1] == 'E') {
				//	return true;
				//}
				//else
					mazeVect[row][col + 1] = 'o';
				return true;
			}

			if (solveMaze(row - 1, col, rSize, cSize)) {
				/*if (mazeVect[row - 1][col] == 'E') {
					return true;
				}
				else*/
					mazeVect[row - 1][col] = 'o';
				return true;
			}

			if (solveMaze(row, col - 1, rSize, cSize)) {
				/*if (mazeVect[row][col - 1] == 'E') {
					return true;
				}
				else*/
					mazeVect[row][col - 1] = 'o';
				return true;
			}
			
			mazeVect[row][col] = ' ';
			return false;

		}

		return false;
	
}

void Maze::printMaze() {
	cout << "normal print \n";
	for (int i = 0; i < mazeVect.size(); i++) {
		for (int j = 0; j < mazeVect[i].size(); j++) {
			cout << mazeVect[i][j] << ' ';
		}
		cout << '\n';
	}

}

void Maze::printshortest() {
	cout << "SHORTEST \n";
	cout << "Shortest Distance is: " << lowest << endl;
	for (int i = 0; i < overallshortest.size(); i++) {
		for (int j = 0; j < overallshortest[i].size(); j++) {
			cout << overallshortest[i][j] << ' ';
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


void Maze::copy1() {
	mazeSol = mazeVect;
}

void Maze::copyMaze() {

	cout << "copymaze\n";
	for (int i = 0; i < mazeSol.size(); i++) {
		for (int j = 0; j < mazeSol[i].size(); j++) {
			if (mazeSol[i][j] == ' ' && aaa[i][j] == 'o') {
				mazeSol[i][j] = 'o';
			}
			if (mazeSol[i][j] == 'o' && aaa[i][j] == ' ') {
				mazeSol[i][j] = 'o';
			}
			if (mazeSol[i][j] == 'E' && (aaa[i][j] == 'X' || aaa[i][j] == 'o')) {
			mazeSol[i][j]='E';
			}
			else
				mazeSol[i][j] = mazeSol[i][j];
		}
	}

	for (int i = 0; i < mazeSol.size(); i++) {
		for (int j = 0; j < mazeSol[i].size(); j++) {
			cout << mazeSol[i][j] << ' ';
		}
		cout << '\n';
	}

	aaa.clear();
}

void Maze::clearO() {
	for (int i = 0; i < mazeVect.size(); i++) {
		for (int j = 0; j < mazeVect[i].size(); j++) {

			if (mazeVect[i][j]== 'o'){
				mazeVect[i][j] = ' ';
			}
			if (mazeVect[0][j] == ' ' ) {
				mazeVect[0][j] = 'X';
			}
			if (mazeVect[i][0] == ' ') {
				mazeVect[i][0] = 'X';
			}
			if (mazeVect[mazeVect[i].size()-1][j] == ' ') {
				mazeVect[mazeVect[i].size()-1][j] = 'X';
			} 
			if (mazeVect[i][mazeVect[j].size()-1] == ' ') {
				mazeVect[i][mazeVect[j].size() - 1] = 'X';
			}

			mazeVect[mazeVect.size() / 2][mazeVect[i].size()/2] = 'S';
		}
	}
	cout << "\n\nclear0\n";
	printMaze();
}












int main() {

	Maze* testM = new Maze();

	


	char input;
	int exits=0;

	cout << " - n = Create new maze\n"
		<< " - s = Save maze to file\n"
		<< " - o = Open file\n"
		<< " - e or 0 = Exit program\n\n" << endl;;

	cin >> input;

	while (input != NULL) {
		switch (input) {
		case 'n':
			testM->clearMaze();
			cout << "Enter row size: ";
			cin >> row;
			cout << "Enter column size: ";
			cin >> col;
			cout << "Enter no. exits from 1 to " << (((row * 2) + (col * 2)) - 4) / 2 << ": ";
			cin >> exits;
			testM->createMaze(row, col, exits);
			testM->middle(row, col);
			testM->printMaze();





			cout << "\nEnter character for next operation: ";
			cin >> input;
			break;


		case 'b':

			testM->ePos();
			testM->copy1();

			for (int i = 0; i < exits; i++) {
				cout << "OPERATION" << i << endl;
				testM->getEPos();
				testM->algorithm(testM->getMaze(), row / 2, col / 2, testM->getTempi(), testM->getTempj());
				testM->copyMaze();
			}

			testM->printshortest();

			







			cout << "\nEnter character for next operation: ";
			cin >> input;
			//testM->printvisit();
			break;





		case 's':
			testM->writeFile();
			cout << "\nEnter character for next operation: ";
			cin >> input;
			break;
		case 'a':

				
			
			testM->copy1(); ///solmaze = maze

			for (int i = 0; i < exits; i++) {
				cout << row;
				testM->ePos(); //find first e pos
				testM->solveMaze(row / 2, col / 2, row, col);
				testM->printMaze();


				testM->copyMaze(); ///copy maze into solmaze
				testM->clearO(); ///clear o in original maze
			}
			

			cout << "\nEnter character for next operation: ";
			cin >> input;
			break;
		case 'o':
			testM->readFile();
			cout << "\nEnter character for next operation: ";
			cin >> input;
			break;
		case 'e':
			delete testM;
			testM = nullptr;
			return 0;
		case '0': //////////////////////////////////////////////////////////////////
			delete testM;
			testM = nullptr;
			return 0;
		default:
			cout << "Please try again: ";
			cin >> input;
			break;
		}

		
	}

	return 0;
}