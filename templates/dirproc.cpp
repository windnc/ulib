#include "ulib.h"
using namespace ulib;
static CUProgress progress;


/////////////////////////////////////////////////////////////////////////////////
bool func2( char filename[] )
{
	fprintf( stderr, "file open [%s]... ", filename );
	CUTextFile file( filename, "r" );
	if( file.IsOpen() == false  )	{
		fprintf( stderr, "[fail]\n" );		
		return false;
	}

	int num_line = file.GetNumLine();
	file.MoveToStart();
	int now_line = 1;
	while(1)	{
		CUString line;
		if( file.ReadLine( line ) == false )	break;
		line.Replace("\r", "" );

		// ADD CODE HERE

		now_line++;
	}

	fprintf( stderr, "%d bytes\n", file.GetFileSize() );

	return true;
}


/////////////////////////////////////////////////////////////////////////////////
bool func1( char dirname[] )
{
	progress.Begin();

	CUDir dir;
	dir.OpenDir( dirname );
	if( dir.IsOpen() == false ) return false;

	int now_file=0;
	while(1)	{
		CUString filename;
		if( dir.ReadFile( filename ) == false )	break;

		filename = CUString(dirname)+CUString("/")+filename;
		filename.TrimRight("/");
		filename.Replace("//", "/");

		func2( filename.GetStr() );
		now_file++;
	}
	fprintf( stderr, "%d files\n", now_file );

	progress.End();
	progress.PrintElapsedTime( stderr );

	return true;	
}


/////////////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
	if( argc < 2 )	{
		fprintf( stderr, "usage: dirproc dir\n" );
		return 1;
	}

	if( func1( argv[1] ) == false )	{
		return 1;
	}

	return 0;
}

// EOF ㅁ