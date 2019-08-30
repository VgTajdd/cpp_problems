#include "Maze2D.h"

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <conio.h>

using namespace std;

Maze2D::Maze2D( const int n ) :
	size( n )
{
	count_directions = 4;
	dx = { 1, 0, -1, 0 };
	dy = { 0, 1, 0, -1 };
	map.resize( n, vector<int>( n ) );
	closed_nodes_map.resize( n, vector<int>( n ) );
	open_nodes_map.resize( n, vector<int>( n ) );
	dir_map.resize( n, vector<int>( n ) );
}

Maze2D::~Maze2D()
{}

string Maze2D::pathFind( const int & xStart, const int & yStart, const int & xFinish, const int & yFinish )
{
	static priority_queue<node> pq[2]; // lista de nodos abiertos (no intentados)
	static int pqi; // pq indices
	static node* n0;
	static node* m0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi = 0;

	// Reseteando el mapa de nodos
	for ( y = 0; y < size; y++ )
	{
		for ( x = 0; x < size; x++ )
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}

	// Crear el nodo de inicio y ponerlo en la lista de abiertos
	n0 = new node( xStart, yStart, 0, 0 );

	n0->updatePriority( xFinish, yFinish );
	pq[pqi].push( *n0 );
	open_nodes_map[x - 1][y - 1] = n0->getPriority();

	// Busqueda A*
	while ( !pq[pqi].empty() )
	{
		// Obetener el nodo actual con la prioridad mas alta
		// desde la lista de nodos abiertos
		n0 = new node( pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
					   pq[pqi].top().getLevel(), pq[pqi].top().getPriority() );

		x = n0->getxPos(); y = n0->getyPos();

		pq[pqi].pop(); // Remover el nodo de la lista abiertos.
		open_nodes_map[x][y] = 0;
		// Marcarlo en el mapa de los nodos cerrados
		closed_nodes_map[x][y] = 1;

		// Para la busqueda cuando el objetivo es alcanzado
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if ( x == xFinish && y == yFinish )
		{
			// Genera el camino desde el final al inicio
			// siguiendo las direcciones
			string path = "";
			while ( !( x == xStart && y == yStart ) )
			{
				j = dir_map[x][y];
				c = '0' + ( j + count_directions / 2 ) % count_directions;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			delete n0;
			// Vaciar los demas nodos
			while ( !pq[pqi].empty() ) pq[pqi].pop();
			return path;
		}

		// Generando nodos hijos en todas las posiciones posibles
		for ( i = 0; i < count_directions; i++ )
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if ( !( xdx<0 || xdx>size - 1 || ydy<0 || ydy>size - 1 || map[xdx][ydy] == 1 || closed_nodes_map[xdx][ydy] == 1 ) )
			{
				// Generando nodo hijo
				m0 = new node( xdx, ydy, n0->getLevel(),
							   n0->getPriority() );
				m0->nextLevel( i, count_directions );
				m0->updatePriority( xFinish, yFinish );

				// Si no esta en la lista abierta: adicionarlo a esta
				if ( open_nodes_map[xdx][ydy] == 0 )
				{
					open_nodes_map[xdx][ydy] = m0->getPriority();
					pq[pqi].push( *m0 );
					// Marcar la direccion de su nodo padre
					dir_map[xdx][ydy] = ( i + count_directions / 2 ) % count_directions;
				}
				else if ( open_nodes_map[xdx][ydy] > m0->getPriority() )
				{
					// Acualizar la prioridad
					open_nodes_map[xdx][ydy] = m0->getPriority();
					// Acuatliza la dierccion del padre
					dir_map[xdx][ydy] = ( i + count_directions / 2 ) % count_directions;

					while ( !( pq[pqi].top().getxPos() == xdx &&
							   pq[pqi].top().getyPos() == ydy ) )
					{
						pq[1 - pqi].push( pq[pqi].top() );
						pq[pqi].pop();
					}
					pq[pqi].pop(); // Removiendo el nodo deseado

					if ( pq[pqi].size() > pq[1 - pqi].size() ) pqi = 1 - pqi;
					while ( !pq[pqi].empty() )
					{
						pq[1 - pqi].push( pq[pqi].top() );
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push( *m0 ); // adicionar el mejor nodo
				}
				else delete m0;
			}
		}
		delete n0;
	}
	return ""; // No se encontro ruta
}

void Maze2D::crear_random()
{
	xA = 1; yA = 1;
	srand( time( NULL ) );
	xB = size - 2;
	yB = ( rand() % size - 2 ) + 1;

	int	num1 = 0;
	srand( time( NULL ) );
	for ( int i = 0; i < size; i++ )
	{
		for ( int j = 0; j < size; j++ )
		{
			num1 = rand() % 100;
			if ( num1 < 20 )
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