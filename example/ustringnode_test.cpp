#include "ulib.h"
using namespace ulib;

void test()
{
	CUStringNode node;
	node.id = 32;

	node.SetData( "hello" );
	char *buf = node.GetData();
	fprintf( stderr, "%s\n", buf );

	CUString str = "bye";
	node.SetData( str );
	buf = node.GetData();
	fprintf( stderr, "%s\n", buf );

}


int main()
{
	test();
	return 0;
}


// EOF ㅁ

