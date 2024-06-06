#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <thread>
#include <chrono>
#include <math.h>

using namespace std;

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

class snakeBody
{
public:

	int x = 1;
	int y = 1;

	snakeBody(int x, int y) : x(x), y(y) {}
};

DWORD dw;
COORD here;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
vector <snakeBody> snakebody;

int randxBig = 0, randyBig = 0;
int randx = 1, randy = 3;
int ordinate = 1, absciss = 1;
int shift = 1, amount = 0;
int field_last[20][40];
int field[20][40] =
{
	{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
};

int input()
{
	this_thread::sleep_for(chrono::microseconds(98000 + (shift / 2) * 2000));
	if (_kbhit())
	{
		int input[2];

		input[0] = _getch();

		if (input[0] == 224)
		{
			input[1] = _getch();
			return input[1];
		}
		else return input[0];
	}
	return 0;
}

void output()
{
	for (int y = 0; y < sizeof(field) / sizeof(field[0]); y++)
	{
		for (int x = 0; x < sizeof(field[0]) / sizeof(int); x++)
		{
			for (int n = 0; n < snakebody.size(); n++)
			{
				field[snakebody[n].x][snakebody[n].y] = 3;
			}

			if (field[y][x] != field_last[y][x])
			{
				LPCWSTR out = L"#";

				switch (field[y][x])
				{
				case 4: out = L"#"; break;
				case 1: out = L" "; break;
				case 2: out = L"Ø"; break;
				case 3: out = L"█"; break;
				case 5:	out = L"@"; break;
				}

				here.Y = y;
				here.X = x;

				WriteConsoleOutputCharacter(hStdOut, out, 1, here, &dw);
			}
		}
	}
	memcpy(field_last, field, sizeof field);

}

void apple()
{

	if (ordinate == randx && absciss == randy)
	{
		while (true)
		{
			srand(time(0));
			randx = rand() % 18 + 1;
			randy = rand() % 38 + 1;
			if (field[randx][randy] != 3) break;
		}
		field[randx][randy] = 2;
		shift += 1 + (int)cbrt(shift) / 3;

	}

	if (shift % 5 == 0 && amount == 0)
	{
		while (true)
		{
			srand(time(0) + 1);
			randxBig = rand() % 18 + 1;
			randyBig = rand() % 38 + 1;
			if (field[randxBig][randyBig] != 3 && field[randxBig][randyBig] != 2) break;
		}
		field[randxBig][randyBig] = 5;
		amount++;
	}
	if (ordinate == randxBig && absciss == randyBig)
	{
		shift += 2 + (int)cbrt(shift) - 2;
		amount = 0;
	}

}

bool snake(int move)
{
	switch (move)
	{

	case 1: ordinate--;	break;
	case 2: absciss--;	break;
	case 3:	ordinate++;	break;
	case 4: absciss++;	break;

	}

	if (move != 0)
	{
		if (ordinate == 0) ordinate = 18;
		if (ordinate == 19) ordinate = 1;
		if (absciss == 0) absciss = 38;
		if (absciss == 39) absciss = 1;

		if (field[ordinate][absciss] == 3 && shift > 1)
		{
			//system("cls");
			SetConsoleTextAttribute(hStdOut, 12);
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nGAME OVER!!!!" << endl;
			cout << "RESULT: " << shift << endl;
			return false;
		}
	}

	snakebody.push_back(snakeBody(ordinate, absciss));
	if (snakebody.size() > shift)
	{
		field[snakebody[0].x][snakebody[0].y] = 1;
		snakebody.erase(snakebody.begin());
	}
	return true;
}

void process()
{
	snakebody.push_back(snakeBody(1, 1));
	bool gameStatus = true;
	int move = 4;
	field[1][3] = 2;


	while (gameStatus)
	{
		apple();
		output();
		int previous_move = move;
		int x = input();

		if (previous_move != 3 && (x == 119 || x == 230 || 296 == x + 224))
		{
			move = 1;
		}
		else if (previous_move != 4 && (x == 97 || x == 228 || 299 == x + 224))
		{
			move = 2;
		}
		else if (previous_move != 1 && (x == 115 || x == 63 || x == 235 || 304 == x + 224))
		{
			move = 3;
		}
		else if (previous_move != 2 && (x == 100 || x == 162 || 301 == x + 224))
		{
			move = 4;
		}

		gameStatus = snake(move);
	}
}

int main()
{
	ShowConsoleCursor(false);
	process();
}