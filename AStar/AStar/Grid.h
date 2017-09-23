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
		bool IsOccupied() const;
        bool IsOnPath() const;
		void MarkObstacle();
		void RemoveObstacle();
		void MarkOccupied();
		void RemoveOccupied();
        void MarkOnPath();
        void RemovePath();

	private:
		int x;
		int y;
		bool isObstacle;
		bool isOccupied;
        bool isOnPath;

};
#endif // __GRID_H_INCLUDED__ 
