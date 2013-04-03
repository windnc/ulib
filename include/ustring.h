/**
	@file		ustring.h
	@brief		ustring header
	@author		이승욱
	@date		06.09.21
	@version	0.9.1
	@todo		Format 구현, 메모리 효율성 개선
	@warning	???
	@bug		???
	@note		Release0.9
*/
#ifndef ___ustring___
#define ___ustring___

#ifndef UNDEFINE
#define UNDEFINE	-1
#endif
#ifndef NOT_FOUND
#define NOT_FOUND	-1
#endif

#ifndef ERR1
#define ERR1	-2
#endif
#ifndef ERR2
#define ERR2	-3
#endif
#ifndef DEF_BUFF_SIZE
#define DEF_BUFF_SIZE	1024
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

namespace ulib
{

	/**
		@class		CUString
		@brief		String 클래스
		@date		06.05.27
		@author		이승욱
		@warning	???
		@todo		???
		@bug		???
		@note		MFC의 CString과 비슷한(최대한 닮은) 클래스.\n
					부분적인 한글 처리 \n

					테스트 환경\n
						- x86, WinXP, vs2003\n
						- x86, Redhat 9, g++\n
						- HP, HPUX, g++\n
						
	*/

	class CUString {
	public:
		CUString();
		CUString( char arg_str[] );
		CUString( const char arg_str[] );
		CUString( const CUString &rhs );
		~CUString();
		char operator[](int nIndex);
		void operator+=( char rhs[]);
		void operator+=( CUString rhs);
		CUString & operator=( char[]);
		CUString & operator=(CUString);
		CUString operator+( char[]);
		CUString operator+( CUString);
		bool operator==( CUString rhs );
		bool operator!=( CUString rhs );
		

		// The String as an Array
		bool IsEmpty();						//
		void Empty();						//
		char GetAt( int nIndex );				//
		void SetAt( int nIndex, char ch );			//
		int GetLength();					//
		
		// Extraction
		CUString Left( int nCount );				//
		CUString Right( int nCount );				//
		CUString Mid( int nFirst  );		//
		CUString Mid( int nFirst, int nCount );		//

		// Searching
		int Find( CUString &find, int pos = 0 );			//
		int Find( char find, int pos = 0 );			//
		int Find( char find[], int pos = 0 );		//
		int FindCasefree( CUString &find, int pos = 0 );
		int FindCasefree( char find, int pos = 0 );
		int FindCasefree( char find[], int pos = 0 );
		int ReverseFind( char ch );


		// Other Conversion
		void MakeToUpper();					//
		void MakeToLower();					//
		char MakeToUpperChar(char ch);
		char MakeToLowerChar(char ch);
		int Replace( char chOld[], char chNew[], bool caseFree = false );	//
		int Delete( int nIndex, int nCount );			//
		int DeleteStr( char chStr[], bool caseFree = false );			//
		int DeleteBoundTag( char chStart[], char chEnd[] );			//
		void Trim( char chTarget[] =" \t\n\r" );			// 
		void TrimLeft( char chTarget[] = " \t\n\r" );			// 
		void TrimRight( char chTarget[] = " \t\n\r" );			// 

		// 직접 구현한것 (MFC엔 없음)
		char* GetStr();						//
		CUString GetColorStr( char *color );						//
		void SetStr( char arg_str[]);				//
		void SetStr( CUString arg_str);				//
		CUString SubStr( int start, int end );		// 
		unsigned int Count( char find );
		unsigned int Count( char find[] );
		bool IsNumber();
		bool IsAlpha();
		bool IsASCII();
		void Print( FILE *fp = stdout );
		void SetColor( char color[] );
		static void NumberFormat( unsigned long size, CUString &str );
		static void FileSizeFormat( unsigned long num, CUString &str);

		void Remove( char *str );
		void Remove( CUString &str );

		

		// 한글 처리
		int GetCharLength();
		int CharToIdx( int nIndex );
		CUString GetChar( int nIndex );
		CUString GetChars( int nIndex, int nCount );
		int DeleteChars( int nIndex, int nCount );


	private:
		char *str;		///< 버퍼
		int len;		///< 길이
		int char_len;	///< 글자 수


	};

}

#endif

