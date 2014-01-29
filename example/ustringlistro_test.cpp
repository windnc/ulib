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

void Test1()
{
	CUString str( "hello my name is ... -_aa;df-we3_;" );
	CUString delim(" .-_;");
	CUStringListRO slist( str, delim );

	printf( "%d\n", (int)slist.GetSize() );
	for( long i=0; i<slist.GetSize(); i++ )	{
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
}

void Test2()
{
	CUStringListRO list( "hello world", " " );
	list.Print( stderr );
	fprintf( stderr, " %ld\n", list.GetSize() );

	CUStringListRO list2 = list;
	list2.Print( stderr );
	fprintf( stderr, " %ld\n", list2.GetSize() );

	CUStringListRO list3;
	list3 = list;
	list.Print( stderr );
	fprintf( stderr, " %ld\n", list3.GetSize() );
}

void Test3()
{
	vector<CUStringListRO> v;
	for( int i=0; i<10; i++ ) {
		CUStringListRO list( "hello world", " " );
		CUStringListRO list2;
		list2 = list;
		v.push_back( list );
		v.push_back( list2 );
	}
	fprintf( stderr, "%d\n", (int)v.size() );
}


void Test4()
{
	CUString str = "ABC DEF 123 1 2 3";
	CUStringListRO list( str, " " );

	str = "123 1 3 j dj sje sj e";
	CUStringListRO list2( str, " " );

	fprintf( stderr, "%d\n", list.Find( list2 ) );

}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();

	return 0;
}
