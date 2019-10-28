
#include <vector>
#include <map>
#include <set>
#include <functional>
#include <iostream>

std::vector< int > getCriticalRouters( const std::vector< int >& routers,
									   const std::vector< std::pair< int, int > >& links )
{
	std::vector< int > ans;

	std::map< int, std::set< int > > nodes;

	for ( const auto link : links )
	{
		nodes[link.first].insert( link.second );
		nodes[link.second].insert( link.first );
	}

	std::function<void( std::vector< int >&, int, int )> getConnectionList;
	getConnectionList = [nodes, &getConnectionList]( std::vector< int >& connectedNodes, int currentNode, int brokenNode )
	{
		for ( auto it = nodes.at( currentNode ).begin(); it != nodes.at( currentNode ).end(); it++ )
		{
			auto x = *it;
			if ( x == brokenNode ) continue;
			if ( std::find( connectedNodes.begin(), connectedNodes.end(), x ) == connectedNodes.end() )
			{
				connectedNodes.push_back( x );
				getConnectionList( connectedNodes, x, brokenNode );
			}
		}
	};

	for ( const auto r : routers )
	{
		auto affectedNodes = nodes[r];
		if ( affectedNodes.size() < 2 ) { continue; }

		std::vector< int > connections;
		getConnectionList( connections, *affectedNodes.begin(), r );

		if ( connections.size() < routers.size() - 1 )
		{
			ans.push_back( r );
		}
	}

	return ans;
}

int main()
{
	// Test1
	{
		std::vector< int > routers = { 1,2,3,4,5 };
		std::vector< std::pair< int, int > > links = { {1,2}, {2,3}, {3,4}, {4,5}, {2,4} };
		auto ans = getCriticalRouters( routers, links );
		std::cout << "Critical routers: ";
		for ( const auto ir : ans )
		{
			std::cout << ir << "  ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;

	// Test2
	{
		std::vector< int > routers = { 1,2,3,4,5,6,7,8 };
		std::vector< std::pair< int, int > > links = { {1,2}, {2,3}, {3,4}, {4,5}, {5,6}, {6,3}, {3,7}, {7,8}, };
		auto ans = getCriticalRouters( routers, links );
		std::cout << "Critical routers: ";
		for ( const auto ir : ans )
		{
			std::cout << ir << "  ";
		}
		std::cout << std::endl;
	}

	std::cin.get();

	return 0;
}
