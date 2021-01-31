#include <iostream>
#include <vector>
#include <map>

int getSumOfDigits( int n )
{
	int sum = 0;
	while ( n )
	{
		int temp = n % 10;
		sum += temp;
		n /= 10;
	}
	return sum;
}

struct TwoMaxStore
{
	int a = -1;
	int b = -1;
	bool size = 0;
};

int solution( std::vector<int>& A )
{
	int ans = -1;

	if ( A.size() < 2 )
		return ans;

	std::map<int, TwoMaxStore> sumsMax;

	for ( size_t i = 0; i < A.size(); i++ )
	{
		int currentSum = getSumOfDigits( A[i] );

		if ( sumsMax[currentSum].size == 0 )
		{
			sumsMax[currentSum].a = A[i];
			sumsMax[currentSum].size++;
		}
		else if ( sumsMax[currentSum].size == 1 )
		{
			sumsMax[currentSum].b = A[i];
			sumsMax[currentSum].size++;

			if ( sumsMax[currentSum].a + sumsMax[currentSum].b > ans )
				ans = sumsMax[currentSum].a + sumsMax[currentSum].b;
		}
		else
		{
			if ( sumsMax[currentSum].a < A[i] )
				sumsMax[currentSum].a = A[i];
			else if ( sumsMax[currentSum].b < A[i] )
				sumsMax[currentSum].b = A[i];

			if ( sumsMax[currentSum].a + sumsMax[currentSum].b > ans )
				ans = sumsMax[currentSum].a + sumsMax[currentSum].b;
		}
	}

	return ans;
}

int main()
{
	std::cout << getSumOfDigits( 12345 ) << std::endl;
	std::cout << getSumOfDigits( 999 ) << std::endl;
	std::cout << getSumOfDigits( 1 ) << std::endl;
	std::cout << getSumOfDigits( 0 ) << std::endl;

	std::vector<int> b{ 42,33,60 };
	std::vector<int> c{ 51,71,17,42 };

	std::cout << solution( b ) << std::endl;
	std::cout << solution( c ) << std::endl;

	std::cin.get();
	return 0;
}