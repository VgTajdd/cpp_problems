#include <iostream>
#include <vector>

int generalizedGCD( int num, int* arr )
{
    int gcd = 1;
    int minValue = arr[0];

    for ( int i = 1; i < num; i++ )
    {
        if ( minValue > arr[i] ) minValue = arr[i];
    }

    std::vector< int > divisors;

    // Iterating from high to low values to optimize search.
    for ( int i = minValue; i > 1; i-- )
    {
        if ( minValue % i == 0 )
        {
            divisors.push_back( i );
        }
    }

    for ( auto it = divisors.begin(); it != divisors.end(); it++ )
    {
        int divisor = *it;
        bool foundGCD = true;
        for ( int i = 0; i < num; i++ )
        {
            if ( arr[i] % ( divisor ) != 0 )
            {
                foundGCD = false;
                break;
            }
        }
        if ( foundGCD )
        {
            gcd = divisor;
            break;
        }
    }

    return gcd;
}

int main()
{
    // Test 1.
    {
        int values[] = { 3, 12, 24, 9, 15 };
        std::cout << "[Test1] GCD of 3, 12, 24, 9, 15: " << generalizedGCD( 5, values ) << std::endl;
    }
    // Test 2.
    {
        int values[] = { 21, 28, 49, 70, 14, 105 };
        std::cout << "[Test2] GCD of 21, 28, 49, 70, 14, 105: " << generalizedGCD( 6, values ) << std::endl;
    }

    std::cin.get();
    return 0;
}