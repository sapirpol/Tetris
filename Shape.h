#ifndef _Shape_H_
#define _Shape_H_
#include <iostream>
#include "Point.h"
#include "Gotoxy.h"
#include "Board.h"

using namespace std;
class Shape
{
public:
	enum eType { Square = 0, Line = 1, Bomb = 3, Joker = 2};
	enum eWall { LEFT_WALL, RIGHT_WALL, UP_WALL, DOWN_WALL, NO_WALL };

	Shape(int head_x, int head_y, Board* board, eType type);
	~Shape();

	void move(Point::eKEYS newDirection);
	bool updateBoardAndChecksArrival(char keyPressed, int& score);
	void Flip();

	eWall CheckIfNextToWall() const;
	bool hasDownNeighborsInBoard();


private:	
	Point* body;
	int size;
	char symbol;
	//we put this atributte to all kind of shapes by pointer bc according to object oriented the shapes should update the board in a diffrent manner
	//that's why we impliment differently "updateBoard()" to each shape.
	Board* board;
	eType type;

	void draw() const;
	void deleteShape() const;
	eWall CheckIfInWall() const;


};

#endif