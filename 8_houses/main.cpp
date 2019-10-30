#include <iostream>
#include <vector>

std::vector< int > cellCompete( int* states, int days )
{
    const int countHouses = 8;

    std::vector< int > ans, buffer;
    ans.resize( countHouses + 2, 0 ); // Adding 2 virtual houses to left/right.
    buffer = ans; // Buffer will contain a copy of the last day states.
    std::copy( states, states + 8, ans.begin() + 1 );

    for ( int d = 0; d < days; d++ ) // Loop for days.
    {
        for ( int i = 1; i < countHouses + 1; i++ ) // Loop for houses.
        {
            buffer[i] = ( ans[i - 1] == ans[i + 1] ) ? 0 : 1; // Filling buffer.
        }
        ans = buffer;
    }

    // Removing empty houses.
    ans.erase( ans.begin() );
    ans.pop_back();

    return ans;
}

int main()
{
    // Test 1:
    {
        int states[] = { 1,0,1,0,0,1,1,1 };
        std::vector< int > ans = cellCompete( states, 10 );
        std::cout << "[Test 1] States afters 10 days: ";
        for ( const auto& state : ans )
        {
            std::cout << state << " ";
        }
    }

    std::cout << std::endl;

    // Test 2:
    {
        int states[] = { 1,0,0,0,0,1,0,1 };
        std::vector< int > ans = cellCompete( states, 100 );
        std::cout << "[Test 2] States afters 100 days: ";
        for ( const auto& state : ans )
        {
            std::cout << state << " ";
        }
    }

    std::cout << std::endl;

    std::cin.get();
    return 0;
}