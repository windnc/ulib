/**
	@file		ustringtree.cpp
	@brief		ustringtree cpp
	@author		swlee
	@date		Apr. 15, 2013 ~
	@version	0.1
	@todo		
	@warning	
	@bug		
*/
#include "ustringtree.h"

namespace ulib
{


	////////////////////////////////////////////////////////////
	CUStringTreeNode::CUStringTreeNode()
	{
	}

	////////////////////////////////////////////////////////////
	void CUStringTreeNode::AddChild( CUStringTreeNode *child )
	{
		child_list.PushBack( (void*)&child, sizeof(child) );
	}


	////////////////////////////////////////////////////////////
	CUStringTreeNode* CUStringTreeNode::GetChild( int idx )
	{
		CUStringTreeNode *node;
		if( child_list.GetAt(idx, (void*)&node ) == false ) {
			return NULL;
		}
		else {
			return node;
		}
	}


	////////////////////////////////////////////////////////////
	void CUStringTreeNode::Print( FILE *fp = stderr )
	{
		for( int i=0; i<depth; i++ ) {
			fprintf( fp, "    " );
		}

		fprintf( fp, "%s\n", (char*)data);
	}

	////////////////////////////////////////////////////////////
	void CUStringTreeNode::SetData( char* str )
	{
		CUNode::SetData( str, strlen( str ) );
	}


	////////////////////////////////////////////////////////////
	void CUStringTreeNode::SetData( CUString str )
	{
		CUNode::SetData( str.GetStr(), str.GetLength() );
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	생성자
	*/
	////////////////////////////////////////////////////////////
	CUStringTree::CUStringTree()
	{
	}



	////////////////////////////////////////////////////////////
	/**
		@brief	소멸자
	*/
	////////////////////////////////////////////////////////////
	CUStringTree::~CUStringTree()
	{
		Clear();
	} 


	////////////////////////////////////////////////////////////
	void CUStringTree::Clear()
	{
	}


	////////////////////////////////////////////////////////////
	void CUStringTree::Print( FILE *fp = stderr, CUStringTreeNode *root = NULL )
	{
		if( root == NULL )	root = GetRootNode();

		root->Print( fp );
		for( int i=0; i<root->GetNumChild(); i++ )
		{
			Print( fp, root->GetChild(i) );
		}
	}


	////////////////////////////////////////////////////////////
	CUStringTreeNode* CUStringTree::GetRootNode()
	{
		CUStringTreeNode *node = NULL;
		if( node_list.GetSize() == 0 )	{
			node = AllocateNode();
			node->SetData( "ROOT" );
		}
		else {
			node_list.GetAt(0, (void*)&node );
		}
		return node;
	}

	CUStringTreeNode* CUStringTree::AllocateNode()
	{
		int node_id = node_list.GetSize();
		CUStringTreeNode *node = new CUStringTreeNode();
		node->id = node_id;
		node_list.PushBack( (void*)&node, sizeof(node) );

		return node;
	}


	////////////////////////////////////////////////////////////
	CUStringTreeNode * CUStringTree::AddChildNode( CUStringTreeNode *parent )
	{
		CUStringTreeNode *node = AllocateNode();
		node->depth = parent->depth+1;
		node->parent = parent;
		parent->AddChild( node );

		return node;
	}


}

// EOF ㅁ

