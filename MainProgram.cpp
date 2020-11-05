//Author: Jane Lee
//Date: 11/2020
//8501 Programming CW1

#include <iostream>
#include <fstream>

#include "Maze.h"

using namespace std;

int main() {

	Maze* testM = new Maze();
	char input;
	int r = 0;
	int c = 0;
	int exits = 0;
	bool notDoneB = false;
	
	cout << " - MENU - \n"
		<< " - n = Create new maze\n"
		<< " - b = Find all routes\n"
		<< " - f = Shortest path out of all routes\n"
		<< " - s = Save CURRENT shown Maze to file\n"
		<< " - a = Save BLANK maze to file\n"
		<< " - o = Open file\n"
		<< " - e or 0 = Exit program\n\n"
		<< "Please enter a character:\n" << endl;;

	cin >> input;

	while (input != NULL) {

		switch (input) {

		case 'n':

			testM->clearAllMazes();
			cout << "Enter row size from 7 to 101: ";
			cin >> r;
			testM->setRow(r);
			cout << "Enter column size from 7 to 101: ";
			cin >> c;
			testM->setCol(c);
			cout << "Enter no. exits from 1 to " << (((testM->getRow() * 2) + (testM->getCol() * 2)) - 4) / 2 << ": ";
			cin >> exits;

			testM->createMaze(r, c, exits);
			testM->createMiddle(testM->getRow(), testM->getCol());
			cout << endl;
			testM->printMaze();

			cout << "\nEnter character for next operation: ";
			cin >> input;
			r = 0;
			c = 0;

			break;

		case 'b':

			if (testM->getMaze().size() <= 0) {
				cout << "No maze found, please create a maze\n\n";
				input = 'n';
			}
			else {
				testM->ePos();
				testM->copyOGMaze();

				for (int i = 0; i < exits; i++) {
					testM->getEPos();
					testM->findPath(testM->getMaze(), testM->getRow() / 2, testM->getCol() / 2, testM->getTempi(), testM->getTempj());
					testM->copyTempMaze();
				}

				if (notDoneB == false) {
					cout << endl;
					testM->printSolution();
					testM->setShouldPrint(true);
					cout << "\nEnter character for next operation: ";
					cin >> input;
				}
				if (notDoneB == true) {
					testM->setShouldPrint(false);
					input = 'f';
					notDoneB = false;
				}

			}
			break;

		case 'f':

			if (testM->getMaze().size() <= 0) {
				cout << "No maze found, please create a maze\n\n";
				input = 'n';
			}
			else if (testM->getSolMaze().size() <= 0 && testM->getMaze().size() > 0) {
				notDoneB = true;
				input = 'b';
				testM->setShouldPrint(false);
			}
			else {
				cout << endl;
				testM->printShortestRoute();
				testM->setShouldPrint(false);
				cout << "\nEnter character for next operation: ";
				cin >> input;
			}
			break;

		case 's':
			testM->setprintOriginal(false);
			testM->writeFile();
			cout << "\nEnter character for next operation: ";
			cin >> input;
			break;

		case 'a':
			testM->setprintOriginal(true);
			testM->writeFile();
			cout << "\nEnter character for next operation: ";
			cin >> input;
			break;

		case 'o':
			testM->readFile();
			cout << "\nEnter character for next operation: ";
			cin >> input;
			break;

		case 'e':
			cout << "Exiting...";
			delete testM;
			testM = nullptr;
			return 0;

		case '0': //////////////////////////////////////////////////////////////////
			cout << "Exiting...";
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