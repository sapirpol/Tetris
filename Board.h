#ifndef _Board_H_
#define _Board_H_

#define MIN_X  0
#define MAX_X  15

#define MIN_Y  4
#define MAX_Y 14


using namespace std;


class Board
{
	
public:
	bool setPoint(int x,int y);
	void unSetPoint(int x, int y);
	bool getPoint(int x,int y) const;
	Board();
private:
	bool isRowFull(int row) const;
	void bombRow(int row);
	bool matrix[MAX_X+1][MAX_Y+1];
};

#endif