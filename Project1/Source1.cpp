#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool EndGamedGame;
const int width = 20;
const int height = 20;
int x, y, FoodX, FoodY, score; //x,y represent the head of the snake
int tailX[100], tailY[100];   //100 is the max lenght the tail can reach
int lTail; // length of the tail
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;
void Setup()
{
	EndGamedGame = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	FoodX = rand() % width;
	FoodY = rand() % height;
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

	for (int i = 0; i < width + 2; i++)
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
			else if (i == FoodY && j == FoodX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < lTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
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

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
}
void Input()
{
	if (_kbhit()) // check if a keyboard key is pressed
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
		case 'x':
			EndGamedGame = true;
			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0]; // remembers the previous value/length/coordinates of the tail and the thail segments
	int prevY = tailY[0];
	int prev2X, prev2Y; 	// remembers the current value/length/coordinates of the tail and the thail segments
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < lTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X; // changes to the new values for the tail
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
	//if (x > width || x < 0 || y > height || y < 0) // when uncommented touching the walls causes the player to lose
	//  gameOver = true;
	// lose conditions
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < lTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			EndGamedGame = true;

	//adds score and segments to tail when eating food
	if (x == FoodX && y == FoodY)
	{
		score += 10;
		FoodX = rand() % width;
		FoodY = rand() % height;
		lTail++;
	}
}
int main()
{
	Setup();
	while (!EndGamedGame)
	{
		Draw();
		Input();
		Logic();
		Sleep(50); // - used to slow the game down a bit
	}
	return 0;
}