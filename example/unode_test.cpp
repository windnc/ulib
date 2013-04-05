#include "ulib.h"
using namespace ulib;

void test()
{
	CUNode node(0);

	int cnt = 1024;
	node.SetData( (void*)&cnt, sizeof(cnt) );

	int cnt2;
	node.GetData( (void*)&cnt2  );

	fprintf( stderr, "%d\n", cnt2 );
}


int main()
{
	test();
	return 0;
}


// EOF ㅁ
