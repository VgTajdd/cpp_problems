#pragma once

#include <vector>

using namespace std;

class Maze2D
{
public:
	Maze2D( const int size );
	~Maze2D();
	string pathFind();
	void generateRandom();
public:
	int xA, yA, xB, yB;
	int size;
	vector<vector<int>> map;
	int count_directions;
	vector<int> dx;
	vector<int> dy;
};

class node
{
public:
	node( int xp, int yp, int d, int p )
	{
		xPos = xp; yPos = yp; level = d; priority = p;
	}

public:
	int getxPos() const { return xPos; }
	int getyPos() const { return yPos; }
	int getLevel() const { return level; }
	int getPriority() const { return priority; }

	void updatePriority( const int& xDest, const int& yDest )
	{
		priority = level + estimate( xDest, yDest ) * 10; //A*
	}

	void nextLevel( const int& i, const int count_directions ) // i: direction
	{
		level += ( count_directions == 8 ? ( i % 2 == 0 ? 10 : 14 ) : 10 );
	}

	const int estimate( const int & xDest, const int & yDest ) const
	{
		int xd, yd, d;
		xd = xDest - xPos;
		yd = yDest - yPos;

		// Euclidian distance
		//d=static_cast<int>(powl((xd*xd+yd*yd),0.5));

		// Manhattan distance
		d = abs( xd ) + abs( yd );

		// Chebyshev distance
		//d=max(abs(xd), abs(yd));

		return d;
	}

public:
	int xPos;
	int yPos;
	int level; // total distance traveled to get the node.
	int priority; // lower : more priority
};