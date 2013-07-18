/**
	@file		ustringlistro.h
	@brief		ustringlistro header
	@author		이승욱
	@date		06.08.14
	@version	0.5
	@todo		string의 list 구조 구현 seperated by NULL
	@warning	???
	@bug		???
*/
#ifndef ___ustringlistro___
#define ___ustringlistro___

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ustring.h"
#include "ulist.h"


namespace ulib {

	////////////////////////////////////////////////////////////
	/**
		@class		CUStringListRO
		@brief		StringList 클래스, Null로 나누어져 있어 빠름.
		@date		06.08.14
		@author		이승욱
		@warning	???
		@bug		???
		@note		???
	*/
	////////////////////////////////////////////////////////////
	class CUStringListRO
	{
	public:
		CUStringListRO();
		CUStringListRO(const CUStringListRO &src );
		CUStringListRO& operator=(CUStringListRO &rhs );
		CUStringListRO( const CUString &str, const CUString &delimeter );
		~CUStringListRO();

	public:
		size_t GetSize();
		char *GetAt( int nPos );
		void MakeList( const CUString &arg_str, CUString delimeter );
		void Print( FILE *fp, char delimeter[] = "\n" );
		void Clear();
		int Find( CUStringListRO &list, int start=0 );

	public:
		CUString buf;
		CUString del;
		CUString str_org;
		int *pos;
		size_t size;
	};

}

#endif

