//=================================
// include guard
#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__
//=================================
#include "Grid.h"
#include "math.h"

class Node
{
	public:
		Node();
		Node(Grid*);
		void SetCost(int);
		int GetCost() const;
		Grid* GetGrid() const;
        Node* GetParent() const;
		void SetParent(Node*);
		int GetCostToAdjacent(Node*);
		int GetX() const;
		int GetY() const;
		bool IsEqual(Node*) const;

		bool InClosed();
		bool InOpen();
		void SetOpen(bool);
		void SetClosed(bool);

	private:
		Grid* grid;
		Node* parent;
		int cost;
		bool inOpen;
		bool inClosed;
};

#endif // __NODE_H_INCLUDED__ 

