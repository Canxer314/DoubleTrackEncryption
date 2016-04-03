//Double-track encryption/decryption program
//This program allows the user to encrypt/decryption his text file
//with an way so called "Double-track encrypting/decryption"
//Usage: Call the program with an option which you want the program
//to perform and with a name of the text file which
//you want to encrypt/decryption seperated by an blank.
//Such as doubleTrack.exe -e doubleTrack.txt
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cctype>
using namespace std;

int encryption( char *fileName );
int decryption( char *fileName );

int main( int argc, char *argv[] )
{
    try
    {
        if ( argc > 3 )
            throw -1;
    }
    catch ( int x )
    {
        cout << "Error: the number of the argument provided to the program more than two." << endl;
        return -1;
    }
    char *nameOfFile = argv[ 2 ];
    //cout << argv[ 1 ] << endl;
    if ( strcmp( argv[ 1 ], "-e" ) == 0 || strcmp( argv[ 1 ], "--encrypt") == 0 )
    {
        encryption( nameOfFile );
    }
    else if ( strcmp( argv[ 1 ], "-d" ) == 0 || strcmp( argv[ 1 ], "--decrypt" ) == 0 )
        {
            decryption( nameOfFile );
        }
        else if ( strcmp( argv[ 1 ], "-h" ) == 0 || strcmp( argv[ 1 ], "--help" ) == 0 )
            {
                cout << "Usage: [-option] [fileName]" << endl;
                cout << "option:" << endl;
                cout << "-e --encrypt     : encryption" << endl;
                cout << "-d --decrypt     : decryption" << endl;
                cout << "-h --help        : see for help" << endl;
                return 1;
            }
            else
            {
                cout << "Incorrect option.Please input \"-h\" for help." << endl;
                return -2;
            }
    return 0;
}

int encryption( char * fileName )
{
    string tmpString;
    string outputString;
    string oddString;
    string evenString;
    size_t sizeOfString;
    size_t oddStringLocation = 0;
    size_t evenStringLocation = 0;
    ifstream inputFile( fileName, ios::in );
    strcat( fileName, ".encrypted");
    ofstream outputFile( fileName, ios::out | ios::trunc );
    try
    {
        if ( !inputFile.is_open() )
        {
            throw -2;
        }
    }
    catch ( int x )
    {
        string tmp = fileName;
        cout << "Can not open the file" << tmp << endl;
    }
    while ( inputFile >> tmpString )//reading context from inputFile to string tmpString
        outputString += tmpString;
    tmpString = outputString;
    sizeOfString = tmpString.size();
    for ( size_t tmpStringLocation = 0; tmpStringLocation < sizeOfString; tmpStringLocation++ )
    {
        if ( ( tmpStringLocation % 2 ) == 0 )
        {
            oddString += " ";
            oddString.at( oddStringLocation++ ) = tolower( tmpString.at( tmpStringLocation ) );
        }
        else
        {
            evenString += " ";
            evenString.at( evenStringLocation++ ) = tolower( tmpString.at( tmpStringLocation ) );
        }
    }
    oddString.at( 0 ) = toupper( oddString.at( 0 ) );
    evenString.at( 0 ) = toupper( evenString.at( 0 ) );
    outputString = oddString + " " + evenString;
    outputFile << outputString;
    inputFile.close();
    outputFile.close();
    return 0;
}

int decryption( char *fileName )
{
    string outputString;
    string oddString;
    string evenString;
    size_t sizeOfString;
    size_t oddStringLocation = 0;
    size_t evenStringLocation = 0;
    ifstream inputFile( fileName, ios::in );
    strcat( fileName, ".decrypted");
    ofstream outputFile( fileName, ios::out | ios::trunc );
    try
    {
        if ( !inputFile.is_open() )
        {
            throw -3;
        }
    }
    catch ( int x )
    {
        string tmp = fileName;
        cout << "Can not open the file " << tmp << endl;
    }
    inputFile >> oddString;
    inputFile >> evenString;
    oddString.at( 0 ) = tolower( oddString.at( 0 ) );
    evenString.at( 0 ) = tolower( evenString.at( 0 ) );
    sizeOfString = oddString.size() + evenString.size();
    for ( int subscript = 0; subscript < sizeOfString; subscript++)
    {
        if ( subscript % 2 == 0 )
        {
            outputString += " ";
            outputString.at( subscript ) = oddString.at( oddStringLocation++ );
        }
        else
        {
            outputString += " ";
            outputString.at( subscript ) = evenString.at( evenStringLocation++ );
        }
    }
    outputFile << outputString;
    inputFile.close();
    outputFile.close();
    return 0;
}
