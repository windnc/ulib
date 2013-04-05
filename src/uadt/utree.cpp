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
	CUTreeNode::CUTreeNode( int id )
	{
		this->id = id;
	}

	////////////////////////////////////////////////////////////
	void CUTreeNode::SetData( void *arg_data, short arg_data_size )	
	{
		// check
		if( arg_data_size  <= 0 )	return;


		// alloc
		if( !(data = malloc( arg_data_size ) ) )	return;
		
		// set
		if( !memcpy( data, arg_data, arg_data_size ) )	{
			free(data);
			data = NULL; 
			return;
		}
		data_size = arg_data_size;
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
	CUTreeNode::~CUTreeNode()
	{
		// dealloc
		if( data )	free(data);
	} 

	////////////////////////////////////////////////////////////
	void *CUTreeNode::GetData()
	{
		if( data == NULL )	return NULL;
		else				return data;
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
		CUTreeNode *node = new CUTreeNode( node_id );
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


