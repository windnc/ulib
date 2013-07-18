/**
	@file		ustringlistro.cpp
	@brief		ustringlistrocpp
	@author		swlee
	@date		Oug. 14, 2006 ~
	@version	0.5
	@todo		???
	@warning	???
	@bug		???
*/
#include "ustringlistro.h"

namespace ulib
{

	////////////////////////////////////////////////////////////
	/**
		@brief	Constructor
	*/
	////////////////////////////////////////////////////////////
	CUStringListRO::CUStringListRO()	
	{
		pos = NULL;
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	Constructor
		@param	str	초기 문자열
		@param	delimeter	 초기 문자열을 나눌 문자들
	*/
	////////////////////////////////////////////////////////////
	CUStringListRO::CUStringListRO( const CUString &str, const CUString &delimeter )
	{
		CUStringListRO();
		MakeList( str, delimeter );
	}

	CUStringListRO::CUStringListRO(const CUStringListRO &src )
	{
		CUStringListRO();
		MakeList( src.str_org, src.del );
	}

	/////////////////////////////////////////////////////////////
	CUStringListRO& CUStringListRO::operator=(CUStringListRO &rhs )
	{
		this->Clear();
		this->MakeList( rhs.str_org, rhs.del );
		return *this;
	}

	////////////////////////////////////////////////////////////
	/**
		@brief	소멸자
	*/
	////////////////////////////////////////////////////////////
	CUStringListRO::~CUStringListRO()
	{
		Clear();
	} 


	////////////////////////////////////////////////////////////
	void CUStringListRO::Clear()
	{
		if( pos != NULL )	{
			delete pos;
			pos = NULL;
		}
		size = 0;
		buf.Empty();

	}

	////////////////////////////////////////////////////////////
	size_t CUStringListRO::GetSize()
	{
		return size;
	}


	////////////////////////////////////////////////////////////
	void CUStringListRO::MakeList( const CUString &arg_str, CUString delimeter )
	{
		str_org = arg_str;
		del = delimeter;
		buf = arg_str;
		pos = new int[buf.GetLength()+1];
		size=0;
		pos[size++] = 0;

		for( int i=0; i<buf.GetLength(); i++ )	{
			for( int j=0; j<delimeter.GetLength(); j++ )	{
				if( buf.GetAt(i) == delimeter.GetAt(j) )	{
					buf.SetAt(i, '\0' );
					pos[size++] = i+1;
					break;
				}
			}
		}
	}


	////////////////////////////////////////////////////////////
	char *CUStringListRO::GetAt( int nPos )
	{
		if( nPos < 0 || nPos > (int)GetSize())	return NULL;

		int idx = pos[nPos];
		
		return &( buf.GetStr()[idx] );
	}

	////////////////////////////////////////////////////////////
	void CUStringListRO::Print( FILE *fp, char delimeter[] )
	{
		for( int i=0; i<(int)GetSize(); i++ )	{
			if( i > 0 )	{
				fprintf( fp, "%s", delimeter );
			}
			fprintf( fp, "%s", GetAt(i) );
		}
	}

	////////////////////////////////////////////////////////////
	int CUStringListRO::Find( CUStringListRO &list, int start )
	{
		if( this->GetSize() < list.GetSize() )	return -1;

		for( int i=start; i<this->GetSize() - list.GetSize(); i++ ) {
			bool match = true;
			for( int j=0; j<list.GetSize(); j++ ) {
				if( strcmp( this->GetAt(i+j), list.GetAt(j) ) != 0 ) {
					match = false;
					break;
				}
			}
			if( match == true ) {
				return i;
			}
		}

		return -1;
	}

}

// EOF
