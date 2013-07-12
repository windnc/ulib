#include "ulib.h"
using namespace ulib;

void Test1()
{
	CUStringDic dic;
	dic.Clear();

	if( dic.Binarize( "dic.sort", "dic" ) == false ) {
		fprintf( stderr, "fail\n" );
	}

}

int main()
{
	Test1();
}

// EOF ㅁ

