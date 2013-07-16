/**
	@file		ustringlist.cpp
	@brief		ustringlist cpp
	@author		swlee
	@date		May. 6, 2008 ~
	@version	0.5
	@todo		
	@warning	
	@bug		
*/
#include "ustringlist.h"

namespace ulib
{

	////////////////////////////////////////////////////////////
	/**
		@brief	생성자
	*/
	////////////////////////////////////////////////////////////
	CUStringList::CUStringList()	
	{
	}

	CUStringList::CUStringList(const CUStringList &src )
	{
		for( int i=0; i<src.GetSize(); i++ ) {
			this->PushBack( src.GetAt(i) );
		}
	}

	/////////////////////////////////////////////////////////////
	CUStringList& CUStringList::operator=(CUStringList &rhs )
	{
		this->Clear();
		for( int i=0; i<rhs.GetSize(); i++ ) {
			this->PushBack( rhs.GetAt(i) );
		}
		return *this;
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	생성자
		@param	str	초기 문자열
		@param	delimeter	 초기 문자열을 나눌 문자들
	*/
	/////////////////////////////////////////////////////////////
	CUStringList::CUStringList( CUString str, CUString delimeter )
	{
		TokenizeByChar( str, delimeter );
	}


	////////////////////////////////////////////////////////////
	void CUStringList::TokenizeByChar( CUString str, CUString delimeter, bool permit_empty )
	{
		Clear();
		/*
		int prev = 0;
		for( int i=0; i< str.GetLength(); i++ )	{
			if( delimeter.Find( str.GetAt(i) ) >= 0 )	{
				PushBack( str.SubStr( prev, i ) );
				i++;
				prev = i;
			}
		}
		*/
		while( true )	{
			
			bool change = false;
			for( int i=0; i<str.GetLength(); i++ )	{
				if( delimeter.Find( str.GetAt(i) ) >= 0 )	{
					if( str.Left( i ).IsEmpty() ) 	{
						if( permit_empty )	{
							PushBack( str.Left( i ) );
						}
					}
					else	{
						PushBack( str.Left( i ) );
					}
					str = str.Mid( i+1 );
					
					change = true;
					break;
				}
			}
			if( change == false )	break;
		}

		if( str.IsEmpty()) {
			if( permit_empty )	{	
				PushBack( str );
			}
		}
		else {
			PushBack( str );
		}
	}


	////////////////////////////////////////////////////////////
	void CUStringList::TokenizeByStr( CUString str, CUString delimeter, bool permit_empty )
	{
		Clear();
		while(1)	{
			int idx = str.Find( delimeter.GetStr() );
			if(  idx < 0 )	break;
			if( str.Left( idx ).IsEmpty() )	{
				if( permit_empty == true )	{
					PushBack( str.Left( idx ) );
				}
			}
			else {
				PushBack( str.Left( idx ) );
			}
			str = str.Mid( idx + delimeter.GetLength() );
		}
		if( str.IsEmpty()) {
			if( permit_empty )	{	
				PushBack( str );
			}
		}
		else {
			PushBack( str );
		}
	}


	////////////////////////////////////////////////////////////
	void CUStringList::TokenizeByBoundTag( CUString str, CUString open_tag, CUString end_tag, bool permit_empty )
	{
		Clear();
		int start_idx = -1;
		while(1)	{
			int idx = str.Find( open_tag.GetStr(), start_idx+1 );
			if(  idx < 0 )	break;
			int idx2 = str.Find( end_tag.GetStr(), idx+1 );
			if( idx2 < 0 )	break;

			if( idx2 == idx + open_tag.GetLength() )	{
				if( permit_empty == true )	{
					PushBack( "" );
				}
			}
			else {
				PushBack( str.SubStr( idx + open_tag.GetLength(),  idx2  ) );
			}
			start_idx = idx2+end_tag.GetLength()-1;
		}
	}


	////////////////////////////////////////////////////////////
	void CUStringList::Print( FILE *fp, char delimeter[] )
	{
		for( int i=0; i<GetSize(); i++ )	{
			if( i > 0 )	{
				fprintf( fp, "%s", delimeter );
			}
			fprintf( fp, "%s", GetAt(i) );
		}
	}


	////////////////////////////////////////////////////////////
	void CUStringList::PrintEx( FILE *fp, char delimeter[] )
	{
		for( int i=0; i<GetSize(); i++ )	{
			if( i > 0 )	{
				fprintf( fp, "%s", delimeter );
			}
			fprintf( fp, "[%d]%s",(int)i, GetAt(i) );
		}
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	소멸자
	*/
	////////////////////////////////////////////////////////////
	CUStringList::~CUStringList()
	{
		Clear();
	} 


	////////////////////////////////////////////////////////////
	void CUStringList::Clear()
	{
		while( 1 )	{
			CUString str;
			if( !PopFront( str ) )	break;		
		}
	}


	////////////////////////////////////////////////////////////
	int CUStringList::Find( char str[] )
	{
		for( int i=0; i<GetSize(); i++ )	{
			if( strcmp( GetAt(i), str ) == 0)	return i;
		}
		return -1;
	}


	////////////////////////////////////////////////////////////
	void CUStringList::PushFront( const CUString &arg_str )
	{
		CUString *str = new CUString( arg_str );
		CUList::PushFront( (void*)&str, sizeof(str) );
	}


	////////////////////////////////////////////////////////////
	void CUStringList::PushBack( const CUString &arg_str )
	{
		CUString *str = new CUString( arg_str );
		CUList::PushBack( (void*)&str, sizeof(str) );
	}


	////////////////////////////////////////////////////////////
	void CUStringList::RemoveFront()
	{
		CUString str;
		PopFront( str );
	}


	////////////////////////////////////////////////////////////
	void CUStringList::RemoveBack()
	{
		CUString str;
		PopBack( str );
	}


	////////////////////////////////////////////////////////////
	bool CUStringList::IsEmpty()
	{
		if( GetSize() == 0 )	return true;
		else return false;
	}


	////////////////////////////////////////////////////////////
	bool CUStringList::PopBack( CUString &ret_str )
	{
		long addr;
		if( CUList::PopBack( (void *)&addr ) == false )	{
			return false;
		}

		CUString *find_str = (CUString *)addr;
		ret_str.SetStr( find_str->GetStr() );

		delete find_str;
		return true;
	}


	////////////////////////////////////////////////////////////
	bool CUStringList::PopFront( CUString &ret_str )
	{
		long addr;
		if( CUList::PopFront( (void *)&addr ) == false )	{
			return false;
		}

		CUString *find_str = (CUString *)addr;
		ret_str.SetStr( find_str->GetStr() );

		delete find_str;
		return true;
	}


	////////////////////////////////////////////////////////////
	bool CUStringList::PopAt( int nPos, CUString &ret_str )
	{
		long addr;
		if( CUList::PopAt( nPos, (void*)&addr ) == false )	{
			return false;
		}

		CUString *find_str = (CUString *)addr;
		ret_str.SetStr( find_str->GetStr() );

		delete find_str;
		return true;
	}


	////////////////////////////////////////////////////////////
	bool CUStringList::PopAt( int nPos )
	{
		long addr;
		if( CUList::PopAt( nPos, (void*)&addr ) == false  )	{
			return false;
		}

		return true;
	}


	////////////////////////////////////////////////////////////
	CUString CUStringList::ToString( char delimeter[] )
	{
		CUString ret_str;
		for( int i=0; i<GetSize(); i++ )	{
			if( i == 0)	{
				ret_str += GetAt(i);
			}
			else	{
				ret_str += CUString(delimeter) + GetAt(i);
			}
		}
		return ret_str;
	}


	////////////////////////////////////////////////////////////
	char *CUStringList::GetAt( int nPos ) const
	{
		long addr;
		if( CUList::GetAt( nPos, (void *)&addr ) == false )	{
			return NULL;
		}
		CUString *find_str = (CUString *)addr;

		return find_str->GetStr();
	}


	////////////////////////////////////////////////////////////
	bool CUStringList::SetAt( int nPos, CUString &str )
	{
		long addr;
		if( CUList::GetAt( nPos, (void *)&addr ) == false )	{
			return false;
		}
		CUString *p = (CUString *)addr;
		*p = str;

		return true;
	}


	////////////////////////////////////////////////////////////
	bool CUStringList::SetAt( int nPos, char *str )
	{
		CUString s = str;
		return SetAt( nPos, s );
	}


	////////////////////////////////////////////////////////////
	bool CUStringList::GetAt( int nPos, CUString &ret_str ) const
	{
		long addr;
		if( CUList::GetAt( nPos, (void *)&addr ) == false )	{
			return false;
		}

		CUString *find_str = (CUString *)addr;
		ret_str.SetStr( find_str->GetStr() );

		return true;
	}


	////////////////////////////////////////////////////////////
	void CUStringList::GetIntersection( CUStringList &list1, CUStringList &list2 )
	{
		Clear();
		for( int i=0; i<list1.GetSize(); i++ )	{
			if( list2.Find( list1.GetAt(i) ) < 0 )	{
			}
			else	{
				PushBack( list1.GetAt(i) );
			}
		}
	}

}

// EOF ㅁ

