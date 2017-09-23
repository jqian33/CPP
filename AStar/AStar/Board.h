//=================================
// include guard
#ifndef __BOARD_H_INCLUDED__
#define __BOARD_H_INCLUDED__
//=================================
#include <vector>
#include <iostream>
#include <queue>
#include <functional>
#include "Grid.h"
#include "Node.h"

class Board
{
	public:
		Board();
		Board(int length, int width);
		int GetLength() const;
		int GetWidth() const;
		void Draw(void) const;
		void MarkObstacle(int, int);
		void MarkOccupied(int, int);
		Grid* GetGrid(int x, int y);
        void TracePath(Node*);

	private:
		int width;
		int length;
		std::vector<std::vector<Grid> > board;
		
};
#endif // __BOARD_H_INCLUDED__ 
