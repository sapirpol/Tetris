#include <iostream>
#include "Gotoxy.h"
#include "Point.h"

using namespace std;

Point :: Point(int x1, int y1)
{
	x = x1;
	y = y1;
};

void Point :: draw(char c) const
{
	gotoxy(x, y);
	cout << c << endl;
}

void Point::setX(int x)
{
	this->x = x;
}

void Point::setY(int y)
{
	this->y = y;
}

 int Point::getX() const
{
	return this->x;
}
int Point::getY() const
{
	return this->y;
}

void Point::setSymbol(char symbol)
{
	this->symbol = symbol;
}
char Point::getSymbol() const
{
	return this->symbol;
}

void Point :: move(eKEYS newDirection)
{
	switch (newDirection)
	{
	case eKEYS::LEFT:
		dir_x = -1;
		dir_y = 0;
		break;
	case eKEYS::RIGHT:
		dir_x = 1;
		dir_y = 0;
		break;
	case eKEYS::DOWN:
		dir_x = 0;
		dir_y = 1;
		break;
	}
	x = x + dir_x;
	y = y + dir_y;
}


