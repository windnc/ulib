#include "ulib.h"
using namespace ulib;

void Test1()
{
	CUStringDic dic;
	dic.Clear();

	if( dic.Binarize( "tiny.txt", "dic" ) == false ) {
		fprintf( stderr, "fail\n" );
	}

}

void Test2()
{
	CUStringDic dic;
	char *prefix = "dic";
	if( dic.LoadBinary( prefix ) == false ) {
		fprintf( stderr, "fail to load\n" );
	}

	//char *str = "whale/NN";
	char *str = "6.25744/CD";
	//char *str = "흙/NNG";
	//char *str = "달러/NNB";
	CUString result;
	if( dic.GetValue( str, result ) == true ) {
		fprintf( stderr, "%s\n%s\n", str, result.GetStr() );
	}
	else {
		fprintf( stderr, "fail to get value: %s\n", str );
	}

}

int main()
{
	Test1();
	Test2();
}

// EOF ㅁ

