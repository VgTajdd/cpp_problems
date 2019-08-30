#include <string>
#include <iostream>
#include <ctime>
#include <conio.h>
#include "Maze2D.h"

using namespace std;

void createMaze2D( int nn )
{
	string ruta = "";
	clock_t start = clock();
	double time_transcurrido;
	Maze2D maze( nn );
	maze.crear_random();
	ruta = maze.pathFind( maze.xA, maze.yA, maze.xB, maze.yB );
	time_transcurrido = ( std::clock() - start ) / ( double ) CLOCKS_PER_SEC;
	cout << "Tiempo para calcular la ruta(ms): " << time_transcurrido << endl;
	cout << "Ruta:" << endl;
	cout << ruta << endl << endl;

	if ( ruta.length() > 0 )
	{
		int j; char c;
		int x = maze.xA;
		int y = maze.yA;
		maze.map[x][y] = 2;
		for ( int i = 0; i < static_cast<int>( ruta.length() ); i++ )
		{
			c = ruta.at( i );
			j = atoi( &c );
			x = x + maze.dx[j];
			y = y + maze.dy[j];
			maze.map[x][y] = 3;
		}
		maze.map[x][y] = 4;

		// Mostrar el mapa con la Ruta
		for ( int y = 0; y < nn; y++ )
		{
			for ( int x = 0; x < nn; x++ )
				if ( maze.map[x][y] == 0 )
					cout << " ";
				else if ( maze.map[x][y] == 1 )
					cout << "*"; //Pared
				else if ( maze.map[x][y] == 2 )
					cout << "A"; //Inicio
				else if ( maze.map[x][y] == 3 )
					cout << "+"; //Ruta
				else if ( maze.map[x][y] == 4 )
					cout << "B"; //Final
			cout << endl;
		}
	}
}

int main()
{
	int n_max = 50;
	cout << "Ingrese la \"n\" <dimension del laberinto>: ";
	int nn;
	cin >> nn;
	for ( ;; )
	{
		if ( nn > n_max )
		{
			cout << "\nEl valor es muy grande, ingrese uno menor o igual a " << n_max << " :" << endl;
			cin >> nn;
		}
		else
		{
			cout << "\nEl laberinto es de \"" << nn << " x " << nn << "\"" << endl;
			break;
		}
	}
	//srand( time( NULL ) );
	createMaze2D( nn );
	_getch();
	return( 0 );
}
