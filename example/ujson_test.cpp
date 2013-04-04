#include "ulib.h"
using namespace ulib;

void func1()
{

	CUTextFile file( "ujson_test.json","r");
	CUString str;
	if( file.LoadToStr( str ) == false )
	{
		fprintf( stderr, "fail to open json file\n" );
		return;
	}


	CUJson json;
	if( json.Load( str ) == false )
	{
		fprintf( stderr, "fail to load json\n" );
		return;
	}

	/*
	CUString str;
	json.ToString( json );
	fprintf( stderr, "%s\n", json.GetStr() );
	*/

}


int main()
{
	func1();
}

// EOF ㅁ

