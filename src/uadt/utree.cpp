/**
	@file		utree.cpp
	@brief		utree cpp
	@author		swlee
	@date		Apr. 5, 2013 ~
	@version	0.1
	@todo		
	@warning	
	@bug		
*/
#include "utree.h"

namespace ulib {


	////////////////////////////////////////////////////////////
	CUTreeNode::CUTreeNode()
	{
	}


	////////////////////////////////////////////////////////////
	CUTreeNode::~CUTreeNode()
	{
	} 


	////////////////////////////////////////////////////////////
	void CUTreeNode::AddChild( CUTreeNode *child )
	{
		child_list.PushBack( (void*)&child, sizeof(child) );
	}

	////////////////////////////////////////////////////////////
	CUTreeNode *CUTreeNode::GetChild( int idx )
	{
		CUTreeNode *node;
		if( child_list.GetAt( idx, (void*)&node ) == false ) {
			return NULL;
		}
		else {
			return node;
		}

	}


	////////////////////////////////////////////////////////////
	CUTree::CUTree( int arg_verbose )
	{
		Verbose( arg_verbose );
		if( verbose >= 1)	{
			printf( "CUTree Create ... \n" ); fflush( stdout );
		}

		// root
		AllocateNode();


		if( verbose >= 1)	{
			printf( "CUTree Create ... [OK]\n" ); fflush( stdout );
		}
	}


	////////////////////////////////////////////////////////////
	CUTree::~CUTree()
	{
		if( verbose >= 1)	{
			printf( "CUTree Release ... \n" ); fflush( stdout );
		}

		Clear();

		if( verbose >= 1)	{
			printf( "CUTree Release ... [OK]\n" ); fflush( stdout );
		}
		
	}


	////////////////////////////////////////////////////////////
	CUTreeNode * CUTree::GetRootNode()
	{
		CUTreeNode *node;
		if( node_list.GetAt(0, (void*)&node) == false ) {
			return NULL;
		}
		else {
			return node;
		}
	}


	////////////////////////////////////////////////////////////
	CUTreeNode * CUTree::AddChildNode( CUTreeNode *parent )
	{
		CUTreeNode *node = AllocateNode();
		node->parent = parent;
		parent->AddChild( node );

		return node;
	}


	////////////////////////////////////////////////////////////
	CUTreeNode* CUTree::AllocateNode()
	{
		int node_id = node_list.GetSize();
		CUTreeNode *node = new CUTreeNode();
		node->id = node_id;
		node_list.PushBack( (void*)&node, sizeof(node) );

		return node;
	}


	////////////////////////////////////////////////////////////
	void CUTree::Verbose( int arg_verbose )
	{
		verbose = arg_verbose;
	}


	////////////////////////////////////////////////////////////
	bool CUTree::IsEmpty()
	{
		return node_list.GetSize() == 0;
	}



	////////////////////////////////////////////
	void CUTree::Clear()	
	{
		if( verbose >= 1)	{
			printf( "CUTree Clear ... \n" ); fflush( stdout );
		}

		while( node_list.GetSize() > 0 ) {
			CUTreeNode *node;
			if( node_list.PopFront( (void*)&node ) )
			{
				delete node;
			}

		}

		if( verbose >= 1)	{
			printf( "CUTree Clear ... [OK]\n" ); fflush( stdout );
		}
	}


	////////////////////////////////////////////
	void CUTree::Print( FILE *fp )
	{
		return Print( fp, GetRootNode(), 0 );
	}

	////////////////////////////////////////////
	void CUTree::Print( FILE *fp, CUTreeNode *node = NULL, int level = -1 )
	{
		if( node == NULL ) node = GetRootNode();
		if( level == -1 ) level = 0;

		for( int j=0; j<level; j++ ) {
			fprintf( fp, " " );
		}
		fprintf( fp, "%d\n", node->id );
		for( int i=0; i<node->child_list.GetSize(); i++ )
		{
			CUTreeNode *child = node->GetChild( i );
			Print( fp, child, level+1 );
		}
	}


	////////////////////////////////////////////
	int CUTree::GetNumNode()
	{
		return node_list.GetSize();
	}
}

// EOF ㅁ


