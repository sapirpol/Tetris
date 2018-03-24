#include "Board.h"
#include "Shape.h"
#include <Windows.h>

Shape::Shape(int head_x, int head_y, Board* board, eType type)
{

	this->board = board;
	this->type = type;
	switch (type) {
	case Line:
		this->symbol = '*';
		this->size = 4;
		this->body = new Point[4];
		this->body[0].setX(head_x);
		this->body[0].setY(head_y);
		this->body[1].setX(head_x);
		this->body[1].setY(head_y + 1);
		this->body[2].setX(head_x);
		this->body[2].setY(head_y + 2);
		this->body[3].setX(head_x);
		this->body[3].setY(head_y + 3);
		break;
	case Square:
		this->symbol = '*';
		this->size = 4;
		this->body = new Point[4];
		this->body[0].setX(head_x);
		this->body[0].setY(head_y);
		this->body[1].setX(head_x + 1);
		this->body[1].setY(head_y);
		this->body[2].setX(head_x);
		this->body[2].setY(head_y + 1);
		this->body[3].setX(head_x + 1);
		this->body[3].setY(head_y + 1);
		break;
	case Bomb:
		this->symbol = '@';
		this->size = 1;
		this->body = new Point[1];
		this->body[0].setX(head_x);
		this->body[0].setY(head_y);
		break;
	case Joker:
		this->symbol = '*';
		this->size = 1;
		this->body = new Point[1];
		this->body[0].setX(head_x);
		this->body[0].setY(head_y);
		break;
	}

	draw();
}

Shape::~Shape()
{
	deleteShape();
	delete[]body;
}


void Shape::Flip()
{

	switch (type)
	{
	case Square:
		break;
	case Bomb:
		break;
	case Joker:
		break;
	case Line:
		deleteShape();
		int remember_x = body[1].getX(), remember_y = body[1].getY();
		for (int i = 0; i < size; i++)
		{
			body[i].setX(body[i].getX() - remember_x);
			body[i].setY(body[i].getY() - remember_y);
		}
		//rotating matrix like we have studied in lenear algebra2,it works for all kind of shapes and we'll use it again later on.
		for (int i = 0; i < size; i++)
		{
			int x = body[i].getX();
			body[i].setX(body[i].getY());
			body[i].setY(x *(-1));
		}
		for (int i = 0; i < size; i++)
		{
			body[i].setX(body[i].getX() + remember_x);
			body[i].setY(body[i].getY() + remember_y);
		}

		while (CheckIfInWall() == LEFT_WALL)
		{
			this->move(Point::RIGHT);
		}

		while (CheckIfInWall() == RIGHT_WALL)
		{
			this->move(Point::LEFT);
		}

		while (CheckIfInWall() == UP_WALL)
		{
			this->move(Point::DOWN);
		}

		while (CheckIfInWall() == DOWN_WALL)
		{
			this->move(Point::UP);
		}
		draw();
		break;
	}
}
void Shape::draw() const
{
	for (int i = 0; i < size; i++)
	{
		body[i].draw(symbol);
	}
}

void Shape::deleteShape() const
{
	for (int i = 0; i < size; i++)
	{
		//we wanna delete the previous shape before moving down,buttttttttttt if there was a point in it that is also in board 
		//we dont want to delete it from the screen that's why we check it.
		if (board->getPoint(body[i].getX(), body[i].getY()) == false)
		{
			body[i].draw(' ');
		}
	}
}

//handeling bombs,joker and polygons
bool Shape::updateBoardAndChecksArrival(char keyPressed,int& score)
{
	switch (type)
	{
	case Bomb:
		//if it's a bomb it does'nt update the matrix,'it's only returns true bc the bomb arrived and erase from the matrix it self and it's neighbors
		if (hasDownNeighborsInBoard())
		{
			int start_x = max(MIN_X, body[0].getX() - 1);
			int start_y = max(MIN_Y, body[0].getY() - 1);
			int end_x = min(MAX_X, body[0].getX() + 1);
			int end_y = min(MAX_Y, body[0].getY() + 1);
			for (int i = start_x; i <= end_x; i++)
			{
				for (int j = start_y; j <= end_y; j++)
				{
					//if theres a neightbor update score by minus 50 and unset it from board.
					if (board->getPoint(i, j))
					{
						score -= 50;
						board->unSetPoint(i, j);
					}
					
					
				}
			}
			return true;
		}
		break;
	case Joker:
		if (keyPressed == 's' || body[0].getY() == MAX_Y)
		{
			
			if (board->setPoint(body[0].getX(), body[0].getY()))
			{
				score += 50;
			}
			return true;
		}
		break;
	case Square:
	case Line:
		int countFullLines = 0;
		if (hasDownNeighborsInBoard())
		{
			for (int i = 0; i < size; i++)
			{
				if (board->setPoint(body[i].getX(), body[i].getY()))
					countFullLines++;
			}

			switch (countFullLines)
			{
			case(1):
				score += 100;
				break;
			case(2):
				score += 300;
				break;
			case(3):
				score += 500;
				break;
			}
			return true;
		}
		break;
		
	}// end of switch

	return false;
}

bool Shape::hasDownNeighborsInBoard()
{
	for (int i = 0; i < size; i++)
	{
		if (board->getPoint(body[i].getX(), body[i].getY() + 1))
			return true;
	}
	//returns false in no point in the shape is next to a point in the matrix.
	return false;
}

void Shape::move(Point::eKEYS newDirection)
{
	//delete only this shape
	deleteShape();
		for (int i = 0; i < size; i++)
		{
			body[i].move(newDirection);
		}

		draw();
	
}
Shape::eWall Shape::CheckIfNextToWall() const
{
	for (int i = 0; i < size; i++)
	{
		if (body[i].getX() == MIN_X || board->getPoint(body[i].getX() - 1, body[i].getY()))
			return LEFT_WALL;
		else if (body[i].getX() == MAX_X || board->getPoint(body[i].getX() + 1, body[i].getY()))
			return RIGHT_WALL;
	}
	return NO_WALL;
}


Shape::eWall Shape::CheckIfInWall() const
{
	for (int i = 0; i < size; i++)
	{
		if (body[i].getX() < MIN_X)
			return LEFT_WALL;
		else if (body[i].getX() > MAX_X)
			return RIGHT_WALL;
		else if (body[i].getY() < MIN_Y)
			return UP_WALL;
		else if (body[i].getY() > MAX_Y)
			return DOWN_WALL;
	}
	return NO_WALL;
}


