#pragma once

#include <vector>
using namespace std;

class Maze2D
{
public:
	Maze2D( const int size );
	~Maze2D();
	string pathFind( const int & xStart, const int & yStart, const int & xFinish, const int & yFinish );
	void crear_random();
	void print();
public:
	int xA, yA, xB, yB;
	int size;
	vector<vector<int>> map;/*int map[n][n];*/
	vector<vector<int>> closed_nodes_map;/*int closed_nodes_map[n][n]*/
	vector<vector<int>> open_nodes_map;/*int open_nodes_map[n][n]*/
	vector<vector<int>> dir_map;/*int dir_map[n][n]*/
	int count_directions/* = 4*/;
	vector<int> dx;//int dx[dir] = { 1, 0, -1, 0 };
	vector<int> dy;//int dy[dir] = { 0, 1, 0, -1 };
};

class node
{
	// Posicion actual
	int xPos;
	int yPos;
	// distancia total viajada para alcanzar el nodo
	int level;
	// priority=level+distancia que hay por estimar
	int priority;  // pequeña : mayor prioridad

public:
	node( int xp, int yp, int d, int p )
	{
		xPos = xp; yPos = yp; level = d; priority = p;
	}

	int getxPos() const { return xPos; }
	int getyPos() const { return yPos; }
	int getLevel() const { return level; }
	int getPriority() const { return priority; }

	void updatePriority( const int & xDest, const int & yDest )
	{
		priority = level + estimate( xDest, yDest ) * 10; //A*
	}

	void nextLevel( const int& i, const int count_directions ) // i: direction
	{
		level += ( count_directions == 8 ? ( i % 2 == 0 ? 10 : 14 ) : 10 );
	}

	const int & estimate( const int & xDest, const int & yDest ) const
	{
		static int xd, yd, d;
		xd = xDest - xPos;
		yd = yDest - yPos;

		// Distancia Euclidiana
		//d=static_cast<int>(powl((xd*xd+yd*yd),0.5));

		// Distancia Manhattan
		d = abs( xd ) + abs( yd );

		// Distancia Chebyshev
		//d=max(abs(xd), abs(yd));

		return( d );
	}
};

inline bool operator < ( const node & a, const node & b )
{
	// Determinar prioridad
	//return a.getPriority() < b.getPriority();//camino mas largo
	return a.getPriority() > b.getPriority();//camino mas corto
}