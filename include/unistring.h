/**
	@file		unistring.h
	@brief		unistring header
	@author		swlee
	@date		Apr. 19, 2013 ~
	@version	0.1
	@todo		
	@warning	
	@bug		
	@note		
*/
#ifndef ___unistring___
#define ___unistring___

#include "ustring.h"
#include "ustringlist.h"

namespace ulib
{

	/**
		@class		CUniString
		@brief		Unicode String class
		@date		Apr. 19, 2013
		@author		swlee
		@warning	
		@todo		
		@bug		
		@note		only support utf-8
	*/

	class CUniString : public CUString {
	public:
		CUniString();
		~CUniString();

		CUniString( char* arg_str, char *enc );

	public:
		int GetNumUniChar();
		void Print( FILE *fp );

	private:
		bool TokenizeAscii();
		bool TokenizeAsciiEscapedUnicode();
		bool TokenizeEuckr();

	private:
		bool tokenized;
		CUString enc;
		CUStringList unichar_list;
	};

}

#endif
// EOF ㅁ

