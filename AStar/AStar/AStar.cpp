// AStar.cpp : Defines the entry point for the console application.
//

#include "AStar.h"

using namespace std;

int main()
{
	Board* board = new Board (10, 10);
    board->MarkOccupied(0, 0);
    board->MarkObstacle(6, 6);
    board->MarkObstacle(6, 9);
//    board->MarkObstacle(6, 8);
    board->MarkObstacle(6, 7);
    board->MarkObstacle(6, 5);
    board->MarkObstacle(6, 4);
    board->MarkObstacle(6, 3);
    board->MarkObstacle(6, 2);
    board->MarkObstacle(6, 1);
    
    board->MarkObstacle(4, 6);
    board->MarkObstacle(4, 9);
    board->MarkObstacle(4, 8);
    board->MarkObstacle(4, 7);
    board->MarkObstacle(4, 5);
    board->MarkObstacle(4, 4);
    board->MarkObstacle(4, 3);
    board->MarkObstacle(4, 2);
    board->MarkObstacle(4, 1);
    
    board->MarkObstacle(7, 7);
    board->MarkObstacle(8, 7);
    board->MarkObstacle(9, 7);
    board->MarkObstacle(7, 9);
    board->MarkObstacle(8, 9);
    board->MarkObstacle(9, 9);
    board->MarkObstacle(5, 9);
    
    board->Draw();

    Player p1(board);
    p1.SetPosition(0, 0);
    p1.SetDestination(9, 8);
    Node* pathNode = p1.FindPath();

    board->TracePath(pathNode);
	
	delete board;

}

