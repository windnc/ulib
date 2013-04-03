/**
	@file		ustringlist.cpp
	@brief		ustringlist cpp
	@author		이승욱
	@date		08.05.06
	@version	0.5
	@todo		???
	@warning	???
	@bug		???
*/
#include "ustringlist.h"

namespace ulib
{

	////////////////////////////////////////////////////////////
	/**
		@brief	생성자
	*/
	////////////////////////////////////////////////////////////
	CUStringList::CUStringList(  )	
	{
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
		for( size_t i=0; i<GetSize(); i++ )	{
			if( i > 0 )	{
				fprintf( fp, "%s", delimeter );
			}
			fprintf( fp, "%s", GetAt(i) );
		}
	}


	////////////////////////////////////////////////////////////
	void CUStringList::PrintEx( FILE *fp, char delimeter[] )
	{
		for( size_t i=0; i<GetSize(); i++ )	{
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
	size_t CUStringList::GetSize()
	{
		return list.GetSize();
	}


	////////////////////////////////////////////////////////////
	int CUStringList::Find( char str[] )
	{
		for( size_t i=0; i<GetSize(); i++ )	{
			if( strcmp( GetAt(i), str ) == 0)	return i;
		}
		return -1;
	}


	////////////////////////////////////////////////////////////
	void CUStringList::PushFront( const CUString &arg_str )
	{
		CUString *str = new CUString( arg_str );
		list.PushFront( (void*)&str, sizeof(str) );
	}


	////////////////////////////////////////////////////////////
	void CUStringList::PushBack( const CUString &arg_str )
	{
		CUString *str = new CUString( arg_str );
		list.PushBack( (void*)&str, sizeof(str) );
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
		if( !list.PopBack( (void *)&addr ) )	{
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
		if( !list.PopFront( (void *)&addr ) )	{
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
		if( !list.PopAt( nPos, (void*)&addr ) )	{
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
		if( !list.PopAt( nPos, (void*)&addr ) )	{
			return false;
		}

		return true;
	}


	////////////////////////////////////////////////////////////
	CUString CUStringList::ToString( char delimeter[] )
	{
		CUString ret_str;
		for( size_t i=0; i<GetSize(); i++ )	{
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
	char *CUStringList::GetAt( int nPos )
	{
		long addr;
		if( !list.GetAt( nPos, (void *)&addr ) )	{
			return NULL;
		}
		CUString *find_str = (CUString *)addr;

		return find_str->GetStr();
	}


	////////////////////////////////////////////////////////////
	bool CUStringList::SetAt( int nPos, CUString &str )
	{
		long addr;
		if( !list.GetAt( nPos, (void *)&addr ) )	{
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
	bool CUStringList::GetAt( int nPos, CUString &ret_str )
	{
		long addr;
		if( !list.GetAt( nPos, (void *)&addr ) )	{
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
		for( size_t i=0; i<list1.GetSize(); i++ )	{
			if( list2.Find( list1.GetAt(i) ) < 0 )	{
			}
			else	{
				PushBack( list1.GetAt(i) );
			}
		}
	}

}

// EOF
