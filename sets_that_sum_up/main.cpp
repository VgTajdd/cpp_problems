#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define USE_MEMOIZATION 0

#if USE_MEMOIZATION
int rec( const int s, const std::vector< int >& list, const int n, std::map< std::string, int >& memo )
#else
int rec( const int s, const std::vector< int >& list, const int n )
#endif
{
#if USE_MEMOIZATION
	char buffer_n[10], buffer_s[10];
	_itoa_s( n, buffer_n, 10 );
	_itoa_s( s, buffer_s, 10 );
	std::string key = buffer_s + std::string( "-" ) + buffer_n;
	if ( memo.find( key ) != memo.end() )
	{
		return memo.at( key );
	}
#endif
	if ( s == 0 ) return 1;
	if ( s < 0 ) return 0;
	if ( n == 0 ) return 0;
#if USE_MEMOIZATION
	if ( list[n - 1] > s )
	{
		memo[key] = rec( s, list, n - 1, memo );
		return memo[key];
	}
	memo[key] = rec( s - list[n - 1], list, n - 1, memo ) + rec( s, list, n - 1, memo );
	return memo[key];
#else
	if ( list[n - 1] > s ) return rec( s, list, n - 1 );
	return rec( s - list[n - 1], list, n - 1 ) + rec( s, list, n - 1 );
#endif
}

int findSetsOfNumbersThatSumUp( const int s, std::vector< int >& list )
{
	std::sort( list.begin(), list.end() ); // Ensure to have sorted (increasing) list.
#if USE_MEMOIZATION
	std::map< std::string, int > memo;
	return rec( s, list, list.size(), memo );
#else
	return rec( s, list, list.size() );
#endif
}

int main()
{
	std::vector<int> list = { 1,2,3,5,7,10 };
	std::cout << findSetsOfNumbersThatSumUp( 10, list );
	std::cin.get();
	return 0;
}