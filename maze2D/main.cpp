#include <string>
#include <iostream>
#include <ctime>
#include <conio.h>
#include "Maze2D.h"

using namespace std;

void createMaze2D( int n )
{
	string path = "";
	Maze2D maze( n );
	maze.generateRandom();
	clock_t start = clock();
	double time_elapsed;
	path = maze.pathFind();
	time_elapsed = ( std::clock() - start ) / ( double ) CLOCKS_PER_SEC;
	cout << "Time to find the path(ms): " << time_elapsed << endl << endl;
	cout << "Path:" << endl;
	cout << path << endl << endl;

	if ( path.length() > 0 )
	{
		int j; char c;
		int x = maze.xA;
		int y = maze.yA;
		maze.map[x][y] = 2;
		for ( int i = 0; i < static_cast<int>( path.length() ); i++ )
		{
			c = path.at( i );
			j = atoi( &c );
			x = x + maze.dx[j];
			y = y + maze.dy[j];
			maze.map[x][y] = 3;
		}
		maze.map[x][y] = 4;
	}

	for ( int y = 0; y < n; y++ )
	{
		for ( int x = 0; x < n; x++ )
			if ( maze.map[x][y] == 0 )
				cout << " ";
			else if ( maze.map[x][y] == 1 )
				cout << "*"; // Wall
			else if ( maze.map[x][y] == 2 )
				cout << "A"; // Start
			else if ( maze.map[x][y] == 3 )
				cout << "+"; // Path
			else if ( maze.map[x][y] == 4 )
				cout << "B"; // End
		cout << endl;
	}
}

int main()
{
	int n_max = 100;
	int n_min = 4;
	string msg = "Enter maze size \"n\" [3 - 100]: ";
	cout << msg;
	int nn;
	cin >> nn;
	for ( ;; )
	{
		if ( nn > n_max	|| nn < n_min )
		{
			cout << msg << endl;
			cin >> nn;
		}
		else
		{
			cout << "Maze dimensions are: " << nn << " x " << nn << endl;
			break;
		}
	}
	createMaze2D( nn );
	_getch();
	return( 0 );
}
