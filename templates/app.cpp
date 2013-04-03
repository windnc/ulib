#include "ulib.h"
using namespace ulib;


////////////////////////////////////////////////////////////////
class CTest {
public:
	bool Load( int argc, char *argv[] )
	{
		option.Load( argc, argv );
	}

	bool Start()
	{
		CUString key = "mode";
		CUString value;

		if( option.GetValue( key, value ) == false )	{
			return false;
		}

		fprintf( stderr, "Start model %s\n", value.GetStr() );
		// code here

		return true;
	}

private:
	CUOption option;
};


////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
	CTest test;
	if( test.Load( argc, argv ) == false )
	{
		fprintf( stderr, "ERROR: fail to load option\n" );
		return 1;
	}

	if( test.Start() == false )	return 1;

	return 0;
}

// EOF ㅁ

