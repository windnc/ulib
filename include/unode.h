/**
	@file		unode.h
	@brief		unode header
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
		CUNode();
		~CUNode();

	public:
		bool SetData( void *arg_data, short arg_data_size );
		bool GetData( void *ret_data );
		void Clear();
		bool IsEmpty();
		void Verbose( int arg_verbose );

	public:
		int id;
		void *data;
		size_t data_size;

	private:
		int verbose;
	};

}
#endif

// EOF ㅁ

