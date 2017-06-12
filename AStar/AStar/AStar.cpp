// AStar.cpp : Defines the entry point for the console application.
//

#include "Board.h"
#include "Grid.h"
#include "Player.h"
#include "Node.h"

using namespace std;

int main()
{
	Board* board = new Board (6, 6);
	board->MarkOccupied(0, 0);
	board->Draw();

	Player p1(board);
	p1.SetPosition(0, 0);
	p1.SetDestination(3, 3);
	Node* pathNode = p1.FindPath();
    
    while (pathNode != NULL) {
        cout << "(" + std::to_string(pathNode->GetX()) + ", " + std::to_string(pathNode->GetY()) + ")";
        cout << endl;
        pathNode = pathNode->GetParent();
    }


	
	delete board;

}

