#include "Node.h"
#include <stdlib.h>

Node::Node(Grid* g) : grid(g) {
	inClosed = false;
	inOpen = false;
    parent = NULL;
}

Node::Node(){
	inClosed = false;
	inOpen = false;
}

void Node::SetCost(int value) {
	cost = value;
}

int Node::GetX() const {
	return grid->GetX();
}

int Node::GetY() const {
	return grid->GetY();
}

int Node::GetCost() const {
	return cost;
}

Grid* Node::GetGrid() const {
	return grid;
}

Node* Node::GetParent() const {
    return parent;
}

void Node::SetOpen(bool openStatus) {
	inOpen = openStatus;
}

void Node::SetClosed(bool closedStatus) {
	inClosed = closedStatus;
}

bool Node::InOpen() {
	return inOpen;
}

bool Node::InClosed() {
	return inClosed;
}

bool Node::IsEqual(Node* n) const
{
	if (GetX() == n->GetX() && GetY() == n->GetY())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Node::GetCostToAdjacent(Node* adjacent)
{
	if (abs(adjacent->GetX() - GetX()) == 1 && abs(adjacent->GetY() - GetY()) == 1) {
		return 14;
	}
	else {
		return 10;
	}
}

void Node::SetParent(Node* parentNode) {
	cost = parentNode->GetCost() + GetCostToAdjacent(parentNode);
	parent = parentNode;
}


