/**
	@file		ustringlist.h
	@brief		ustringlist header
	@author		이승욱
	@date		08.05.06
	@version	0.6
	@todo		string의 list 구조 구현
	@warning	???
	@bug		???
*/
#ifndef ___ustringlist___
#define ___ustringlist___

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ustring.h"
#include "ulist.h"

#define DELIMETER_CHARS   " #$%@*\n\t\"'-+=!?,./%<>()[]{}:;|"


namespace ulib {

	////////////////////////////////////////////////////////////
	/**
		@class		CUStringList
		@brief		StringList 클래스
		@date		08.05.06
		@author		이승욱
		@warning	???
		@bug		???
		@note		???
	*/
	////////////////////////////////////////////////////////////
	class CUStringList : public CUList
	{
	public:
		CUStringList();
		CUStringList( CUString str, CUString delimeter );
		~CUStringList();

	public:

		void PushFront( const CUString &arg_str );
		void PushBack( const CUString &arg_str );
		void RemoveFront();
		void RemoveBack();
		bool IsEmpty();
		int Find( char str[] );
		bool PopFront( CUString &ret_str );
		bool PopBack( CUString &ret_str );
		bool PopAt( int nPos, CUString &ret_str );
		bool PopAt( int nPos );
		bool GetAt( int nPos, CUString &ret_str );
		char *GetAt( int nPos );
		bool SetAt( int nPos, CUString &str );
		bool SetAt( int nPos, char *str );

		void TokenizeByChar( CUString str, CUString delimeter, bool permit_empty = true );
		void TokenizeByStr( CUString str, CUString delimeter, bool permit_empty = true );
		void TokenizeByBoundTag( CUString str, CUString open_tag, CUString close_tag, bool permit_empty = true );
		void GetIntersection( CUStringList &list1, CUStringList &list2 );

		CUString ToString( char delimeter[] = " ");
		
		void Print( FILE *fp, char delimeter[] = "\n" );
		void PrintEx( FILE *fp, char delimeter[] = "\n" );
		
		void Clear();

	};

}

#endif

