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
#include "ujsonparser.h"

namespace ulib {

	////////////////////////////////////////////////////////////////////
	CUJsonParser::CUJsonParser()
	{
	}

	////////////////////////////////////////////////////////////////////
	CUJsonParser::~CUJsonParser()
	{
	}


	////////////////////////////////////////////////////////////////////
	bool CUJsonParser::Tokenize()
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


	int CUJsonParser::FindMatchBraceIdx( int start_idx, int end_idx, int pos )
	{
		int stack=0;
		for( int i=pos; i<=end_idx; i++ )
		{
			CUParserToken *token = token_list.GetAt(i);
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

	int CUJsonParser::FindMatchCurlBraceIdx( int start_idx, int end_idx, int pos )
	{
		int stack=0;
		for( int i=pos; i<=end_idx; i++ )
		{
			CUParserToken *token = token_list.GetAt(i);
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
	bool CUJsonParser::MatchBrace( int start_idx = -1, int end_idx = -1 )
	{
		if( start_idx == -1 )	start_idx = 0;
		if( end_idx == -1 )	end_idx = token_list.GetSize()-1;


		for( int i=start_idx; i<=end_idx; i++ )
		{
			CUParserToken *token = token_list.GetAt(i);
			if( token == NULL ) { 
				fprintf( stderr, "out of boundary\n" );
				return false;
			}

			if( token->lexical == "{" ) {
				int match_idx = FindMatchCurlBraceIdx( start_idx, end_idx, i );
				if( match_idx < 0 ) {
					fprintf( stderr, "match fail %d -> ?\n", i );
					return false;
				}
				token->match_idx = match_idx;
				token_list.GetAt( match_idx ) -> match_idx = i;
				for( int j=i+1; j<=match_idx-1; j++ )
				{
					token_list.GetAt(j)->level++;
				}

				if( MatchBrace( i+1, match_idx-1 ) == false ) {
					return false;
				}

				i = match_idx+1;
			}
		}

		return true;
	}


	////////////////////////////////////////////////////////////////////
	bool CUJsonParser::Parse( int start_idx=-1, int end_idx=-1, CUTreeNode *root = NULL )
	{
		if( start_idx == -1 ) start_idx = 0;
		if( end_idx == -1 ) end_idx = token_list.GetSize()-1;
		if( root == NULL ) root = tree.GetRootNode();

		for( int i=start_idx; i<=end_idx; i++ )
		{
			CUParserToken *token1 = token_list.GetAt( i );
			if( token1->match_idx != -1 ) {
				CUTreeNode *child = tree.AddChildNode( root );
			}
			else {
			}

		}

		return true;
	}


	////////////////////////////////////////////////////////////////////
	bool CUJsonParser::Load( CUString &_str )
	{
		str = _str;
		Preproc();

		if( Tokenize() == false ) {
			return false;
		}

		if( MatchBrace() == false ) {
			return false;
		}

		if( Parse() == false ) {
			return false;
		}

		tree.Print( stdout );
//		token_list.Print();

		return true;
	}


	////////////////////////////////////////////////////////////////////
	void CUJsonParser::Preproc()
	{
		str.Replace( "\\\"", "___QUOT_X__" );
	}


	////////////////////////////////////////////////////////////////////
	bool CUJsonParser::ToString( CUString &ret )
	{
		return true;
	}


	////////////////////////////////////////////////////////////////////
	CUJsonNode *CUJsonParser::GetRootNode()
	{
		return NULL;
	}

}

// EOF ㅁ

