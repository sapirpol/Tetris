#ifndef _Tetris_H_
#define _Tetris_H_
#include <iostream>
#include <windows.h>
#include "Point.h"
#include <iostream>
#include "Gotoxy.h"
#include "Board.h"
#include "Shape.h"

using namespace std;




class Tetris
{
	Shape* Tetris::newShape(Board* board,int& piecesCounter, int score) const;
public:
	void Tetris::run() const;
	
};
#endif
