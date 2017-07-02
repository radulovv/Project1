#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;
bool EndGame;
const int width = 20;
const int height = 20;
int x, y, foodX, foodY, score; //x,y represent the head of the snake
int tailX[25], tailY[25]; //25 is the max lenght the tail can reach
int lTail; // length of the tail

enum eDirection {LEFT, RIGHT, UP, DOWN, STOP = 0};
eDirection dir;
 

void Setup()
{
	EndGame = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	foodX = rand() % width;
	foodY = rand() % height;
	score = 0; 

}

//######
//#    #
//#    #
//###### example map
 
void Draw()
{
	system("cls"); //calls a clear system console
	
	//Draws the "arena"
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)

		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == foodX && j == foodX)
				cout << "F";
			else 
			{
				bool print = false;
				for (int t = 0; t < lTail; t++)
				{
					if (tailX[t] == j && tailY[t] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
	 

}

void Input()
{
	if (_kbhit())// check if a keyboard key is pressed
	{
		switch (_getch())
		{
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
		case 'q':
			EndGame = true;
			break;

		}
	}
}

void Logic()
{
	int prevX = tailX[0];
						// remembers the previous value/length/coordinates of the tail and the thail segments
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < lTail; i++)
	{
		prev2X = tailX[i];
						// remembers the current value/length/coordinates of the tail and the thail segments
		prev2Y = tailY[i];

		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
					// changes to the new values for the tail
		prevY = prev2Y;

	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x < 0 || y > height || y < 0)
		EndGame = true; // lose conditions
	for (int i = 0; i < lTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			EndGame == true;
	
	if (x == foodX && y == foodY)
	{
		lTail++;
		score += 5;
		foodX = rand() % width;
		foodY = rand() % height;
	}
}


int main()
{
	Setup();
	while (!EndGame)
	{
		Draw();
		Input();
		Logic();
		Sleep(50);// - used to slow the game down a bit

	}

	return 0;
}
