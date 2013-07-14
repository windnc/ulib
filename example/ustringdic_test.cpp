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
	CUStringDicEntry *entry = NULL;
	if( dic.GetValue( str, result ) == true ) {
		fprintf( stderr, "%s\n%s\n", str, result.GetStr() );
	}
	else {
		fprintf( stderr, "fail to get value: %s\n", str );
	}

}

void Test3()
{
	CUStringDic dic;
	char *prefix = "dic";
	if( dic.LoadBinary( prefix ) == false ) {
		fprintf( stderr, "fail to load\n" );
	}

	char *str = "도/JX";
	CUString value = "hello too long";
	if( dic.SetValue( str, value ) == true ) {
		fprintf( stderr, "%s\n%s\n", str, value.GetStr() );
	}
	else {
		fprintf( stderr, "fail to set value: %s\n", str );
	}

}

int main()
{
	Test1();
	Test2();
	Test3();
}

// EOF ㅁ

