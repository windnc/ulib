/**
	@file		ustringnode.cpp
	@brief		ustringnode cpp
	@author		swlee
	@date		Apr. 5, 2013 ~
	@version	0.1
	@todo		
	@warning	
	@bug		
*/
#include "ustringnode.h"

namespace ulib {


	////////////////////////////////////////////////////////////
	CUStringNode::CUStringNode()
	{
	}
	

	////////////////////////////////////////////////////////////
	CUStringNode::~CUStringNode()
	{
	}


	////////////////////////////////////////////////////////////
	bool CUStringNode::SetData( CUString &arg_str )
	{
		return SetData( (char*)arg_str.GetStr() );
	}

	////////////////////////////////////////////////////////////
	bool CUStringNode::SetData( char *arg_str )
	{
		CUNode::SetData( arg_str, strlen(arg_str) );
		return true;
	}


	////////////////////////////////////////////////////////////
	char *CUStringNode::GetData()
	{
		if( data_size <= 0 )	return NULL;
		
		return (char*)data;
	} 


	////////////////////////////////////////////////////////////
	void CUStringNode::Print( FILE *fp = stdout )
	{
		fprintf( fp, "%s\n", GetData() );
	}

}

// EOF ㅁ

