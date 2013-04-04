#ifndef ___uoption___
#define ___uoption___

#include "ulib.h"
#include <map>
#include <string>
using namespace std;

namespace ulib {

	/**
		@file		uoption.h
		@brief		uoption header
		@author		swlee
		@date		Apr. 3, 2013
		@version	0.0.1
		@todo		
		@warning	
		@bug		
		@note		Release 0.1
	*/
	class CUOption {
	public:
		CUOption();
		bool Load( int argc, char *argv[] );
		void Print( FILE *fp );
		bool GetValue( CUString &key, CUString &value );

		map<string, string> option_map;
		CUConfigFile conf_file;
	};
}

#endif

// EOF ㅁ

