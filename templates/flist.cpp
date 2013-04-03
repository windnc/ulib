#include "ulib.h"
using namespace ulib;
static CUProgress progress;

/////////////////////////////////////////////////////////////////////////////////
bool func2( CUString &content )
{
	fprintf( stderr, "%d bytes\n", content.GetLength() );
	return true;
}


/////////////////////////////////////////////////////////////////////////////////
bool func1( char list_filename[] )
{
	CUFlistFile file( list_filename );
	if( file.CheckOpen() == false )	{
		return false;
	}
	if( file.CheckList( false ) == false )	{	
		return false;
	}

	progress.SetMaxCount( file.GetNumFile() );
	progress.Begin();
	for( int i=0; i<file.GetNumFile(); i++ )	{
		progress.PrintPercent( stderr, i+1, "" );

		CUString content;
		if( file.GetFileContent( i, content ) == false )	{
			return false;
		}

		func2( content );
	}
	progress.End();
	progress.PrintElapsedTime( stderr );

	return true;	
}


/////////////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
	if( argc < 2 )	{
		fprintf( stderr, "usage: flist flist\n" );
		return 1;
	}
	
	if( func1( argv[1] ) == false )	{
		return 1;
	}

	return 0;
}

// EOF ㅁ
