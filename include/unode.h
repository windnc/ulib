/**
	@file		unode.h
	@brief		uonde header
	@author		swlee
	@date		Apr. 5, 2013 ~
	@version	0.1
	@todo		
	@warning	
	@bug		
*/
#ifndef ___unode___
#define ___unode___

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

namespace ulib {


	////////////////////////////////////////////////////////////
	class CUNode
	{
	public:
		int id;
		CUNode( int id );
		~CUNode();

	public:
		void SetData( void *arg_data, short arg_data_size );
		void *GetData();

	public:
		void *data;
		short data_size;
	};

}
#endif

// EOF ㅁ

