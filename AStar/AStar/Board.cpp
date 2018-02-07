#include "Board.h"

using namespace std;

Board::Board(int width, int length) : width(width), length(length)
{
	std::vector<Grid> column(length);
	board = std::vector<std::vector<Grid>>(width, column);
	for (int i = 0; i < board.size(); i++)
	{
		int columnCount = static_cast<int>(board[i].size());
		for (int j = 0; j < columnCount; j++)
		{
			board[i][j] = Grid(j, i, false, false);
		}
	}
};

Board::Board()
{
	width = 0;
	length = 0;
}

int Board::GetLength() const {
	return length;
}

int Board::GetWidth() const {
	return width;
}

void Board::Draw() const {
	for (int i = 0; i < board.size(); i++)
	{
		int columnCount = static_cast<int>(board[i].size());
		for (int j = 0; j < columnCount; j++)
		{
			Grid grid = board[i][j];
			cout << "[";
			if (!grid.IsOccupied() && !grid.IsObstacle() && !grid.IsOnPath())
			{
				cout << " ";
			}
			else if (grid.IsOccupied())
			{
				cout << "*";
			}
			else if (grid.IsObstacle())
			{
				cout << "X";
			}
            else if (grid.IsOnPath())
            {
                cout << "-";
            }
			cout << "]";
			if (j == columnCount - 1)
			{
				cout << endl;
			}
			else
			{
				cout << " ";
			}
		}
	}
}

void Board::TracePath(Node* node) {
    cout << endl;
    while (node != NULL) {
        node->GetGrid()->MarkOnPath();
        node = node->GetParent();
    }
    Draw();
}

void Board::MarkObstacle(int x, int y) {
    board[y][x].MarkObstacle();
}

void Board::MarkOccupied(int x, int y) {
	board[y][x].MarkOccupied();
}

Grid* Board::GetGrid(int x, int y) {
	return &board[y][x];
}


