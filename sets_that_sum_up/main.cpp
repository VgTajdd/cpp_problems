#include <iostream>
#include <vector>
#include <algorithm>

int rec( const int s, const std::vector< int >& list, const int n )
{
	if ( s == 0 ) return 1;
	if ( s < 0 ) return 0;
	if ( n <= 0 ) return 0;
	if ( list[n - 1] > s ) return rec( s, list, n - 1 );
	return rec( s - list[n - 1], list, n - 1 ) + rec( s, list, n - 1 );
}

int findSetsOfNumbersThatSumUp( const int s, std::vector< int >& list )
{
	std::sort( list.begin(), list.end() ); // Ensure to have sorted (increasing) list.
	return rec( s, list, list.size() );
}

int main()
{
	std::vector<int> list = { 1,2,3,5,7,10 };
	std::cout << findSetsOfNumbersThatSumUp( 10, list );
	std::cin.get();
	return 0;
}