#include "ulib.h"
using namespace ulib;


//////////////////////////////////////////////////////////
void test()
{
	CUTree tree;

	fprintf( stderr, "num node: %d\n", tree.GetNumNode() );

	CUTreeNode *root = tree.GetRootNode();
	CUTreeNode *child = tree.AddChildNode( root );
	child = tree.AddChildNode( root );
	child = tree.AddChildNode( root );
	child = tree.AddChildNode( root );
	child = tree.AddChildNode( child );
	child = tree.AddChildNode( child );
	child = tree.AddChildNode( child );
	child = tree.AddChildNode( child );
	child = tree.AddChildNode( root );

	CUString *str = new CUString( "string test" );
	fprintf( stderr, "%d [%s]\n", str, str->GetStr() );
	child->SetData( (void*)&str, sizeof( str ) );

	CUString *tmp;
	child->GetData( (void*)&tmp );
	fprintf( stderr, "%d [%s]\n", tmp, tmp->GetStr() );

	// bug?

	child = tree.AddChildNode( child );
	child = tree.AddChildNode( child );
	child = tree.AddChildNode( child );

	tree.Print( stderr, root, 0 );


}


//////////////////////////////////////////////////////////
int main()
{
	test();
	return 0;
}


// EOF ㅁ

