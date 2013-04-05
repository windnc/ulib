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
		CUNode( int id, void *arg_data, short arg_data_size );
		~CUNode();

	public:
		bool SetData( void *arg_data, short arg_data_size );
		bool GetData( void *ret_data );
		void Clear();
		bool IsEmpty();
		void Verbose( int arg_verbose );

	public:
		void *data;
		short data_size;
		int verbose;
	};

}
#endif

// EOF ㅁ

