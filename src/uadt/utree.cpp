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
	CUTreeNode::CUTreeNode( void *arg_data, short arg_data_size )	
	{
		// init
		/*
		data = next = prev = NULL;	
		data_size = 0;
		
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
		*/
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

		int node_id = node_list.GetSize();
		CUTreeNode *root_node = new CUTreeNode( node_id );
		node_list.PushBack( (void*)&root_node, sizeof(root_node) );

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
		/*
		if(	head )	delete head;
		if( tail )	delete tail;
		*/

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


		/*
		CUListNode *tmp_node = head->next;
		while( tmp_node != tail )	{
			CUListNode *del_node = tmp_node;
			tmp_node = tmp_node->next;
			delete del_node;
		}

		head->next = tail;
		tail->prev = head;
		size = 0;
		*/

		if( verbose >= 1)	{
			printf( "CUTree Clear ... [OK]\n" ); fflush( stdout );
		}
	}


	////////////////////////////////////////////
	int CUTree::GetNumNode()
	{
		return node_list.GetSize();
	}
}

// EOF ㅁ


