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
	inline CUStringListRO::CUStringListRO()	
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


	////////////////////////////////////////////////////////////
	/**
		@brief	소멸자
	*/
	////////////////////////////////////////////////////////////
	inline CUStringListRO::~CUStringListRO()
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
		str.Empty();

	}

	////////////////////////////////////////////////////////////
	inline size_t CUStringListRO::GetSize()
	{
		return size;
	}


	////////////////////////////////////////////////////////////
	void CUStringListRO::MakeList( const CUString &arg_str, CUString delimeter )
	{
		str = arg_str;
		pos = new int[str.GetLength()+1];
		size=0;
		pos[size++] = 0;

		for( int i=0; i<str.GetLength(); i++ )	{
			for( int j=0; j<delimeter.GetLength(); j++ )	{
				if( str.GetAt(i) == delimeter.GetAt(j) )	{
					str.SetAt(i, '\0' );
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
		
		return &( str.GetStr()[idx] );
	}

}

// EOF
