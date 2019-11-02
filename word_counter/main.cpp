#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

static std::string readFile( const std::string& filepath )
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

static void trimString( std::string& str, const bool left )
{
	if ( str.empty() ) return;

	size_t position = str.size() - 1;
	int increment = -1;
	if ( left )
	{
		position = 0;
		increment = 0;
	}

	while ( str[position] == ' ' || str[position] == '\n' )
	{
		str.erase( str.begin() + position );
		position += increment;
	}
}

static const size_t findFirstChar( const std::string& str, const std::string& chars )
{
	size_t index = std::string::npos;
	for ( const auto& c : chars )
	{
		size_t t_index = str.find( c );
		if ( t_index != std::string::npos )
		{
			if ( index == -1 || t_index < index )
			{
				index = t_index;
			}
		}
	}
	return index;
}

static const int countWords( const std::string& str )
{
	unsigned int count = 0;
	std::string temp_string = str;
	trimString( temp_string, true );
	trimString( temp_string, false );

	while ( !temp_string.empty() )
	{
		size_t index = findFirstChar( temp_string, " .,\n" );

		if ( index == 0 )
		{
			temp_string.erase( temp_string.begin() );
		}
		else if ( index != std::string::npos )
		{
			temp_string.erase( temp_string.begin(), temp_string.begin() + index + 1 );
			count++;
		}
		else // Last word.
		{
			count++;
			break;
		}
	}
	return count;
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

const int countWords_optimized( const std::string& text )
{
	unsigned int count = 0, start = 0;
	bool inWord = false;
	for ( unsigned int i = 0; i < text.size(); i++ )
	{
		if ( !( inWord ) && /*( isalpha( text[i] ) || isdigit( text[i] ) )*/isWordCharacter( text[i] ) )
		{
			inWord = true;
			start = i;
		}
		else if ( ( inWord ) && /*( !isalpha( text[i] ) && !isdigit( text[i] ) )*/!isWordCharacter( text[i] ) )
		{
			inWord = false;
			count++;
		}
	}
	if ( inWord ) // Last word.
	{
		count++;
	}
	return count;
}

int main()
{
	std::string text = readFile( "text.txt" );
	std::cout << text << std::endl;
	std::cout << "The text has: " << countWords( text ) << " words." << std::endl;
	std::cout << "The text has: " << countWords_optimized( text ) << " words." << std::endl;
	std::cin.get();
	return 0;
}