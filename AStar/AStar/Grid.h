//=================================
// include guard
#ifndef __GRID_H_INCLUDED__
#define __GRID_H_INCLUDED__
//=================================
class Grid
{
	public:
		Grid();
		Grid(int x, int y, bool available, bool occupied);
		int GetX() const;
		int GetY() const;
		bool IsObstacle() const;
		bool Occupied() const;
		void MarkObstacle();
		void RemoveObstacle();
		void MarkOccupied();
		void RemoveOccupied();
	
	private:
		int x;
		int y;
		bool isObstacle;
		bool occupied;



};
#endif // __GRID_H_INCLUDED__ 
