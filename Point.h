#ifndef _Point__
#define _Point__
#include <iostream>
#include "Gotoxy.h"


using namespace std;

class Point
{
	int x;
	int y;
	int dir_x = 1;
	int dir_y = 0;
	char symbol;
public:
	enum eKEYS { LEFT = 'g', RIGHT = 'h', UP = 'y', DOWN = 'b', FLIP = 'a', ESC = 27, RESTART = '1',PAUSE_CONTINUE = '2',SPEED = '3',SLOW = '4',EXIT = '9'};
	Point(int x1 = 1, int y1 = 1);
	void draw(char c = '*') const;
	void move(eKEYS newDirection);
	void Point::setX(int x);
	void Point::setY(int y);
	 int Point::getX() const;
	 int Point::getY() const;
	 void Point::setSymbol(char symbol);
	 char Point::getSymbol() const;



	
};


#endif
