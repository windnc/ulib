#include "ulib.h"
using namespace ulib;


//////////////////////////////////////////////////////////
void test()
{
	CUTree tree;

	fprintf( stderr, "num node: %d\n", tree.GetNumNode() );

	CUTreeNode *root = tree.GetRootNode();
	if( root != NULL )
	{
		fprintf( stderr, "ROOT [%d]\n", root->id );
	}



}


//////////////////////////////////////////////////////////
int main()
{
	test();
	return 0;
}


// EOF ㅁ
