#include <conio.h>  
#include <iostream> 

#include "Board.h"
#include "Point.h"
#include "Gotoxy.h"
#include <windows.h>

using namespace std;

Board::Board()
{
	for (int i = 0; i < MAX_X + 1; i++)
	{
		for (int j = 0; j < MAX_Y + 1; j++)
		{
			matrix[i][j] = false;
		}
	}
	for (int i = MIN_Y; i < MAX_Y+1; i++) {
		gotoxy(MAX_X+1, i);
		cout << '|';
	}
	for (int i = MIN_X; i < MAX_X+2; i++) {
		gotoxy(i, MAX_Y+1);
		cout << '-';
	}
}

bool Board ::isRowFull(int row) const
{
	for (int i = MIN_X; i <= MAX_X; i++)
	{
		if (!(matrix[i][row]))
			return false;
	}
	return true;
}

void Board::bombRow(int row)
{
	for (int i = MIN_X; i <= MAX_X; i++)
	{
		for (int j = row - 1; j >= MIN_Y; j--)
		{
			matrix[i][j + 1] = matrix[i][j];
			gotoxy(i, j + 1);
			if (matrix[i][j + 1])
				cout << '*';
			else
				cout << ' ';
		}
	}
	for (int i = MIN_X; i <= MAX_X; i++)
	{
		matrix[i][MIN_Y] = false;
		gotoxy(i, MIN_Y);
		cout << ' ';

	}

}
bool Board::setPoint(int x, int y)
{
	matrix[x][y] = true;
	gotoxy(x, y);
	cout << '*';

	if (isRowFull(y))
	{
		bombRow(y);
		return true;
	}
	return false;
}

void Board::unSetPoint(int x, int y)
{
	matrix[x][y] = false;
	gotoxy(x, y);
    cout << ' ';
}

bool Board::getPoint(int x, int y) const
{
	if (y > MAX_Y)
	{
		return true;
	}
	return matrix[x][y];
}
