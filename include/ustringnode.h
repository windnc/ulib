/**
	@file		ustringnode.h
	@brief		ustring header
	@author		swlee
	@date		Apr. 5, 2013 ~
	@version	0.1
	@todo		
	@warning	
	@bug		
*/
#ifndef ___ustringnode___
#define ___ustringnode___

#include "unode.h"
#include "ustring.h"

namespace ulib {


	////////////////////////////////////////////////////////////
	class CUStringNode : public CUNode
	{
	public:
		CUStringNode();
		~CUStringNode();

		bool SetData( char *arg_str );
		bool SetData( CUString &arg_str );
		char *GetData();
	};

}
#endif

// EOF ㅁ

