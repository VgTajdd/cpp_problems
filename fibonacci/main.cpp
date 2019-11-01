#include <iostream>
#include <map>
#include <vector>

// Using recursion.
// Time complexity O(2^n) (ALT+94 = ^).
int fib_r( const int n )
{
	if ( n == 1 || n == 2 )
	{
		return 1;
	}
	return fib_r( n - 1 ) + fib_r( n - 2 );
}

// Using memoization.
// Time complexity O(n).
int fib_m( const int n, std::map<int, int>& memo )
{
	if ( n == 1 || n == 2 )
	{
		return 1;
	}
	if ( memo.find( n ) != memo.end() )
	{
		return memo.at( n );
	}
	int result = fib_m( n - 1, memo ) + fib_m( n - 2, memo );
	memo[n] = result;
	return result;
}

// Using bottom-up.
// Time complexity O(n).
int fib_bu( const int n )
{
	std::vector< int > buffer;
	buffer.resize( n, 1 );
	for ( int i = 3; i <= n; i++ )
	{
		buffer[i - 1] = buffer[i - 2] + buffer[i - 3];
	}
	return buffer[n - 1];
}

int main()
{
	{
		std::cout << "Test Fibonacci recursive" << std::endl;
		std::cout << "Fib(38) = " << fib_r( 38 ) << std::endl;
	}
	std::cout << std::endl;
	{
		std::cout << "Test Fibonacci memoization" << std::endl;
		std::map< int, int > memo;
		std::cout << "Fib(40) = " << fib_m( 40, memo ) << std::endl;
	}
	std::cout << std::endl;
	{
		std::cout << "Test Fibonacci bottom-up" << std::endl;
		std::cout << "Fib(5) = " << fib_bu( 5 ) << std::endl;
		std::cout << "Fib(40) = " << fib_bu( 40 ) << std::endl;
	}
	std::cout << std::endl;

	std::cin.get();
	return 0;
}