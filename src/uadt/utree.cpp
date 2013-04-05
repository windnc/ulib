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

		/*
		head = new CUListNode( (void*)"head", strlen("head")+1 );	
		tail = new CUListNode( (void*)"tail", strlen("tail")+1 );
		head->prev = NULL;
		head->next = tail;
		tail->prev = head;
		tail->next = NULL;
		cur_node = head;
		size = 0;	
		*/

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
	void CUTree::Verbose( int arg_verbose )
	{
		verbose = arg_verbose;
	}


	////////////////////////////////////////////////////////////
	bool CUTree::IsEmpty()
	{
		if( size <= 0 )	return true;
		return false;
	}



	////////////////////////////////////////////
	void CUTree::Clear()	
	{
		if( verbose >= 1)	{
			printf( "CUTree Clear ... \n" ); fflush( stdout );
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
	long CUTree::GetSize()
	{
		return size;
	}
}

// EOF ㅁ


