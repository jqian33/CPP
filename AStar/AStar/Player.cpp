#include "Player.h"

Player::Player(Board* board) {
	mapLength = board->GetLength();
	mapWidth = board->GetWidth();
	std::vector<Node> column(mapLength);
	map = std::vector<std::vector<Node>>(mapWidth, column);
	
    // Player creates a recreates a representation of the board with Nodes,
    // Nodes are used during path finding
    for (int i = 0; i < map.size(); i++)
	{
		int columnCount = static_cast<int>(map[i].size());
		for (int j = 0; j < columnCount; j++)
		{
			map[i][j] = Node(board->GetGrid(j,i));
		}
	}
}

Player::Player(){
	mapWidth = 0;
	mapLength = 0;
}

void Player::SetPosition(int x, int y) {
	position = &map[y][x];
}

void Player::SetDestination(int x, int y) {
	destination = &map[y][x];
}

Grid* Player::GetPosition() {
	return position->GetGrid();
}

bool Player::OutOfBounds(int x, int y) {
	if (x > (mapWidth - 1) || x < 0 || y < 0 || y >(mapLength - 1)) {
		return true;
	}
	else {
		return false;
	}
}

std::vector<Node*> Player::GetAdjacent(Node* node) {
	std::vector<Node*> adjacentList;
	int x = node->GetX();
	int y = node->GetY();
	if (OutOfBounds(x + 1, y) != true) {
		adjacentList.push_back(&map[y][x + 1]);
	}
	if (OutOfBounds(x - 1, y) != true) {
		adjacentList.push_back(&map[y][x - 1]);
	}
	if (OutOfBounds(x, y + 1) != true) {
		adjacentList.push_back(&map[y + 1][x]);
	}
	if (OutOfBounds(x, y - 1) != true) {
		adjacentList.push_back(&map[y - 1][x]);
	}
	if (OutOfBounds(x + 1, y + 1) != true) {
		adjacentList.push_back(&map[y + 1][x + 1]);
	}
	if (OutOfBounds(x - 1, y + 1) != true) {
		adjacentList.push_back(&map[y + 1][x - 1]);
	}
	if (OutOfBounds(x - 1, y - 1) != true) {
		adjacentList.push_back(&map[y - 1][x - 1]);
	}
	if (OutOfBounds(x + 1, y - 1) != true) {
		adjacentList.push_back(&map[y - 1][x + 1]);
	}
	return adjacentList;
}

bool Player::CompareCost(Node* a, Node* b) {
	if (a->GetCost() < b->GetCost()) {
		return true;
	}
	else
	{
		return false;
	}
}

// Commented code uses PriorityQueue implementation
Node* Player::FindPath() {
	position->SetCost(0);
//	std::priority_queue<Node*, std::vector<Node*>, std::function<bool(Node*, Node*)>> openListPQ(CompareCost);
    std::multiset<Node*, bool(*)(Node*, Node*)> openList(CompareCost);
//	openListPQ.push(position);
    openList.insert(position);
	position->SetOpen(true);
    while(!openList.empty()){
//	while (!openListPQ.empty()) {
//		Node* current = openListPQ.top();
//		openListPQ.pop();
        std::set<Node*>::iterator it=openList.begin();
        Node* current = *it;
        openList.erase(it);
        
		current->SetOpen(false);
		current->SetClosed(true);
		if (current->IsEqual(destination))
		{
			return current;
		}
		std::vector<Node*> adjacentList = GetAdjacent(current);
		for (Node* n : adjacentList) {
			if ((!n->InClosed() && !n->GetGrid()->IsObstacle()))
			{
				if (!n->InOpen()) {
					n->SetOpen(true);
					n->SetParent(current);
//					openListPQ.push(n);
                    openList.insert(n);
				}
				else {
					if (n->GetCost() > (current->GetCostToAdjacent(n) + current->GetCost()))
					{
						Node updated(n->GetGrid());
						updated.SetParent(current);
                        openList.erase(&updated);
                        openList.insert(&updated);
						//openListPQ.push(&updated);
					}
				}
			}
		}
	}
	return NULL;
}
