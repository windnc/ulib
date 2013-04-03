#include "ulib.h"
using namespace ulib;
static CUProgress progress;


//////////////////////////////////////////////////////////////////////
bool func2( CUString &str )
{
	return true;
}


//////////////////////////////////////////////////////////////////////
bool func1( char filename[] )
{
	CUTextFile file( filename, "r" );
	if( file.IsOpen() )	{
		fprintf( stderr, "file opened\n" );
	}
	else	{
		fprintf( stderr, "file open fail\n" );
		return false;
	}

	progress.Begin();

	CUString str;
	file.LoadToStr( str );
	
	func2( str );

	progress.End();
	progress.PrintElapsedTime( stderr );
	return true;
}


//////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
	if( argc < 2 )	{
		fprintf( stderr, "usage: txtfilemem file\n" );
		return 1;
	}

	if( func1( argv[1] ) == false )	{
		return 1;
	}

	return 0;
}

// EOF ㅁ
