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


	CUJsonParser json;
	if( json.Load( str ) == false )
	{
		fprintf( stderr, "fail to load json\n" );
		return;
	}
	json.Print( stdout );

	CUJsonTreeNode *root = json.GetRootNode();
	if( root == NULL )	{
		fprintf( stderr, "fail to get root\n" );
		return;
	}

	CUJsonTreeNode *text_node = root->Find( "text" );
	if( text_node == NULL )	{
		fprintf( stderr, "fail to find text\n" );
		return;
	}
	else {
		fprintf( stderr, "text: %s\n", text_node->value_str.GetStr() );
	}




}


int main()
{
	func1();
}

// EOF ㅁ

