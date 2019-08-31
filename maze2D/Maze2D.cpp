#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include "Maze2D.h"

using namespace std;

Maze2D::Maze2D( const int n ) :
	size( n )
{
	count_directions = 4;
	dx = { 1, 0, -1, 0 };
	dy = { 0, 1, 0, -1 };
	map.resize( n, vector<int>( n ) );
}

Maze2D::~Maze2D()
{}

bool operator < ( const node& a, const node & b )
{
	//return a.getPriority() < b.getPriority(); // longest path
	return a.getPriority() > b.getPriority(); // shortest path
}

string Maze2D::pathFind()
{
	vector<vector<int>> closed_nodes_map;
	vector<vector<int>> open_nodes_map;
	vector<vector<int>> dir_map;

	closed_nodes_map.resize( size, vector<int>( size ) );
	open_nodes_map.resize( size, vector<int>( size ) );
	dir_map.resize( size, vector<int>( size ) );

	priority_queue<node> pq[2]; // Open nodes list (not tested).
	int pqi = 0; // pq indexes.
	node* n0;
	node* m0;
	int i, j, x, y, xdx, ydy;
	char c;

	// Reset
	for ( y = 0; y < size; y++ )
	{
		for ( x = 0; x < size; x++ )
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}

	// Create starting node and put in open list.
	n0 = new node( xA, yA, 0, 0 );

	n0->updatePriority( xB, yB );
	pq[pqi].push( *n0 );
	open_nodes_map[0][0] = n0->getPriority();

	// Busqueda A*
	while ( !pq[pqi].empty() )
	{
		// Get the current node with the highest priority from the open list.
		n0 = new node( pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
					   pq[pqi].top().getLevel(), pq[pqi].top().getPriority() );

		x = n0->getxPos(); y = n0->getyPos();

		pq[pqi].pop(); // Remove node from open list.
		open_nodes_map[x][y] = 0;
		closed_nodes_map[x][y] = 1; // Mark in close nodes map.

		// Stop the search when the target is found.
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if ( x == xB && y == yB )
		{
			// Generate the path from end to start following directions.
			string path = "";
			while ( !( x == xA && y == yA ) )
			{
				j = dir_map[x][y];
				c = '0' + ( j + count_directions / 2 ) % count_directions;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			delete n0;
			// Empty all nodes.
			while ( !pq[pqi].empty() ) pq[pqi].pop();
			return path;
		}

		// Generating child nodes in all possible positions.
		for ( i = 0; i < count_directions; i++ )
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if ( !( xdx<0 || xdx>size - 1 || ydy<0 || ydy>size - 1 || map[xdx][ydy] == 1 || closed_nodes_map[xdx][ydy] == 1 ) )
			{
				m0 = new node( xdx, ydy, n0->getLevel(),
							   n0->getPriority() ); // Generating child node.
				m0->nextLevel( i, count_directions );
				m0->updatePriority( xB, yB );

				// If it's not in the open nodes list: add to it.
				if ( open_nodes_map[xdx][ydy] == 0 )
				{
					open_nodes_map[xdx][ydy] = m0->getPriority();
					pq[pqi].push( *m0 );
					// Mark its parent node direction.
					dir_map[xdx][ydy] = ( i + count_directions / 2 ) % count_directions;
				}
				else if ( open_nodes_map[xdx][ydy] > m0->getPriority() )
				{
					// Update priority.
					open_nodes_map[xdx][ydy] = m0->getPriority();
					// Update parent direction.
					dir_map[xdx][ydy] = ( i + count_directions / 2 ) % count_directions;

					while ( !( pq[pqi].top().getxPos() == xdx &&
							   pq[pqi].top().getyPos() == ydy ) )
					{
						pq[1 - pqi].push( pq[pqi].top() );
						pq[pqi].pop();
					}
					pq[pqi].pop(); // Remove not desired node.

					if ( pq[pqi].size() > pq[1 - pqi].size() ) pqi = 1 - pqi;
					while ( !pq[pqi].empty() )
					{
						pq[1 - pqi].push( pq[pqi].top() );
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push( *m0 ); // Add de best node.
				}
				else delete m0;
			}
		}
		delete n0;
	}
	return ""; // Path not found.
}

void Maze2D::generateRandom()
{
	xA = 1; yA = 1;
	srand( ( unsigned ) time( NULL ) ); // only once.
	xB = size - 2;
	yB = ( rand() % size - 2 ) + 1;

	int	num1 = 0;
	for ( int i = 0; i < size; i++ )
	{
		for ( int j = 0; j < size; j++ )
		{
			num1 = rand() % 100;
			if ( num1 < 30 )
			{
				map[i][j] = 1;
			}
			else
			{
				map[i][j] = 0;
			}
		}
	}
	map[xA][yA] = 0;
	map[xB][yB] = 0;
	for ( int i = 0; i < size; i++ )
	{
		map[size - 1][i] = 1;
	}
	for ( int i = 0; i < size; i++ )
	{
		map[i][size - 1] = 1;
	}
	for ( int i = 0; i < size; i++ )
	{
		map[0][i] = 1;
	}
	for ( int i = 0; i < size; i++ )
	{
		map[i][0] = 1;
	}
}