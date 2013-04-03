#include "ulib.h"
using namespace ulib;
static CUProgress progress;

/////////////////////////////////////////////////////
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

	int num_line = file.GetNumLine();
	file.MoveToStart();
	progress.SetMaxCount( num_line );
	int now_line = 0;

	CUTextFile file2( "out.txt", "w" );
	CUString str;
	progress.Begin();
	while(1)	{
		CUString line;
		if( file.ReadLine( line ) == false )	break;
		line.Replace("\r", "" );
		now_line++;

		if( line.GetAt( line.GetLength() -1 ) == '.' )	{
			file2.WriteLine( line.Left( line.GetLength() -1 ) + CUString(" .") );
		}
		else	{
			file2.WriteLine( line );
		}

		//progress.PrintPercent( stderr, now_line );
		// ADD CODE HERE
	}

	file2.WriteLine( str );

	progress.End();
	progress.PrintElapsedTime( stderr );

	return true;	
}


///////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
	if( argc < 2 )	{
		fprintf( stderr, "usage: txtfile file\n" );
		return 1;
	}

	if( func1( argv[1] ) == false )	{
		return 1;
	}

	return 0;
}

// EOF ㅁ
