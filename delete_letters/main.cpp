#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

int solution2( std::string& S )
{
	if ( S.size() < 2 )
	{
		return 0;
	}

	std::map<char, int> frequency;

	for ( const auto& c : S )
	{
		if ( frequency.find( c ) != frequency.end() )
		{
			frequency[c]++;
		}
		else
		{
			frequency[c] = 1;
		}
	}

	std::vector<int> frequencyVector;

	for ( const auto& it : frequency )
	{
		frequencyVector.emplace_back( it.second );
	}

	std::sort( frequencyVector.rbegin(), frequencyVector.rend() );

	int deletions = 0;

	int oldValue = frequencyVector[0]; // max

	for ( size_t i = 1; i < frequencyVector.size(); i++ )
	{
		while ( frequencyVector[i] >= oldValue )
		{
			if ( frequencyVector[i] == 0 )
			{
				break;
			}
			deletions++;
			frequencyVector[i]--;
		}
		oldValue = frequencyVector[i];
	}

	return deletions;
}

int main()
{
	std::string a( "ccaaffddecee" );

	std::vector<std::string> inputs = { "a", "aabb", "ccaaffddecee" };

	for ( auto& input : inputs )
	{
		std::printf( "The solution for \"%s\" is: %d\n", input.c_str(), solution2( input ) );
	}

	std::cin.get();
	return 0;
}