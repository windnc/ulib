#include "ulib.h"
using namespace ulib;

void Test1( CUStringList &slist )
{
	slist.PushBack ( "hello" );
	slist.PushBack ( "bye" );
	slist.Clear();
	slist.PushFront( "am" );
	slist.PushFront ( "I" );

	for( size_t i=0; i<(size_t)slist.GetSize(); i++ )		{
		CUString str;
		slist.GetAt(i, str );
		printf( "%s\n", str.GetStr() );
	}
}

void TestCreater()
{
	CUString str("hello my name is ");
	CUStringList strlist( str, " " );
	strlist.PopAt( 434, str );
	while(1)	{
		CUString word;
		if( !strlist.PopFront( word ) )	break;
		printf( "%s\n" , word.GetStr() );
	}
}

void Test2()
{
	CUString str("ass <bold>eee</bold> fff" );
	CUStringList list;
	list.TokenizeByStr( str, "" );

	for( size_t i=0; i<(size_t)list.GetSize(); i++ )	{
		CUString node;
		list.GetAt( i, node );
		fprintf( stderr, "%s\n", node.GetStr() );
	}
}


void Test3()
{
	CUString str( "hello <s>this</s> <s></s> <s>is</s> sample." );
	CUStringList list;
	list.TokenizeByBoundTag( str, "<s>", "</s>", true );
	list.RemoveBack();
	list.RemoveFront();
	list.RemoveFront();
	list.RemoveFront();
	list.Print( stdout );

	str= "aacaaabaabaabbaaabaaaaaaaaa";
	list.Clear();
	list.TokenizeByBoundTag( str, "a", "a", false );
	//list.PrintEx( stdout );
}

void Test4()
{
	CUStringList list1;
	list1.PushBack( "a" );
	list1.PushBack( "b" );
	list1.PushBack( "c" );
	list1.PushBack( "d" );

	CUStringList list2;
	list2.PushFront( "a" );
	list2.PushFront( "c" );
	
	CUStringList list3;
	list3.GetIntersection( list1, list2 );
	list3.Print( stdout );
}

int main()
{
	CUStringList slist;
	Test1( slist );
	TestCreater();
	Test2();
	
	Test3();
	Test4();
	return 0;
}

// EOF ㅁ
