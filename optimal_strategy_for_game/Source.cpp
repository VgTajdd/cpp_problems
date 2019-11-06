/*

Optimal Strategy for a Game | Set 2
Problem statement: Consider a row of n coins of values v1 . . . vn, where n is even. We play a game against an opponent by alternating turns.
In each turn, a player selects either the first or last coin from the row, removes it from the row permanently, and receives the value of the coin.
Determine the maximum possible amount of money we can definitely win if we move first.

Note: The opponent is as clever as the user.

Let us understand the problem with few examples:

1. 5, 3, 7, 10 : The user collects maximum value as 15(10 + 5)

2. 8, 15, 3, 7 : The user collects maximum value as 22(7 + 15)

Does choosing the best at each move give an optimal solution?

No. In the second example, this is how the game can finish:

1.
…….User chooses 8.
…….Opponent chooses 15.
…….User chooses 7.
…….Opponent chooses 3.
Total value collected by user is 15(8 + 7)
2.
…….User chooses 7.
…….Opponent chooses 8.
…….User chooses 15.
…….Opponent chooses 3.
Total value collected by user is 22(7 + 15)
So if the user follows the second game state, maximum value can be collected although the first move is not the best.

*/

#include <iostream>
#include <algorithm>

int F( int sum, int i, int j, int arr[] )
{
	if ( i + 1 == j )
	{
		return std::max( arr[i], arr[j] );
	}
	return std::max( sum - F( sum - arr[i], i + 1, j, arr ), sum - F( sum - arr[j], i, j - 1, arr ) );
}

int getMaxPossibleOfPlayer( int arr[], int n )
{
	int sum = arr[0];
	for ( int i = 1; i < n; i++ )
	{
		sum += arr[i];
	}
	return F( sum, 0, n - 1, arr );
}

int main()
{
	int arr[] = { 8, 15, 3, 7 };
	int n = sizeof( arr ) / sizeof( arr[0] );
	std::cout << getMaxPossibleOfPlayer( arr, n ) << std::endl;
	std::cin.get();
	return 0;
}