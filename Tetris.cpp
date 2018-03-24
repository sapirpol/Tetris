#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>  
#include <stdio.h>  
#include <time.h>  

#include "Point.h"
#include "Shape.h"
#include "Tetris.h"
#include "Board.h"


using namespace std;
Shape* Tetris::newShape(Board* board,int& piecesCounter, int score) const
{
	Shape* shape = nullptr;
	Shape::eType shape_choice = Shape::eType(rand() % 4);
	shape = new Shape(7, 3, board, shape_choice);
	piecesCounter++;
	gotoxy(0, 0);
	cout << "How many pieces has been droppen: " << piecesCounter << endl;
	cout << "Score: " << score << endl;
	cout << "(1)Initalize game, (2)Pause/Continue game, (3)Speed shapes, (4)Slow shapes, (9)Exit" << endl;
	return shape;
}

void Tetris::run() const
{
	int currentSpeed = 500;
	Board* board = new Board();
	srand((unsigned int)time(NULL));
	int piecesCounter = 0, score = 0;
	Shape* shape = newShape(board,piecesCounter,score);
	while (true)
	{
		char keyPressed = 0;
		if (_kbhit()) // checks if there is anything in the buffer
		{
			keyPressed = _getch(); // take the head of the buffer
			switch (keyPressed)
			{
			case Point::eKEYS::RESTART:
				clrscr();
				delete shape;
				shape = newShape(board, piecesCounter = 0, score = 0);
				delete board;
				board = new Board();
				continue;
			case Point::eKEYS::PAUSE_CONTINUE:
				while (_getch() != Point::eKEYS::PAUSE_CONTINUE);
				continue;
			case Point::eKEYS::SPEED:
				if (currentSpeed > 100)
				{
					currentSpeed -= 100;
				}
				break;
			case Point::eKEYS::SLOW:
				currentSpeed += 100;
				break;
			case Point::eKEYS::EXIT:
				return;
			case Point::eKEYS::LEFT:
				if (shape->CheckIfNextToWall() != Shape::eWall::LEFT_WALL)
				{
					shape->move(Point::LEFT);
				}
				break;
			case Point::eKEYS::RIGHT:
				if (shape->CheckIfNextToWall() != Shape::eWall::RIGHT_WALL)
				{
					shape->move(Point::RIGHT);
				}
				break;
			case Point::eKEYS::FLIP:
				shape->Flip();
			}
		}

		bool shapeHasStopped;
		do
		{
			shape->move(Point::DOWN);
			shapeHasStopped = shape->updateBoardAndChecksArrival(keyPressed, score);
			if (keyPressed == Point::eKEYS::DOWN)
				score++;
		} while (keyPressed == Point::eKEYS::DOWN && !shapeHasStopped);

		if (shapeHasStopped)
		{

			delete shape;

			shape = newShape(board,piecesCounter,score);
			if (shape->hasDownNeighborsInBoard())
			{
				gotoxy(5,5);
				cout << "GAME OVER" << endl;
				_getch();
				break;
			}
		}		
		
		Sleep(currentSpeed);
	}

	delete shape;
	return;


}


