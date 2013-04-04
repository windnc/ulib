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
	bool CUJson::Tokenize()
	{
		token_list.Clear();

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
			else if( ch == '[' ) { token_list.PushBack( "[" ); pos++; }
			else if( ch == ']' ) { token_list.PushBack( "]" ); pos++; }
			else if( ch == '{' ) { token_list.PushBack( "{" ); pos++; }
			else if( ch == '}' ) { token_list.PushBack( "}" ); pos++; }
			else if( ch == ',' ) { token_list.PushBack( "," ); pos++; }
			else if( ch == ':' ) { token_list.PushBack( ":" ); pos++; }
			else {
				int start = pos;
				int end = start+1;
				while( true )
				{
					if( end >= str.GetLength() )	return false;
					char ch = str.GetAt(end);

					if( ch == ',' ||  ch == '}' || ch == ']' ) { break; }
					else { end++; }
				}
				pos = end;

				token_list.PushBack( str.SubStr( start, end ) );
			}
		}

		return true;
	}


	int CUJson::FindMatchBraceIdx( int start_idx, int end_idx, int pos )
	{
		int stack=0;
		for( int i=pos; i<end_idx; i++ )
		{
			CUJsonToken *token = token_list.GetAt(i);
			if( token == NULL )	return -1;

			if( token->lexical == "[" )	stack++;
			else if( token->lexical == "]" )	{
				stack--;
				if( stack == 0 )	{
					return i;
				}
			}
		}

		return -1;
	}

	int CUJson::FindMatchCurlBraceIdx( int start_idx, int end_idx, int pos )
	{
		int stack=0;
		for( int i=pos; i<end_idx; i++ )
		{
			CUJsonToken *token = token_list.GetAt(i);
			if( token == NULL )	return -1;

			if( token->lexical == "{" )	stack++;
			else if( token->lexical == "}" )	{
				stack--;
				if( stack == 0 )	{
					return i;
				}
			}
		}

		return -1;
	}


	////////////////////////////////////////////////////////////////////
	bool CUJson::MatchBrace( int start_idx = -1, int end_idx = -1 )
	{
		if( start_idx == -1 )	start_idx = 0;
		if( end_idx == -1 )	end_idx = token_list.GetSize();

		for( int i=start_idx; i<end_idx; i++ )
		{
			CUJsonToken *token = token_list.GetAt(i);
			if( token == NULL )	return false;

			if( token->lexical == "[" ) {
				int match_idx = FindMatchBraceIdx( start_idx, end_idx, i );
				if( match_idx < 0 ) {
					return false;
				}
				token->match_idx = match_idx;
				token_list.GetAt( match_idx ) -> match_idx = i;

				if( MatchBrace( i+1, match_idx ) == false ) {
					return false;
				}

				i = match_idx+1;
			}

			if( token->lexical == "{" ) {
				int match_idx = FindMatchCurlBraceIdx( start_idx, end_idx, i );
				if( match_idx < 0 ) {
					return false;
				}
				token->match_idx = match_idx;
				token_list.GetAt( match_idx ) -> match_idx = i;

				if( MatchBrace( i+1, match_idx ) == false ) {
					return false;
				}

				i = match_idx+1;
			}
		}

		return true;
	}


	////////////////////////////////////////////////////////////////////
	bool CUJson::Load( CUString &_str )
	{
		str = _str;
		Preproc();

		if( Tokenize() == false )
		{
			return false;
		}

		if( MatchBrace() == false )
		{
			return false;
		}

		token_list.Print();

		return true;
	}


	////////////////////////////////////////////////////////////////////
	void CUJson::Preproc()
	{
		str.Replace( "\\\"", "___QUOT_X__" );
	}


	////////////////////////////////////////////////////////////////////
	bool CUJson::ToString( CUString &ret )
	{
		return true;
	}


	////////////////////////////////////////////////////////////////////
	void CUJsonTokenList::Print()
	{
		/*
		for( int i=0; i<CUList::GetSize(); i++ )
		{
			CUJsonToken *token = GetAt(i);
			if( token->lexical == "{" ) {
				fprintf( stdout, "[%d] =>   %s %d\n", i,  token->lexical.GetStr(), token->match_idx  );
			}
			else if( token->lexical == "}" )
			{
				fprintf( stdout, "[%d] =>   %s %d\n", i,  token->lexical.GetStr(), token->match_idx  );
			}
			else if( token->lexical == "[" ) {
				fprintf( stdout, "[%d] => %s %d\n", i,  token->lexical.GetStr(), token->match_idx  );
			}
			else if( token->lexical == "]" )
			{
				fprintf( stdout, "[%d] => %s %d\n", i,  token->lexical.GetStr(), token->match_idx  );
			}
			else {
			//	fprintf( stderr, "[%d] %d   ", i, token->match_idx  );
			}


		}
		fprintf( stderr, "\n" );
		*/

		for( int i=0; i<CUList::GetSize(); i++ )
		{
			CUJsonToken *token = GetAt(i);
				fprintf( stdout, "[%d] %s %d\n", i, token->lexical.GetStr(), token->match_idx );
		}
		fprintf( stdout, "\n" );

	}


	////////////////////////////////////////////////////////////////////
	void CUJsonTokenList::PushBack( CUString str )
	{
		CUJsonToken *token = new CUJsonToken();
		token->lexical = str;
		CUList::PushBack( (void *)&token, sizeof( token ) );
	}


	////////////////////////////////////////////////////////////////////
	CUJsonToken * CUJsonTokenList::GetAt( int i )
	{
		long addr=0;
		if( CUList::GetAt( i, (void *)&addr) == false )	return NULL;

		return (CUJsonToken *)addr;
	}

}

// EOF ㅁ

