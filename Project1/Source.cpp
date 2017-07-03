#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>


using namespace std;
bool EndGame;
const int width = 20;
const int height = 20;
int x, y, FoodX, FoodY, gameScore; //x,y represent the head of the snake
int tailX[100], tailY[100];   //100 is the max lenght the tail can reach
int lTail; // length of the tail
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;
void Setup()
{
	EndGame = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	FoodX = rand() % width;
	FoodY = rand() % height;
	gameScore = 0;
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
	cout << "Score:" << gameScore << endl;
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
		case 'q':
			EndGame = true;
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
			EndGame = true;

	//adds score and segments to tail when eating food
	if (x == FoodX && y == FoodY)
	{
		gameScore += 5;
		FoodX = rand() % width;
		FoodY = rand() % height;
		lTail++;
	}
	
}

void Leaderboard()
{
	ServiceAPI api = new ServiceAPI("b0f3a390ab9423bc7ffacafea3978faafe5bebc7fcd18645f9f6ae68e7a77ec3", "b6a0e6a49dcb58c145a53a68da163cff3143235b65ea713dbc667d32962a9fdc");

	//Build User Service  
	UserService userService = serviceAPI.BuildUserService();
	// Using userService reference, you should be able to call all its method like create user/update user/authenticate etc.  
	//Build Storage Service  
	StorageService storageService = serviceAPI.BuildStorageService();

	String userName = "Nick";
	String pwd = "********";
	String emailId = "nick@shephertz.com";
	User user = userService.CreateUser(userName, pwd, emailId);
	/* This will create user in App42 cloud and will return User object */
	Console.WriteLine("userName is " + user.GetUserName());
	Console.WriteLine("emailId is " + user.GetEmail());

	String gameName = "<Enter_your_game/level_name>";
	String userName = "Nick";
	double gameScore = 3500;
	Game game = scoreBoardService.SaveUserScore(gameName, userName, gameScore);
	Console.WriteLine("gameName is " + game.GetName());
	for (int i = 0; i<game.GetScoreList().Count; i++)
	{
		Console.WriteLine("userName is : " + game.GetScoreList()[i].GetUserName());
		Console.WriteLine("score is : " + game.GetScoreList()[i].GetValue());
		Console.WriteLine("scoreId is : " + game.GetScoreList()[i].GetScoreId());
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
		Leaderboard();
		Sleep(50); // - used to slow the game down a bit
	}
	return 0;
}
