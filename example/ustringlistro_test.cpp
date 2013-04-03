#include "ulib.h"
using namespace ulib;

// ㅁ
/*
void Test1( CUStringList &slist )
{
	slist.PushBack ( "hello" );
	slist.PushBack ( "bye" );
	slist.Clear();
	slist.PushFront( "am" );
	slist.PushFront ( "I" );

	for( int i=0; i<slist.GetSize(); i++ )		{
		CUString str;
		slist.GetAt(i, str );
		printf( "%s\n", str.GetStr() );
	}
}

void TestCreater()
{
	CUString str("hello my name is uki.");
	CUStringList strlist( str, " " );
strlist.PopAt( 434, str );
	while(1)	{
		CUString word;
		if( !strlist.PopFront( word ) )	break;
		printf( "%s\n" , word.GetStr() );
	}
}
*/

int main()
{
	CUString str( "hello my name is ... -_aa;df-we3_;" );
	CUString delim(" .-_;");
	CUStringListRO slist( str, delim );

	printf( "%d\n", (int)slist.GetSize() );
	for( size_t i=0; i<slist.GetSize(); i++ )	{
		char *ptr = slist.GetAt(i );
		
		printf( "%s\n", ptr );
	}

	printf( "%s\n", str.GetStr() );
	printf( "%s\n", delim.GetStr() );
	CUStringList slist2( str, delim );
	while(1)	{
		CUString tmp;
		if( !slist2.PopFront( tmp) )	break;
		printf("%s\n", tmp.GetStr() );
	}
	return 0;
}
