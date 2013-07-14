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
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include "ustring.h"
#include "ustringlistro.h"
#include "utextfile.h"

using namespace std;
namespace ulib {

	class CUStringDicEntry {
	public:
		CUString key;
		long start_addr;
		long end_addr;
	};

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
		bool LoadBinary( char *prefix );
		bool GetValue( char *str, CUString &result );
		bool SetValue( char *str, CUString &value );
	
	private:
		CUStringDicEntry* FindEntry( char *str );
		bool GetValueByAddr( long start, long end, CUString &result );
		bool SetValueByAddr( long start, long end, CUString &result );

	private:
		vector<CUStringDicEntry*> entry_vec;
		CUString prefix;
	};

}

#endif

