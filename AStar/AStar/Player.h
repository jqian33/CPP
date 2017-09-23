//=================================
// include guard
#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__
//=================================
#include "Board.h"
#include "Node.h"
#include <vector>
#include <set>

class Player
{
	public:
		Player(Board*);
		Player();
		bool OutOfBounds(int, int);
		void SetPosition(int, int);
		void SetDestination(int, int);
		Grid* GetPosition();
		std::vector<Node*> GetAdjacent(Node*);
		static bool CompareCost(Node*, Node*);
		Node* FindPath();

	private:
		std::vector<std::vector<Node> > map;
		int mapWidth;
		int mapLength;
		Node* position;
		Node* destination;

};

#endif // __PLAYER_H_INCLUDED__
