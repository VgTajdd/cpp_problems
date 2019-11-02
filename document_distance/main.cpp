#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

std::string readFile( const std::string& filepath )
{
	std::ifstream stream( filepath );
	std::string line;
	std::stringstream ss;

	while ( getline( stream, line ) )
	{
		ss << line << std::endl;
	}
	return ss.str();
}

/*
	This method supports special characters as part of word.
*/
const bool isWordCharacter( const char c )
{
	// ASCII reference: https://elcodigoascii.com.ar/
	if ( ( c >= 65 && c <= 90 ) // A-Z.
		 || ( c >= 97 && c <= 122 ) // a-z.
		 || ( c >= 48 && c <= 57 ) // 0-9.
		 || c == 'ñ' // ñ.
		 || c == 'á' // á.
		 || c == 'é' // é.
		 || c == 'í' // í.
		 || c == 'ó' // ó.
		 || c == 'ú' // ú.
		 || c == 'Á' // Á.
		 || c == 'É' // É.
		 || c == 'Í' // Í.
		 || c == 'Ó' // Ó.
		 || c == 'Ú' // Ú.
		 )
	{
		return true;
	}
	return false;
}

std::map< std::string, double > getFrequencies( const std::string& filepath, const bool normalized )
{
	unsigned int count = 0;
	std::map< std::string, double > frequencies;

	std::string text = readFile( filepath );

	unsigned int start = 0, end = 0;
	bool inWord = false;
	for ( int i = 0; i < text.size(); i++ )
	{
		if ( !( inWord ) && /*( isalpha( text[i] ) || isdigit( text[i] ) )*/ isWordCharacter( text[i] ) )
		{
			inWord = true;
			start = i;
		}
		else if ( ( inWord ) && /*( !isalpha( text[i] ) && !isdigit( text[i] ) )*/ !isWordCharacter( text[i] ) )
		{
			inWord = false;
			frequencies[text.substr( start, i - start )]++;
			count++;
		}
	}
	if ( inWord ) // Last word.
	{
		inWord = false;
		frequencies[text.substr( start, text.size() - start )]++;
		count++;
	}

	if ( normalized && count != 0 )
	{
		double accumulator = 0.0;
		for ( auto&[key, freq] : frequencies )
		{
			accumulator += freq * freq;
		}
		accumulator = pow( accumulator, 0.5 );
		for ( auto&[key, freq] : frequencies )
		{
			freq /= double( accumulator );
		}
	}

	return frequencies;
}

const double getDocumentDistance( const std::string& filepath1, const std::string& filepath2 )
{
	auto frequencies1 = getFrequencies( filepath1, true );
	auto frequencies2 = getFrequencies( filepath2, true );

	double accumulator = 0.0;
	for ( const auto[key, freq] : frequencies1 )
	{
		if ( frequencies2.find( key ) != frequencies2.end() )
		{
			accumulator += freq * frequencies2.at( key );
		}
	}

	return accumulator;
}

int main()
{
	std::cout << getDocumentDistance( "t2.bobsey.txt", "t2.bobsey.txt" ) << std::endl;
	std::cout << getDocumentDistance( "t2.bobsey.txt", "t3.lewis.txt" ) << std::endl;
	std::cout << getDocumentDistance( "t3.lewis.txt", "t3.lewis.txt" ) << std::endl;

	std::cin.get();
	return 0;
}