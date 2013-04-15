#include "ulib.h"
using namespace ulib;

void Test1()
{
	CUStringTree str_tree;
	str_tree.Clear();

	CUStringTreeNode *root = str_tree.GetRootNode();
	if( root == NULL )	{
		fprintf( stderr, "fail to get root\n" );
		return;
	}

	CUStringTreeNode *child1 = str_tree.AddChildNode( root );
	child1->SetData( "Animal" );

	CUStringTreeNode *child1A = str_tree.AddChildNode( child1 );
	child1A->SetData( "Cat" );

	CUStringTreeNode *child1B = str_tree.AddChildNode( child1 );
	child1B->SetData( "Dog" );

	CUStringTreeNode *child1B1 = str_tree.AddChildNode( child1B );
	child1B1->SetData( "Bull-dog" );

	CUStringTreeNode *child1B2 = str_tree.AddChildNode( child1B );
	child1B2->SetData( "Dachshund" );

	CUStringTreeNode *child1C = str_tree.AddChildNode( child1 );
	child1C->SetData( "Monkey" );


	CUStringTreeNode *child2 = str_tree.AddChildNode( root );
	child2->SetData( "Sports" );

	CUStringTreeNode *child2A = str_tree.AddChildNode( child2 );
	child2A->SetData( "Soccer" );

	CUStringTreeNode *child2B = str_tree.AddChildNode( child2 );
	child2B->SetData( "Baseball" );

	CUStringTreeNode *child2C = str_tree.AddChildNode( child2 );
	child2C->SetData( "Swimming" );

	str_tree.Print( stdout, root );

}

int main()
{
	Test1();
}

// EOF ㅁ

