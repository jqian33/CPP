#include "Grid.h"

Grid::Grid(int x, int y, bool isObstacle, bool isOccupied) : x(x), y(y), isObstacle(isObstacle), isOccupied(isOccupied)
{
}

Grid::Grid()
{
	isObstacle = false;
	isOccupied = false;
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

bool Grid::IsOccupied() const
{
	return isOccupied;
}

bool Grid::IsOnPath() const{
    return isOnPath;
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
	isOccupied = true;
}

void Grid::RemoveOccupied()
{
	isOccupied = false;
}

void Grid::MarkOnPath() {
    isOnPath = true;
}

void Grid::RemovePath() {
    isOnPath = false;
}





