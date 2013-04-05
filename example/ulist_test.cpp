#include "ulib.h"
using namespace ulib;


//////////////////////////////////////////////////////////
void test()
{
	CUList list;

	int a=10;
	char b = 'j';
	CUString *str = new CUString("hello");

	list.PushBack( (void*)&a, sizeof(a) );
	list.PushBack( (void*)&b, sizeof(b) );
	list.PushBack( (void*)&str, sizeof(str) );

	int a2;
	list.PopFront( (void*)&a2 );
	fprintf( stderr, "%d\n", a2 );

	char b2;
	list.PopFront( (void*)&b2 );
	fprintf( stderr, "%c\n", b2 );

	CUString *str2;
	list.PopFront( (void*)&str2 );
	fprintf( stderr, "%s\n", str2->GetStr() );


}


//////////////////////////////////////////////////////////
int main()
{
	test();
	return 0;
}


// EOF ㅁ

