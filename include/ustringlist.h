/**
	@file		ustringlist.h
	@brief		ustringlist header
	@author		이승욱
	@date		May 6, 2008
	@version	0.6
	@todo		
	@warning	
	@bug		
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

	class CUStringListNode : public CUListNode {
	};

	////////////////////////////////////////////////////////////
	/**
		@class		CUStringList
		@brief		StringList class
		@date		May 06, 2008
		@author		swlee
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
		CUStringList(const CUStringList &src );
		CUStringList & operator=(CUStringList &);

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
		bool GetAt( int nPos, CUString &ret_str ) const;
		char *GetAt( int nPos ) const;
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

