#include "Grid.h"

Grid::Grid(int x, int y, bool isObstacle, bool occupied) : x(x), y(y), isObstacle(isObstacle), occupied(occupied) {

}

Grid::Grid()
{
	isObstacle = false;
	occupied = false;
}

int Grid::GetX() const
{
	return x;
}

int Grid::GetY() const
{
	return y;
}

bool Grid::IsObstacle() const
{
	return isObstacle;
}

bool Grid::Occupied() const
{
	return occupied;
}

void Grid::MarkObstacle()
{
	isObstacle = true;
}

void Grid::RemoveObstacle()
{
	isObstacle = false;
}

void Grid::MarkOccupied()
{
	occupied = true;
}

void Grid::RemoveOccupied()
{
	occupied = false;
}






