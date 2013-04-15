/**
	@file		ustringtree.h
	@brief		ustringtree header
	@author		swlee
	@date		Apr. 15, 2013
	@version	0.1
	@todo		
	@warning	
	@bug		
*/
#ifndef ___ustringtree___
#define ___ustringtree___

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ustring.h"
#include "utree.h"

#define DELIMETER_CHARS   " #$%@*\n\t\"'-+=!?,./%<>()[]{}:;|"


namespace ulib {

	////////////////////////////////////////////////////////////
	/**
		@class		CUStringTree
		@brief		StringTree class
		@date		Apr 15, 2013 ~
		@author		swlee
		@warning	???
		@bug		???
		@note		???
	*/
	////////////////////////////////////////////////////////////
	class CUStringTree: public CUTree
	{
	public:
		CUStringTree();
		~CUStringTree();

	public:
		void Clear();

	};

}

#endif

