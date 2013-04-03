#include "ulib.h"
using namespace ulib;


int main( int argc, char *argv[] )
{
	CUOption option;
	if( option.Load( argc, argv ) == true )
	{
		option.Print( stderr );
		CUString key = "-mode";
		CUString val;

		if( option.GetValue( key, val ) == true ) {
			fprintf( stderr, "The value of [%s] is [%s]\n", key.GetStr(), val.GetStr() );
		}
		else {
			fprintf( stderr, "Fail to get value of %s option\n", key.GetStr() );
		}


		key = "option3";
		if( option.GetValue( key, val ) == true ) {
			fprintf( stderr, "The value of [%s] is [%s]\n", key.GetStr(), val.GetStr() );
		}
		else {
			fprintf( stderr, "Fail to get value of %s option\n", key.GetStr() );
		}
	}


	return 0;
}

// EOF ㅁ

