/**
	@file		unode.cpp
	@brief		unode cpp
	@author		swlee
	@date		Apr. 5, 2013 ~
	@version	0.1
	@todo		
	@warning	
	@bug		
*/
#include "unode.h"

namespace ulib {

	////////////////////////////////////////////////////////////
	CUNode::CUNode()
	{
		data = NULL;
		data_size = 0;
	}

	
	////////////////////////////////////////////////////////////
	CUNode::~CUNode()
	{
		// dealloc
		if( data )	free(data);
	} 


	////////////////////////////////////////////////////////////
	bool CUNode::SetData( void *arg_data, short arg_data_size )
	{
		if( arg_data_size  <= 0 )	return false;

		if( !(data = malloc( arg_data_size ) ) )	return false;
		
		if( !memcpy( data, arg_data, arg_data_size ) )	{
			free(data);
			data = NULL; 
			return false;
		}

		data_size = arg_data_size;
		return true;
	} 


	////////////////////////////////////////////////////////////
	bool CUNode::GetData( void *ret_data )
	{
		if( data_size <= 0 )	return false;

		memcpy( ret_data, data, data_size );
		
		return true;
	} 


	////////////////////////////////////////////////////////////
	void CUNode::Verbose( int arg_verbose )
	{
		verbose = arg_verbose;
	}


	////////////////////////////////////////////////////////////
	bool CUNode::IsEmpty()
	{
		if( data_size <= 0 )	return true;
		return false;
	}


	////////////////////////////////////////////////////////////
	void CUNode::Clear()
	{
		if( data ) free(data);
		data = NULL; 
	}

}

// EOF ㅁ

