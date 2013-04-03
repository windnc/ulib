#include "ulib.h"
using namespace ulib;
CUProgress progress;


/////////////////////////////////////////////////////////////////
bool check_conf( CUConfig &conf )
{
	CUString str;

	if( conf.HaveValue( "flist" ) == false )    {
		fprintf( stderr, "cannot find field: flist\n" );
		return false;
	}

	return true;
}


/////////////////////////////////////////////////////////////////
void create_sample()
{
	CUTextFile file( "sample.conf", "w" );
	fprintf( file.GetFP(), "#리스트 파일(한라인이 한 파일명)\n" );
	fprintf( file.GetFP(), "flist = test.flist\n" );
	fprintf( file.GetFP(), "\n" );
}


/////////////////////////////////////////////////////////////////
bool func1( CUConfig &conf )
{
	CUString flist;
	conf.GetValue( "flist", flist );

	progress.Begin();
	CUTextFile list_file( flist );
	if( list_file.CheckOpen() == false )	return false;
	int now_line = 0;
	int num_line = list_file.GetNumLine();
	list_file.MoveToStart();
	progress.SetMaxCount( num_line );

	while(1)	{
		CUString filename;
		if( list_file.ReadLine( filename ) == false )	break;
		now_line++;

		progress.PrintPercent( stderr, now_line, "\n" );
	}
	progress.End();
	progress.PrintElapsedTime( stderr );
	
	return true;
}


/////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
	if( argc !=2  )	{
		fprintf( stderr, "usage: confproc sample.conf\n" );
		fprintf( stderr, "usage: confproc -t\n" );
		return 1;
	}

	if( argv[1][0] == '-' && argv[1][1] =='t' )	{
		create_sample();
		return 0;
	}

	CUConfig conf;
	conf.Load( argv[1] );
	if( conf.IsLoad() == false )	{
		fprintf( stderr, "cannot read conf file %s\n", argv[1] );
		return 1;
	}

	if( check_conf( conf ) == false )	{
		return 1;
	}

	if( func1( conf ) == false )	{
		return 1;
	}

	return 0;
}

// EOF ㅁ
