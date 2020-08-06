#include <iostream>

void reverseArray( int* start, int* end )
{
	while ( (intptr_t) start - (intptr_t) end >= 2 * sizeof( int* ) )
	{
		std::swap( *start++, *end-- );
	}
}

int main()
{

	int arr[] = { 1,2,3,4,5 };
	reverseArray( &arr[0], &arr[4] );

	for ( int i = 0; i < sizeof( arr ) / sizeof( int ); i++ )
	{
		printf( "%d", arr[i] );
	}

	std::cin.get();

	return 0;
}