#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
const int framerate = 10;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
direction dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	system("cls");
	for (int i = 0; i < width + 2; i++)
		cout << "#"; 
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";
			if (i == y && j == x) {
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print) {
					cout << " ";
				}
			}
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl << "Score: " << score << endl << "Framerate: " << framerate << endl;
}

void Input() {
	if (_kbhit()) {
		switch (tolower(_getch())) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}

	if (x > width || x < 0 || y > height || y < 0) {
		gameOver = true;
	}

	if (x == fruitX && y == fruitY) {
		score++;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) {
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	default:
		break;
	}
}

void End() {
	system("cls");
	cout << "You lost!" << endl << "Your score is " << score << endl;
}

int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		this_thread::sleep_for(std::chrono::milliseconds(framerate));
	}
	End();
	return 0;
}