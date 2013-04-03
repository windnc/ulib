#include "uprogress.h"
using namespace ulib;

void test_stamp()
{
	printf( ">>>>>>>>> stamp\n" );

	CUProgress prog;
	prog.Begin();

	//////////////////
	unsigned long v = 0;
	for( int i=0; i<100000; i++ )	{
		for( int j=0; j<3000; j++ )	{
			int tmp = i*j;
			v *= tmp;
		}
	}
	printf( "v: %lu\n", v );
	//////////////////

	prog.End();
	printf( "%1.4f sec\n", prog.GetElapsedSec() );

	printf( "\n" );
}

void test_progress()
{
	printf( ">>>>>>>>> stamp\n" );

	CUProgress prog;


	int max_cnt = 30;
	prog.SetMaxCount( max_cnt );
	for( int i=0; i<max_cnt; i++ )	{
	//	float percent = prog.GetPercent( i );
//		fprintf( stderr, "%1.2f%%\n", percent );
		prog.PrintPercent( stderr, i+1 );
	}


	printf( "\n" );
}

int main()
{
	test_stamp();
	test_progress();
	return 0;
}

// EOF ㅁ
