/**
	@file		ustring.cpp
	@brief		ustring cpp
	@author		이승욱
	@date		Sep. 21. 2006 ~
	@version	1.0
	@todo		Format 구현, 메모리 효율성 개선
	@warning	???
	@bug		???
	@note		Release 1.0
*/
#include "ustring.h"

namespace ulib
{
	/////////////////////////////////////////////////////////////
	/**
		@brief	생성자
		@note	기본 크기(1024 Byte)로 버퍼를 생성
		@see	~CUString()
	*/	
	/////////////////////////////////////////////////////////////
	CUString::CUString()
	{
		str = new char[DEF_BUFF_SIZE];
		str[0] = '\0';
		len = 0;
		char_len = UNDEFINE;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	생성자	
		@param	arg_str	생성하면서 채워 넣을 문자열
		@note	입력받은 char[] 크기만큼 버퍼를 생성
		@see	~CUString()
	*/	
	/////////////////////////////////////////////////////////////
	CUString::CUString( char arg_str[] )
	{
	//	SetStr( arg_str );
		len = (int)strlen( arg_str );
		char_len = UNDEFINE;

		str = new char[len+1];
		sprintf( str, "%s", arg_str );
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	생성자	
		@param	arg_str	생성하면서 채워 넣을 문자열
		@note	입력받은 const char[] 크기만큼 버퍼를 생성
		@see	~CUString()
	*/	
	/////////////////////////////////////////////////////////////
	CUString::CUString( const char arg_str[] )
	{
	//	SetStr( arg_str );
		len = (int)strlen( arg_str );
		char_len = UNDEFINE;

		str = new char[len+1];
		sprintf( str, "%s", arg_str );
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	생성자
		@param	rhs	복사하려는 CUString 객체
		@note	입력받은 CUString를 복사
		@see	~CUString()
	*/	
	/////////////////////////////////////////////////////////////
	CUString::CUString( const CUString &rhs )
	{
		len = rhs.len;
		char_len = rhs.char_len;

		if( len < 0 )	return;

		str = new char[len+1];
		sprintf( str, "%s", rhs.str );
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	소멸자
		@note	생성한 버퍼를 해제
		@see	CUString()
	*/	
	/////////////////////////////////////////////////////////////
	CUString::~CUString()
	{
		if( str )	delete str;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 char *를 구함
		@return	char *를 리턴
		@see	SetStr()
	*/	
	/////////////////////////////////////////////////////////////
	char* CUString::GetStr()
	{
		return str;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 char *를 구함 컬러링
		@return	char *를 리턴
		@see	SetStr()
	*/	
	/////////////////////////////////////////////////////////////
	CUString CUString::GetColorStr( char *color )
	{
		CUString tmp = *this;
		tmp.SetColor( color );
		return tmp;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 길이(Byte)를 구함
		@return	길이를 리턴
		@see	GetCharLength()
	*/	
	/////////////////////////////////////////////////////////////
	int CUString::GetLength()
	{
		return len;
	}


	void CUString::Print( FILE *fp )
	{
		if( fp == NULL )	return;
		fprintf( fp, "%s\n", GetStr() );
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 글자수를 구함
		@return	글자수를 리턴
		@see	GetLength()
	*/	
	/////////////////////////////////////////////////////////////
	int CUString::GetCharLength()
	{
		if( char_len != UNDEFINE )	return char_len;

		char_len = 0;
		for( int i=0; i<len; i++ )	{
			char_len++;

			// 한글
			if( str[i] < 0 )	{
				i++; // 1바이트 더 읽음
			}
		}

		return char_len;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 특정 위치의 char를 구함
		@param	nIndex	구하려는 char의 위치
		@return	nIndex번째 char를 리턴\n찾을려는 위치기 길이보다 크다면 \\0을 리턴
		@see	GetCharLength()
	*/	
	/////////////////////////////////////////////////////////////
	char CUString::GetAt( int nIndex )
	{
		if( nIndex < len )	return str[nIndex];
		else				return '\0';
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 특정 위치의 글자를 구함
		@param	nPos	구하려는 글자의 위치
		@return	nPos 번째 글자를 리턴
		@see	GetChars()
	*/	
	/////////////////////////////////////////////////////////////
	CUString CUString::GetChar( int nPos )
	{	
		// nPos에 해당하는 글자의 위치를 구함
		int i = CharToIdx( nPos );
		if( i < 0 )	return CUString("");

		if( str[i] >= 0 )	{
			char tmp[2];
			tmp[0] = str[i];
			tmp[1] = '\0';
			CUString t(tmp);
			return t;
		}
		else	{
			char tmp[3];
			tmp[0] = str[i];
			tmp[1] = str[i+1];
			tmp[2] = '\0';

			CUString t(tmp);
			return t;
		}

	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 특정 위치의 글자들을 구함
		@param	nIndex	구하려는 글자의 위치
		@param	nCount	구하려는 글자의 개수
		@return	nPos 번째 글자부터 nCount개의 글자를 리턴
		@see	GetChar()
	*/	
	/////////////////////////////////////////////////////////////
	CUString CUString::GetChars( int nIndex, int nCount )
	{
		if( nIndex < 0 )	nIndex = 0;
		CUString tmp;
		for( int i=0; i<nCount; i++ )	{
			CUString ch = GetChar( nIndex+i );
			if( ch.IsEmpty() )	break;
			
			tmp+=ch;
		}
		return tmp;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	글자의 위치로 offset을 찾음
		@param	nPos	글자의 위치
		@return	nIndex번째 글짜가 시작하는 위치
	*/	
	/////////////////////////////////////////////////////////////
	int CUString::CharToIdx( int nPos )
	{
		if( nPos < 0 )	return -1;
		
		int found = 0;
		int i=0;
		for( i=0; found<nPos; i++ )	{
			if( i > len || found > GetCharLength() )	{
				return -1;
			}

			// 한글체크
			if( str[i] < 0 )	i++;

			// 읽은 글자 수 증가
			found++;
		}

		return i;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 특정 위치의 글자들을 삭제
		@param	nIndex	글자의 위치
		@param	nCount	글자의 수
		@return 지워진 byte 크기
		@note	nIndex번째 글자부터 nCount개의 글자를 삭제
	*/	
	/////////////////////////////////////////////////////////////
	int CUString::DeleteChars( int nIndex, int nCount )
	{
		if( nIndex < 0 )	nIndex = 0;
		if( nCount <= 0 )	return 0;
		
		int prev_len = GetLength();
		int nIndex_char = CharToIdx( nIndex );
		int nCount_char = CharToIdx( nIndex+nCount );

		// 문자열 길이보다 큰 경우
		if( nCount_char < 0 )	{
			SetStr( Left( nIndex_char ).GetStr() );
			return prev_len - GetLength();
		}
		

		CUString tmp = Left( nIndex_char ) + Mid( nCount_char );
		SetStr( tmp.GetStr() );
		return  prev_len - GetLength();

	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 특정 위치에 char를 설정
		@param	nIndex	설정하려는 char의 위치
		@param	ch	설정하려는 char
		@note	길이보다 긴 위치에 설정하려고 하면 아무 작업도 안함.
		@see	GetAt()
	*/	
	/////////////////////////////////////////////////////////////
	void CUString::SetAt( int nIndex, char ch )
	{
		if( len < nIndex )	return;
		str[nIndex] = ch;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String를 char[]로 설정
		@param	arg	설정하려는 char[]
		@note	현재 버퍼보다 긴 입력이 들어오면 크기에 맞게 버퍼를 재할당 후 복사
		@see	GetAt()
	*/	
	/////////////////////////////////////////////////////////////
	void CUString::SetStr( char arg[] )
	{
		// 설정하려는 문자열이 기존 버퍼보다 크다면 재할당
		int arg_len = (int)strlen( arg );	
		if( arg_len > (int)strlen( str ) )	{
			if( str )	delete str;
			str = new char[arg_len+1];
		}
		
		sprintf( str, "%s", arg );
		len = arg_len;
		char_len = UNDEFINE;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String를 String으로 설정
		@param	arg	설정하려는 String
		@note	현재 버퍼보다 긴 입력이 들어오면 크기에 맞게 버퍼를 재할당 후 복사
		@see	SetStr() GetStr()
	*/	
	/////////////////////////////////////////////////////////////
	void CUString::SetStr( CUString arg )
	{
		SetStr( arg.GetStr() );
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 일부분을 삭제
		@param	nIndex	지우려는 시작 위치
		@param	nCount	지우려는 개수(Byte)
		@return	지워진 byte 크기
		@see	GetAt()
	*/	
	/////////////////////////////////////////////////////////////
	int CUString::Delete( int nIndex, int nCount )
	{
		/*
		if( nIndex + nCount > len )	return 0;
		if( nIndex < 0 )	return 0;

		char *tmp = new char[len-nCount+1];
		int idx = 0;

		int i;
		for( i=0; i<nIndex; i++ )	{
			tmp[idx++] = str[i];
		}

		i+= nCount;
		for( ; i<len; i++ )	{
			tmp[idx++] = str[i];
		}
		tmp[idx] ='\0';
		
		if( str )	delete str;
		str = new char[ strlen( tmp )];
		strcpy( str, tmp );

		return nCount;
		*/

		
		int prev_len = GetLength();
		CUString tmp = Left( nIndex ) + Mid( nIndex+nCount );
		SetStr( tmp.GetStr() );
		return  prev_len - GetLength();	
	}


	/////////////////////////////////////////////////////////////
	int CUString::DeleteStr( char chStr[], bool caseFree )
	{
		return Replace( chStr, "", caseFree );
	}


	/////////////////////////////////////////////////////////////
	int CUString::DeleteBoundTag( char chStart[], char chEnd[] )
	{
		int cnt = 0;
		while(1)	{
			int idx = Find( chStart );
			if( idx < 0 )	break;

			int idx2 = Find( chEnd, idx+strlen(chStart) );
			if( idx2 < 0 )	break;

			SetStr( Left( idx ) + Mid( idx2+strlen(chEnd) ) );

			cnt++;
		}

		return cnt;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	[] 연산자
		@param	nIndex	구하려는 위치
		@return	해당 위치의 char를 리턴
		@see	GetAt()
	*/	
	/////////////////////////////////////////////////////////////
	char CUString::operator[]( int nIndex )
	{
		return GetAt( nIndex );
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	+= 연산자
		@param	rhs	뒤에 붙히려는 char[]
	*/	
	/////////////////////////////////////////////////////////////
	void CUString::operator+=( char rhs[] )
	{
		CUString t( rhs );
		operator+=( t );
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	+= 연산자
		@param	rhs	뒤에 붙히려는 String 객체
	*/	
	/////////////////////////////////////////////////////////////
	void CUString::operator+=( CUString rhs )
	{
		if( rhs.IsEmpty() )	return;

		len += rhs.GetLength();
		char *tmp = new char[ len + 1 ];
		sprintf( tmp, "%s%s", str, rhs.GetStr() );

		delete str;
		str = tmp;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	== 연산자
		@param	rhs	비교하려는 String 객체
		@return	두 Stirng이 같으면 true를 리턴
	*/	
	/////////////////////////////////////////////////////////////
	bool CUString::operator==( CUString rhs )
	{
		if( strcmp( str, rhs.GetStr() ) == 0 )	return true;
		return false;
		
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	!= 연산자
		@param	rhs	비교하려는 String 객체
		@return	두 Stirng이 다르면 true를 리턴
	*/	
	/////////////////////////////////////////////////////////////
	bool CUString::operator!=( CUString rhs )
	{
		if( strcmp( str, rhs.GetStr() ) == 0 )	return false;
		return true;
		
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	+ 연산자
		@param	rhs 뒤에 붙히려는 char[]
		@return	현재 String의 뒤에 rhs를 붙힌 새로운 String 객체를 리턴
	*/	
	/////////////////////////////////////////////////////////////
	CUString  CUString::operator+( char rhs[])
	{
		CUString t( rhs );
		return operator+( t );
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	+ 연산자
		@param	rhs 뒤에 붙히려는 String 객체
		@return	현재 String의 뒤에 rhs를 붙힌 새로운 String 객체를 리턴
	*/	
	/////////////////////////////////////////////////////////////
	CUString  CUString::operator+(  CUString rhs )
	{
		char *tmp = new char[len + rhs.GetLength()+1];
		int i;
		for( i=0; i<len; i++ )	{
			tmp[i] = str[i];
		}
		for( int j=0; j<rhs.GetLength(); j++ )	{
			tmp[i] = rhs.GetAt(j);
			i++;
		}
		tmp[i] = '\0';
		CUString t( tmp );

		delete tmp;
		return t;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	= 연산자
		@param	rhs	복사하려는 char[]
		@return	설정후의 String 객체 자신의 주소
	*/	
	/////////////////////////////////////////////////////////////
	CUString& CUString::operator=( char rhs[] )
	{
		CUString t( rhs );
		return operator=( t );
	}

	/////////////////////////////////////////////////////////////
	/**
		@brief	= 연산자, String을 rhs로 설정
		@param	rhs	복사하려는 String 객체
		@return	설정후의 String 객체 자신의 주소
	*/	
	/////////////////////////////////////////////////////////////
	CUString& CUString::operator=( CUString rhs )
	{
		// 복사하려는 문자열의 길이가 버퍼보다 크면 재할당
		if( len < rhs.GetLength() )	{
			if( str )  delete str;
			str = new char[rhs.GetLength()+1];
		}

		sprintf( str, "%s", rhs.GetStr() );
		len = rhs.GetLength();
		char_len = UNDEFINE;
		return *this;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	비어있는지 여부를 체크함
		@return	비어있으면 true를 리턴
		@see	Empty()
	*/	
	/////////////////////////////////////////////////////////////
	bool CUString::IsEmpty()
	{
		if( !str )	return true;
		if( GetLength() == 0 )	return true;
		else					return false;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String을 비움
		@see	IsEmpty()
	*/	
	/////////////////////////////////////////////////////////////
	void CUString::Empty()
	{
		str[0] = '\0';
		len = 0;
		char_len = UNDEFINE;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String을 둘로 나눠 왼쪽 영역을 구함
		@param	pos	나눌려는 위치( 왼쪽부터 시작 )
		@return	왼쪽 영역의 String 객체
		@see	Mid(), Right()
	*/	
	/////////////////////////////////////////////////////////////
	CUString CUString::Left( int pos )
	{
		if ( pos < 0)	pos = 0;
		if( pos >= GetLength() )	{
			return( *this );
		}

		return this->SubStr( 0, pos );
	}



	/////////////////////////////////////////////////////////////
	/**
		@brief	String을 둘로 나눠 오른쪽 영역을 구함
		@param	pos	나눌려는 위치( 오른쪽부터 시작 )
		@return	오른쪽 역역의 String 객체
		@see	Left(), Mid()
		@warning	Mid와 헷갈리기 쉬움
	*/
	/////////////////////////////////////////////////////////////
	CUString CUString::Right( int pos )
	{
		if (pos < 0)	pos =  0;

		if( pos >= GetLength() )	{
			return( *this );
		}
		return this->SubStr( len-pos, len );
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 일부분을 구함
		@param	nFirst	일부분의 시작위치
		@return	일부분의 String 객체
		@see	Left(), Right(), SubStr()
		@note	SubStr()와 유사
	*/
	/////////////////////////////////////////////////////////////
	CUString CUString::Mid( int nFirst )
	{
		return Mid( nFirst, len-nFirst );
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 일부분을 구함
		@param	nFirst	일부분의 시작위치
		@param	nCount	일부분의 길이, 단, 0 일때는 남은 모든 문자열의 개수
		@return	일부분의 String 객체
		@see	Left(), Right(), SubStr()
		@note	SubStr()와 유사
	*/
	/////////////////////////////////////////////////////////////
	CUString CUString::Mid( int nFirst, int nCount )
	{
		if( nFirst < 0 )	nFirst = 0;
		if( nCount < 0 )	nCount = 0;

		if( nFirst+nCount > GetLength() )	{
			nCount = GetLength()-nFirst;
		}

		if( nFirst > GetLength() )	{
			nCount = 0;
		}
		return this->SubStr( nFirst, nFirst+nCount );
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 일부분을 구함
		@param	start	일부분의 시작위치
		@param	end	일부분의 끝위치
		@return	일부분의 String 객체
		@see	Left(), Right(), Mid()
		@note	Mid와 비슷하나 두번째 인자가(end) 마지막 인덱스임, MFC에선 길이(nCount)였음.
	*/
	////////////////////////////////////////////////////////////
	CUString CUString::SubStr( int start, int end )
	{
		if( start > end )	return CUString("");
		if( start > len )	return CUString("");

		int diff = end - start;
		char *tmp = new char[diff+1];
		int pos = 0;
		for( int i=start; i<end; i++ )	{
			tmp[pos++] = str[i];
		}

		tmp[pos] = '\0';	
		CUString ret( tmp );
		if( tmp )	delete tmp;

		return ret;
	}


	//////////////////////////////////////////////
	/**
		@brief	String의 내부에 해당 string이 있는지 검색
		@param	find	찾으려는 string
		@param	pos	찾기 시작할 위치
		@return	찾은 위치\n찾지 못했을 경우 음수값을 리턴
	*/
	////////////////////////////////////////////////////////////
	int CUString::Find( char find, int pos )
	{
		if( pos > len )	return -1;
		for( int i=pos; i<len; i++ )	{
			if( str[i] == find ) 	return i;
		}
		return -1;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 내부에 해당 string이 있는지 검색
		@param	find	찾을려는 string
		@param	pos	찾기 시작할 위치
		@return	찾은 위치\n찾지 못했을 경우 음수값을 리턴
	*/
	////////////////////////////////////////////////////////////
	int CUString::Find( CUString &find, int pos )
	{
		return this->Find( (char*)find.GetStr(), pos );
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 내부에 해당 string이 있는지 검색
		@param	find	찾을려는 string
		@param	pos	찾기 시작할 위치
		@return	찾은 위치\n찾지 못했을 경우 음수값을 리턴
	*/
	////////////////////////////////////////////////////////////
	int CUString::Find( char find[], int pos )
	{
		if( pos > len )	return -1;
		int find_len = (int)strlen( find );
		if( find_len <= 0 )	return -1;

		for( int i=pos; i<len; i++ )	{
			if( str[i] == find[0] )	{
				bool match = true;
				for( int j=1; j<find_len; j++ )	{
					if( str[i+j] !=  find[j] )	{
						match = false;
						break;
					}
				}
				if( match == true )	{
					return i;
				}
			}
		}
		return -1;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 내부에 해당 string이 있는지 대소문자 구별 없이 검색
		@param	find	찾을려는 string
		@param	pos	찾기 시작할 위치
		@return	찾은 위치\n찾지 못했을 경우 음수값을 리턴
	*/
	////////////////////////////////////////////////////////////
	int CUString::FindCasefree( CUString &find, int pos )
	{
		return this->FindCasefree( find.GetStr(), pos );
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 내부에 해당 string이 있는지 대소문자 구별 없이 검색
		@param	find	찾을려는 string
		@param	pos	찾기 시작할 위치
		@return	찾은 위치\n찾지 못했을 경우 음수값을 리턴
	*/
	////////////////////////////////////////////////////////////
	int CUString::FindCasefree( char find[], int pos )
	{
		if( pos > len )	return -1;
		int find_len = (int)strlen( find );
		if( find_len <= 0 )	return -1;

		for( int i=pos; i<len; i++ )	{
			if( MakeToUpperChar(str[i]) == MakeToUpperChar(find[0]) )	{
				bool match = true;
				for( int j=1; j<find_len; j++ )	{
					if( MakeToUpperChar( str[i+j] ) != 
						MakeToUpperChar( find[j]  ) )	{
						match = false;
						break;
					}
				}
				if( match == true )	{
					return i;
				}
			}
		}
		return -1;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 내부에 해당 char이 있는지 뒤에서 부터 검색
		@param	ch	찾을려는 char
		@return	찾은 위치\n찾지 못했을 경우 -1을 리턴
	*/
	////////////////////////////////////////////////////////////
	int CUString::ReverseFind( char ch )
	{
		for( int i=GetLength(); i>0; i-- )	{
			if( GetAt( i ) == ch )	return i;
		}
		return -1;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 내부에 해당 char[]을 새로운 char[]로 교체
		@param	chOld	대상 char[]
		@param	chNew	교체할 char[]
		@return	교체한 개수
	*/
	////////////////////////////////////////////////////////////
	int CUString::Replace( char chOld[], char chNew[], bool caseFree )
	{
#ifdef USTR_DBG
		fprintf( stdout, "start replace\n" );
		fprintf( stdout, "[%s] [%s]->[%s]\n", GetStr(), chOld, chNew );
#endif
		
		if( IsEmpty() == true )	{
#ifdef USTR_DBG
		fprintf( stdout, "fail: null string\n" );
#endif
			return 0;
		}

		// 새 문자열의 길이 설정
		size_t realloc_len = len+1;
		// new가 old보다 길면 충분히 크게 설정함
		if( strlen(chNew) > strlen(chOld) )	{
			realloc_len = (len * (strlen(chNew)+1)) + 1;
		}

		char *new_str = new char[ realloc_len ];
		if( new_str == NULL )	{
#ifdef USTR_DBG
		fprintf( stdout, "allocation fail\n" );
#endif
			return -1;
		}
		else	{
#ifdef USTR_DBG
		fprintf( stdout, "allocation succ: %d\n", realloc_len );
#endif
		}

		size_t new_len = strlen( chNew );
	//	size_t old_len = strlen( chOld );
		size_t new_pos =0;
		int num = 0;
		int start_pos = 0;
		while(1)	{
			int found_idx = -1;
			if( caseFree == true )	{
				found_idx =	FindCasefree( chOld, start_pos );
			}
			else	{
				found_idx =	Find( chOld, start_pos );
			}
			if( found_idx < 0 )	break;

#ifdef USTR_DBG
		fprintf( stdout, "found at %d\n", found_idx );
#endif

			// copy left part
			for(int i=start_pos; i<(int)found_idx; i++ )	{
				new_str[new_pos] = GetAt(i);
				new_pos++;
			}

			// copy new string part
			for(int i=0; i<(int)new_len; i++ )	{
				new_str[new_pos] = chNew[i];
				new_pos++;
			}
			start_pos = found_idx+(int)strlen( chOld );
			num++;
		}

		// copy remained
		for(int i=start_pos; i<(int)GetLength(); i++ )	{
			new_str[new_pos] = GetAt(i);
			new_pos++;
		}

		new_str[new_pos] = '\0';
		

		delete str;
		str = new_str;
		len = (int)strlen( str );
		char_len = UNDEFINE;

#ifdef USTR_DBG
		fprintf( stdout, "[%s]\n", GetStr() );
		fprintf( stdout, "replace finish\n" );
#endif
		return num;
	}


	/*
	int CUString::Replace( char chOld[], char chNew[])
	{
		int num = 0;
		int start_pos = 0;
		size_t new_len = strlen( chNew );

		while( 1 )	{
			int found_idx = Find( chOld, start_pos );
			if( found_idx < 0 )	break;

	//		CUString tmp_l = Left( found_idx );
	//		CUString tmp_r = Mid( found_idx + (int)strlen( chOld ) );

	//		sprintf( new_str, "%s%s%s", tmp_l.str, chNew, tmp_r.str );
	//		sprintf( new_str, "%s%s%s", Left( found_idx).GetStr(), chNew, Mid( found_idx + (int)strlen(chOld) ).GetStr() );
			
			char *new_str = new char[len+ strlen(chNew)+1];
			size_t new_pos=0;

			// copy left part
			for( size_t i=0; i<found_idx; i++ )	{
				new_str[new_pos] = GetAt(i);
				new_pos++;
			}

			// copy new string part
			for( size_t i=0; i<new_len; i++ )	{
				new_str[new_pos] = chNew[i];
				new_pos++;
			}

			// copy right part
			for( size_t i=found_idx+(int)strlen(chOld); i<GetLength(); i++ )	{
				new_str[new_pos] = GetAt(i);
				new_pos++;
			}
			new_str[new_pos] = '\0';

		
			// overwrite new string to the original one
			delete str;
			str = new_str;
			len = (int)strlen( str );
			char_len = UNDEFINE;

			num++;
			start_pos = found_idx+(int)strlen( chNew);
		}

		return num;
	}
	*/


	////////////////////////////////////////////////////////////
	void CUString:: Remove(CUString &str )
	{
		this->Remove( str.GetStr() );
	}


	////////////////////////////////////////////////////////////
	void CUString:: Remove( char *str )
	{
		bool *mask = new bool[ GetLength() +1 ];
		char *new_str = new char [ GetLength() + 1 ];

		for( int i=0; i<GetLength(); i++ )	{
			mask[i] = true;
		}

		size_t str_len = strlen( str );
		int last_idx = -1;
		while(1)	{
			int idx = Find( str, last_idx + 1 );
			if( idx < 0 )	break;

			for( int i = idx; i<idx+(int)str_len; i++ )	{
				mask[i] = false;
			}
			last_idx = idx + str_len - 1;
		}

		size_t final_len=0;
		for( int i=0; i<GetLength(); i++ )	{
			if( mask[i] == true )	{
				new_str[ final_len ] = GetAt(i);
				final_len++;
			}
		}
		new_str[ final_len ] = '\0';
		SetStr( new_str );


		delete new_str;
		delete mask;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 내부에 해당 char이 몇 개 있는지 검색
		@param	find	찾으려는 char
		@return	찾은 회수
	*/
	////////////////////////////////////////////////////////////
	unsigned int CUString::Count( char find )
	{
		char str[2];
		str[0] = find;
		str[1] = '\0';
		return Count( str );
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 내부에 해당 char[]이 몇 개 있는지 검색
		@param	find	찾으려는 char[]
		@return	찾은 회수
	*/
	////////////////////////////////////////////////////////////
	unsigned int CUString::Count( char find[] )
	{
		unsigned int num = 0;
		size_t start_pos = 0;
		while( 1 )	{
			int found_idx = Find( find, start_pos );
			if( found_idx < 0 )	break;

			num++;
			start_pos = found_idx+(size_t)strlen( find);
		}

		return num;
	}


	////////////////////////////////////////////////////////////
	void CUString::Trim( char chTarget[])
	{
		TrimLeft( chTarget );
		TrimRight( chTarget );
	}

	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 왼쪽에 chTarget이 있으면 제거
		@param	chTarget	제거할 문자들의 배열
		@see	TrimRight
	*/	
	/////////////////////////////////////////////////////////////
	void CUString::TrimLeft( char chTarget[])
	{
		int target_len = (int)strlen( chTarget );
		if( target_len <= 0 )	return;


		while(1)	{
			bool change = false;

			for( int i=0; i<target_len; i++ )	{

				if( GetLength() <= 0 )	break;
				if( GetAt(0) == chTarget[i] )	{
					Delete( 0 ,1 );				
					change = true;
				}
			}
			
			if( change == false )	break;
		}
	}

	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 오른쪽에 chTarget이 있으면 제거
		@param	chTarget	제거할 문자들의 배열
		@see	TrimLeft
	*/	
	////////////////////////////////////////////////////////////
	void CUString::TrimRight( char chTarget[])
	{
		int target_len = (int)strlen( chTarget );
		if( target_len <= 0 )	return;
		
		while(1)	{
			bool change = false;
			
			for( int i=0; i<target_len; i++ )	{
				
				if( GetLength() <= 0 )	break;
				if( GetAt(GetLength()-1) == chTarget[i] )	{
					Delete( GetLength()-1 ,1 );				
					change = true;
				}
			}
			
			if( change == false )	break;
		}	
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 모든 소문자를 대분자로 변경
		@see	MakeToUpper()
	*/
	////////////////////////////////////////////////////////////
	void CUString::MakeToLower()
	{
		for( int i=0; i<GetLength(); i++ )	{
			SetAt(i, MakeToLowerChar( GetAt(i) ) );
		}
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	String의 모든 대문자를 소분자로 변경
		@see	MakeToLower()
	*/
	////////////////////////////////////////////////////////////
	void CUString::MakeToUpper()
	{
		for( int i=0; i<GetLength(); i++ )	{
			SetAt(i, MakeToUpperChar( GetAt(i) ) );
		}
	}


	////////////////////////////////////////////////////////////
	char CUString::MakeToUpperChar( char ch )
	{
		if( (int)ch >= (int)'a' &&
			(int)ch <= (int)'z' )	{
			return (char)( (int)(ch)-32 );
		}
		return ch;
	}


	////////////////////////////////////////////////////////////
	char CUString::MakeToLowerChar( char ch )
	{
		if( (int)ch >= (int)'A' &&
			(int)ch <= (int)'Z' )	{
			return (char)( (int)(ch)+32 );
		}
		return ch;
	}


	////////////////////////////////////////////////////////////
	bool CUString::IsNumber()
	{
		// atoi return 0 when string is zero
		if( *this == "0" || *this == "0.0" )	return true;

		// in other case, zero means fail
		if( atoi( GetStr() ) == 0) {
			if( atof( GetStr() ) == 0.0 )	{
				return false;
			}
			else {
				return true;
			}
		}
		else {
			return true;
		}
	}


	////////////////////////////////////////////////////////////
	bool CUString::IsASCII()
	{
		for( int i=0; i<GetLength(); i++ )	{
			if( GetAt(i) < 0 )	return false;
		}
		return true;
	}


	////////////////////////////////////////////////////////////
	bool CUString::IsAlpha()
	{
		for( int i=0; i<GetLength(); i++ )	{
			if( GetAt(i) >= 'a' && GetAt(i) <= 'z' )	continue;
			if( GetAt(i) >= 'A' && GetAt(i) <= 'Z' )	continue;
			if( GetAt(i) >= '0' && GetAt(i) <= '9' )	continue;

			if( GetAt(i) < 0 )	return false;
		}
		return true;
	}


	////////////////////////////////////////////////////////////
	void CUString::SetColor( char color[] )
	{
		if( strcmp( color, "black" ) == 0 )	{
			this->SetStr( CUString("\033[30m" ) + GetStr() + CUString("\033[m") );
		}
		else if( strcmp( color, "red" ) == 0 )	{
			this->SetStr( CUString("\033[31m" ) + GetStr() + CUString("\033[m") );
		}
		else if( strcmp( color, "green" ) == 0 )	{
			this->SetStr( CUString("\033[32m" ) + GetStr() + CUString("\033[m") );
		}
		else if( strcmp( color, "brown" ) == 0 )	{
			this->SetStr( CUString("\033[33m" ) + GetStr() + CUString("\033[m") );
		}
		else if( strcmp( color, "blue" ) == 0 )	{
			this->SetStr( CUString("\033[34m" ) + GetStr() + CUString("\033[m") );
		}
		else if( strcmp( color, "magenta" ) == 0 )	{
			this->SetStr( CUString("\033[35m" ) + GetStr() + CUString("\033[m") );
		}
		else if( strcmp( color, "cyan" ) == 0 )	{
			this->SetStr( CUString("\033[36m" ) + GetStr() + CUString("\033[m") );
		}
		else if( strcmp( color, "gray" ) == 0 )	{
			this->SetStr( CUString("\033[37m" ) + GetStr() + CUString("\033[m") );
		}

		else if( strcmp( color, "dark_gray" ) == 0 )	{
			this->SetStr( CUString("\033[01;30m" ) + GetStr() + CUString("\033[m") );
		}
		else if( strcmp( color, "light_red" ) == 0 )	{
			this->SetStr( CUString("\033[01;31m" ) + GetStr() + CUString("\033[m") );
		}
		else if( strcmp( color, "light_green" ) == 0 )	{
			this->SetStr( CUString("\033[01;32m" ) + GetStr() + CUString("\033[m") );
		}
		else if( strcmp( color, "yellow" ) == 0 )	{
			this->SetStr( CUString("\033[01;33m" ) + GetStr() + CUString("\033[m") );
		}
		else if( strcmp( color, "light_blue" ) == 0 )	{
			this->SetStr( CUString("\033[01;34m" ) + GetStr() + CUString("\033[m") );
		}
		else if( strcmp( color, "light_magenta" ) == 0 )	{
			this->SetStr( CUString("\033[01;35m" ) + GetStr() + CUString("\033[m") );
		}
		else if( strcmp( color, "light_cyan" ) == 0 )	{
			this->SetStr( CUString("\033[01;36m" ) + GetStr() + CUString("\033[m") );
		}
		else if( strcmp( color, "white" ) == 0 )	{
			this->SetStr( CUString("\033[01;37m" ) + GetStr() + CUString("\033[m") );
		}
	}


	////////////////////////////////////////////////////////////
	void CUString::FileSizeFormat(unsigned long size,  CUString &str)
	{
		char buf[1024];
		sprintf ( buf, "%ld", size );
		str = buf;

		if( size < 1024 )	{
			sprintf( buf, "%ldB", size);
			str = buf;
		}
		else if( size < 1024 * 1024 )	{
			sprintf( buf, "%1.2fKB", (float)size/1024.0f );
			str = buf;
		}
		else if( size < 1024l * 1024l * 1024l )  {
			sprintf( buf, "%1.2fMB", (float)size/1024.0f/1024.0f );
			str = buf;
		}
		else if( size < 1024l * 1024l * 1024l * 1024l ) {
			sprintf( buf, "%1.2fGB", (float)size/1024.0f/1024.0f/1024.0f );
			str = buf;
		}
		else {
			sprintf( buf, "%1.2fTB", (float)size/1024.0f/1024.0f/1024.0f/1024.0f);
			str = buf;
		}
	}


	////////////////////////////////////////////////////////////
	void CUString::NumberFormat( unsigned long num, CUString &str)
	{
		char buf[1024];
		sprintf( buf, "%ld", num );
		size_t len = strlen( buf );

		char buf2[1024];
		size_t now_len = 0;
		for( size_t i=0; i<len; i++ )	{
			if( (len-i) % 3 == 0 )	{
				if( i != 0 )	{
					buf2[now_len++] = ',';
				}
				buf2[now_len++] = buf[ i ];
			}
			else	{
				buf2[now_len++] = buf[ i ];
			}
		}

		buf2[now_len++] = '\0';
		str = buf2;
	}
}

// EOF

