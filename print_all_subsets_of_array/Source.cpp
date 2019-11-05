
#include <iostream>
#include <vector>

void printVector( const std::vector< int >& v )
{
	std::cout << "{";
	for ( unsigned int i = 0; i < v.size(); i++ )
	{
		std::cout << v[i] << ",";
	}
	std::cout << "}" << std::endl;
}

void helper( const std::vector< int >& subset, const std::vector<int>& v, int index )
{
	if ( index == v.size() )
	{
		printVector( subset );
		return;
	}
	std::vector< int > va = subset, vb = subset;
	va.push_back( v.at( index ) );
	index++;
	helper( va, v, index );
	helper( vb, v, index );
}

void printAllSubSets( const std::vector<int>& v )
{
	std::vector< int > subset;
	helper( subset, v, 0 );
}

int main()
{
	std::vector< int > v = { 1, 2, 3, 4, 5 };
	printAllSubSets( v );

	std::cin.get();
	return 0;
}