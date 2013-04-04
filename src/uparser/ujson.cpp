/**
	@file		ujson.cpp
	@brief		ujson.cpp
	@author		swlee
	@date		Apr. 4, 2013
	@version	0.0.1
	@todo		
	@warning	
	@bug		
	@note		
*/
#include "ulib.h"
#include "ujson.h"

namespace ulib {

	////////////////////////////////////////////////////////////////////
	CUJson::CUJson()
	{
		this->container.name = "ROOT";
	}

	////////////////////////////////////////////////////////////////////
	CUJson::~CUJson()
	{
	}


	////////////////////////////////////////////////////////////////////
	bool CUJson::Tokenize( CUString &str, CUStringList &token_list )
	{
		token_list.Clear();

		str.Replace( "\\\"", "___QUOT_X__" );

		int pos = 0;
		while( true )
		{
			if( pos >= str.GetLength() )	break;
			char ch = str.GetAt(pos);

			if( ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' )
			{
				pos++;
			}
			else if( ch == '\"' ) {
				int start = pos;
				int end = str.Find("\"", pos+1 );
				if( end < 0 )	return false;
				token_list.PushBack( str.SubStr( start, end+1 ) );
				pos = end+1;
			}
			else if( ch == '{' ) {
				token_list.PushBack( "{" );
				pos++;
			}
			else if( ch == '}' ) {
				token_list.PushBack( "}" );
				pos++;
			}
			else if( ch == ',' ) {
				token_list.PushBack( "," );
				pos++;
			}
			else if( ch == ':' ) {
				token_list.PushBack( ":" );
				pos++;
			}
			else {
				int start = pos;
				int end = start+1;
				while( true )
				{
					if( end >= str.GetLength() )	return false;
					char ch = str.GetAt(end);

					if( ch == ',' ||  ch == '}' ) {
						break;
					}
					else {
						end++;
					}
				}
				pos = end;

				token_list.PushBack( str.SubStr( start, end ) );
			}
		}

		return true;
	}

	int FindMatchBrace( CUStringList &token_list, int start_idx, int end_idx, int pos )
	{
		int stack=0;
		for( int i=pos; i<end_idx; i++ )
		{
			CUString token = token_list.GetAt(i);
			if( token == "{" )	stack++;
			else if( token == "}" )	{
				stack--;
				if( stack == 0 )	{
					return i;
				}
			}
		}

		return -1;
	}


	////////////////////////////////////////////////////////////////////
	bool CUJson::Parse( CUStringList &token_list, CUJsonContainer *container = NULL, int start_idx = -1, int end_idx = -1 )
	{
		if( start_idx == -1 )	start_idx = 0;
		if( end_idx == -1 )	end_idx = token_list.GetSize();
		if( container == NULL )	container = &(this->container);

//		fprintf( stderr, "%s [%d] ~ [%d]\n", container->name.GetStr(), start_idx, end_idx );
	//	token_list.PrintEx( stderr, " " );
	//	fprintf( stderr, "\n" );

		for( int i=start_idx; i<end_idx; i++ )
		{
			CUString token = token_list.GetAt(i);
			if( token == "{" ) {
				int match_idx = FindMatchBrace( token_list, start_idx, end_idx, i );
				if( match_idx < 0 ) {
					fprintf( stderr, "@@ fail to match %d from %d~%d\n", i, start_idx, end_idx );
					return false;
				}

				CUString key = "_main";
				if( i > 2 )	{
					key = token_list.GetAt(i-2);
				}

				CUJsonContainer *sub_container = new CUJsonContainer();
				sub_container->name = key;

				if( Parse( token_list, sub_container, i+1, match_idx ) == false )
				{
					return false;
				}

				i = match_idx+1;
			}
			else {
				CUString key = token_list.GetAt(i);
				i++;
				i++;
				CUString value = token_list.GetAt(i);
				i++;

				fprintf( stderr, "[%s] = [%s]    ", key.GetStr(), value.GetStr() );
//				fprintf( stderr, "[%s] ", key.GetStr() );

//				CUString value = token_list.GetAt(i+2);
			}
		}

		return true;
	}

	////////////////////////////////////////////////////////////////////
	bool CUJson::Load( CUString &_str )
	{
		str = _str;

		CUStringList token_list;
		if( Tokenize( str, token_list ) == false )
		{
			return false;
		}
		if( Parse( token_list ) == false )
		{
			return false;
		}

		return true;
	}


	////////////////////////////////////////////////////////////////////
	bool CUJson::ToString( CUString &ret )
	{
		return true;
	}
}

// EOF ㅁ

