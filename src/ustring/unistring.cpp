/**
	@file		unistring.cpp
	@brief		unistring cpp
	@author		swlee
	@date		Apr. 19, 2013 ~
	@version	0.1
	@todo		
	@warning	
	@bug		
	@note		
*/
#include "unistring.h"

namespace ulib
{
	/////////////////////////////////////////////////////////////
	/**
		@brief	생성자
		@note	
		@see	~CUniString()
	*/	
	/////////////////////////////////////////////////////////////
	CUniString::CUniString()
	{
		tokenized = false;
	}

	
	/////////////////////////////////////////////////////////////
	/**
		@brief	생성자
		@note	
		@see	~CUniString()
	*/	
	/////////////////////////////////////////////////////////////
	CUniString::CUniString( char* arg_str, char* arg_enc )
		: CUString( arg_str )
	{
		tokenized = false;
		this->enc = arg_enc;
		this->enc.MakeToUpper();
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	소멸자
		@note	생성한 버퍼를 해제
		@see	CUniString()
	*/	
	/////////////////////////////////////////////////////////////
	CUniString::~CUniString()
	{
	}


	int CUniString::GetNumUniChar()
	{
		if( tokenized == false ) {
			if( this->enc == "ASCII" ) {
				if( TokenizeAscii() == false ) {
					return -1;
				}
			}
			else if( this->enc == "EUCKR" || this->enc == "CP949" ) {
				if( TokenizeEuckr() == false ) {
					return -1;
				}
			}
			else if( this->enc == "AEU" || this->enc == "ASCIIESCAPEDUNICODE" ) {
				if( TokenizeAsciiEscapedUnicode() == false ) {
					return -1;
				}
			}
		}

		return unichar_list.GetSize();
	}

	bool CUniString::TokenizeAscii()
	{
		for( int i=0; i<GetLength(); i++ ) {
			char ch = GetAt(i);
			if( (int)ch >= 0 ) {
				char buf[4]; sprintf( buf, "%c", ch );
				unichar_list.PushBack( buf );
			}
			else {
				return false;
			}
		}

		tokenized = true;
		return true;
	}

	bool CUniString::TokenizeEuckr()
	{
		for( int i=0; i<GetLength(); i++ ) {
			char ch = GetAt(i);
			if( (int)ch >= 0 ) {
				char buf[4]; sprintf( buf, "%c", ch );
				unichar_list.PushBack( buf );
			}
			else {
				if( i+1 == GetLength() ) return false;
				char ch2 = GetAt(i+1);
				char buf[4]; sprintf( buf, "%c%c", ch, ch2 );
				unichar_list.PushBack( buf );
				i++;
			}
		}

		tokenized = true;
		return true;
	}

	void dumptoBin( char ch )
	{
		int mask = 1;
		for(int i=8;i>0;i--) {
			 printf("%d",(ch & (mask << (i-1) ))?1:0);
		}
		printf( "\n" );
	}

	CUString EncodeUTF8( CUString &str )
	{
		CUString ret = "";
		if( str.GetLength() == 6 ) {
			ret = str.SubStr( 2,6 );
			unsigned long index;
			index = strtoul( ret.GetStr(), 0, 16 );
			if( 0x00 <= index && index <= 0x7F ) {
				char buf[4]; sprintf( buf, "%c", (char)index );
				ret = buf;
			}
			else if( 0x80 <= index && index <= 0x07FF )	{
				// 2byte;
				int enc_ch1 = 0xC0; // 11000000
				int enc_ch2 = 0x80; // 10000000

				char ch1 = (char)strtoul( ret.SubStr(0,2).GetStr(), 0, 16 );
				char ch2 = (char)strtoul( ret.SubStr(2,4).GetStr(), 0, 16 );

				if( ch1 & (1 << (3-1) ) ) { enc_ch1 |= (1 << (5-1) ); }
				if( ch1 & (1 << (2-1) ) ) { enc_ch1 |= (1 << (4-1) ); }
				if( ch1 & (1 << (1-1) ) ) { enc_ch1 |= (1 << (3-1) ); }

				if( ch2 & (1 << (8-1) ) ) { enc_ch1 |= (1 << (2-1) ); }
				if( ch2 & (1 << (7-1) ) ) { enc_ch1 |= (1 << (1-1) ); }
				if( ch2 & (1 << (6-1) ) ) { enc_ch2 |= (1 << (6-1) ); }
				if( ch2 & (1 << (5-1) ) ) { enc_ch2 |= (1 << (5-1) ); }
				if( ch2 & (1 << (4-1) ) ) { enc_ch2 |= (1 << (4-1) ); }
				if( ch2 & (1 << (3-1) ) ) { enc_ch2 |= (1 << (3-1) ); }
				if( ch2 & (1 << (2-1) ) ) { enc_ch2 |= (1 << (2-1) ); }
				if( ch2 & (1 << (1-1) ) ) { enc_ch2 |= (1 << (1-1) ); }

				//dumptoBin( enc_ch1 ); dumptoBin( enc_ch2 );
				char buf[4]; sprintf( buf, "%c%c", enc_ch1, enc_ch2 );
				ret = buf;
			}
			else if( 0x0800 <= index && index <= 0xFFFF )	{
				// 3byte;
				char enc_ch1 = 0xE0; // 11100000
				char enc_ch2 = 0x80; // 10000000
				char enc_ch3 = 0x80; // 10000000

				char ch1 = (char)strtoul( ret.SubStr(0,2).GetStr(), 0, 16 );
				char ch2 = (char)strtoul( ret.SubStr(2,4).GetStr(), 0, 16 );

				if( ch1 & (1 << (8-1) ) ) { enc_ch1 |= (1 << (4-1) ); }
				if( ch1 & (1 << (7-1) ) ) { enc_ch1 |= (1 << (3-1) ); }
				if( ch1 & (1 << (6-1) ) ) { enc_ch1 |= (1 << (2-1) ); }
				if( ch1 & (1 << (5-1) ) ) { enc_ch1 |= (1 << (1-1) ); }

				if( ch1 & (1 << (4-1) ) ) { enc_ch2 |= (1 << (6-1) ); }
				if( ch1 & (1 << (3-1) ) ) { enc_ch2 |= (1 << (5-1) ); }
				if( ch1 & (1 << (2-1) ) ) { enc_ch2 |= (1 << (4-1) ); }
				if( ch1 & (1 << (1-1) ) ) { enc_ch2 |= (1 << (3-1) ); }

				if( ch2 & (1 << (8-1) ) ) { enc_ch2 |= (1 << (2-1) ); }
				if( ch2 & (1 << (7-1) ) ) { enc_ch2 |= (1 << (1-1) ); }
				if( ch2 & (1 << (6-1) ) ) { enc_ch3 |= (1 << (6-1) ); }
				if( ch2 & (1 << (5-1) ) ) { enc_ch3 |= (1 << (5-1) ); }

				if( ch2 & (1 << (4-1) ) ) { enc_ch3 |= (1 << (4-1) ); }
				if( ch2 & (1 << (3-1) ) ) { enc_ch3 |= (1 << (3-1) ); }
				if( ch2 & (1 << (2-1) ) ) { enc_ch3 |= (1 << (2-1) ); }
				if( ch2 & (1 << (1-1) ) ) { enc_ch3 |= (1 << (1-1) ); }

				//dumptoBin( enc_ch1 ); dumptoBin( enc_ch2 ); dumptoBin( enc_ch3 );

				char buf[4]; sprintf( buf, "%c%c%c", enc_ch1, enc_ch2, enc_ch3 );
				ret = buf;
			}
		}

		return ret;
	}


	bool CUniString::TokenizeAsciiEscapedUnicode()
	{

		CUString tmp = GetStr();
		while( true ) {
			int idx = tmp.Find( "\\u" );
			if( idx < 0 )	{
				for( int i=0; i<tmp.GetLength(); i++ ) {
					char ch = tmp.GetAt(i);
					if( (int)ch >= 0 ) {
						char buf[4]; sprintf( buf, "%c", ch );
						unichar_list.PushBack( buf );
					}
					else {
						return false;
					}
				}
				break;
			}
			else {
				for( int i=0; i<idx; i++ ) {
					char ch = tmp.GetAt(i);
					if( (int)ch >= 0 ) {
						char buf[4]; sprintf( buf, "%c", ch );
						unichar_list.PushBack( buf );
					}
					else {
						return false;
					}
				}
				CUString uni = tmp.SubStr( idx, idx+6 );
				uni = EncodeUTF8( uni );
				unichar_list.PushBack( uni );
				tmp = tmp.Mid( idx+6 );
			}
		}

		tokenized = true;
		return true;
	}

	void CUniString::Print( FILE *fp )
	{
		if( tokenized == false )	return;
		for( int i=0; i<unichar_list.GetSize(); i++ ) {
			fprintf( fp, "[%s] ", unichar_list.GetAt(i) );
		}
		fprintf( fp, "\n" );
	}

}

