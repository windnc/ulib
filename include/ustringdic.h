/**
	@file		ustringdic.h
	@brief		ustringdic header
	@author		swlee
	@date		July. 11, 2013
	@version	0.1
	@todo		
	@warning	
	@bug		
*/
#ifndef ___ustringdic___
#define ___ustringdic___

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <string>
#include "ustring.h"
#include "ustringlistro.h"
#include "utextfile.h"

using namespace std;
namespace ulib {

	////////////////////////////////////////////////////////////
	/**
		@class		CUStringDic
		@brief		StringDic class
		@date		July. 11, 2013 ~
		@author		swlee
		@warning	???
		@bug		???
		@note		???
	*/
	////////////////////////////////////////////////////////////
	class CUStringDic {
	public:
		CUStringDic();
		~CUStringDic();

	public:
		void Clear();
		bool Binarize( char *fn, char *out_prefix );

	private:
//		CUStringDicNode* node_array;
//		CUStringDicNode* root;
		CUStringListRO key_list;
		CUStringListRO data_list;
	};

}

#endif

