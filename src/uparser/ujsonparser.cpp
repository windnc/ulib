/**
	@file		ujsonparser.cpp
	@brief		ujsonparser.cpp
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
	void CUJsonTree::Print( FILE *fp )
	{
		CUTree::Print( fp );
	}


	void CUJsonParserToken::Print()
	{
		fprintf( stderr, "%s (%s) ", lexical.GetStr(), type.GetStr() );
	}


	CUJsonParserToken* CUJsonParserTokenList::GetAt( int i )
	{
		return (CUJsonParserToken*) CUParserTokenList::GetAt(i);
	}

	long CUJsonParserTokenList::PushBack( CUString &lexical )
	{
		lexical.Replace( "___QUOT_X__", "\\\"" );
		CUJsonParserToken *tok = new CUJsonParserToken();
		tok->lexical = lexical;

		if( lexical == "{" ) {
			tok->type = "OBJ_BEGIN";
		}
		else if( lexical == "}" ) {
			tok->type = "OBJ_END";
		}
		else if( lexical == "[" ) {
			tok->type = "ARR_BEGIN";
		}
		else if( lexical == "]" ) {
			tok->type = "ARR_END";
		}
		else if( lexical == ":" ) {
			tok->type = ":";
		}
		else if( lexical == "," ) {
			tok->type = ",";
		}
		else if( lexical.GetAt(0) == '\"' ) {
			tok->type = "STRING";
		}
		else if( lexical == "true" || lexical == "false" ) {
			tok->type = "BOOL";
		}
		else if( lexical == "null" ) {
			tok->type = "NULL";
		}
		else if( lexical.IsNumber() == true ) {
			tok->type = "NUM";
		}
		else {
			tok->type = "UNKNOWN";
			fprintf( stderr, "[ERROR] lexical recognize fail: [%s]\n", lexical.GetStr() );
		}

		return CUList::PushBack( (void*)&tok, sizeof(tok) );
	}

	void CUJsonParserTokenList::AddToken( char *lexical )
	{
		CUString str = lexical;
		this->PushBack( str );
	}

	void CUJsonParserTokenList::AddToken( CUString &lexical )
	{
		this->PushBack( lexical );
	}




	////////////////////////////////////////////////////////////////////
	void CUJsonParserTokenList::Print()
	{

		for( int i=0; i<GetSize(); i++ )
		{
			CUJsonParserToken *token = GetAt(i);
			if( token != NULL )
			{
				if( token->type == "STRING" )
				{
					CUJsonParserToken *token2 = GetAt(i+1);
					if( token2 != NULL )
					{
						if( token2->type == ":" )
						{

							CUJsonParserToken *token3 = GetAt(i+2);
							if( token3 != NULL )
							{
								if( token3->type == "STRING" ||
								    token3->type == "NUM" ||
								    token3->type == "NULL" ||
								    token3->type == "BOOL" )
								{
									for( int j=0; j<token->level; j++ )
									{
										fprintf( stderr, "   " );
									}

									fprintf( stderr, "[%d] %s -> %s\n", i,
											token->lexical.GetStr(),
											token3->lexical.GetStr() );
									i+=2;
								}
							}
						}
					}
				}
			}
		}
		fprintf( stderr, "\n" );
		return;

		for( int i=0; i<GetSize(); i++ )
		{
			CUJsonParserToken *token = GetAt(i);
			if( token != NULL )
			{
				fprintf( stderr, "[%d] ", i );
				token->Print();
			}
		}
		fprintf( stderr, "\n" );

	}



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
				CUString token = str.SubStr( start, end+1 );
				token_list.AddToken( token );
				pos = end+1;
			}
			else if( ch == '[' ) { token_list.AddToken( "[" ); pos++; }
			else if( ch == ']' ) { token_list.AddToken( "]" ); pos++; }
			else if( ch == '{' ) { token_list.AddToken( "{" ); pos++; }
			else if( ch == '}' ) { token_list.AddToken( "}" ); pos++; }
			else if( ch == ',' ) { token_list.AddToken( "," ); pos++; }
			else if( ch == ':' ) { token_list.AddToken( ":" ); pos++; }
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

				CUString token = str.SubStr( start, end );
				token_list.AddToken( token );
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

			if( token->lexical == "[" ) {
				int match_idx = FindMatchBraceIdx( start_idx, end_idx, i );
				if( match_idx < 0 ) {
					fprintf( stderr, "match fail %d -> ?\n", i );
					return false;
				}
				token->match_idx = match_idx;
				token_list.GetAt( match_idx ) -> match_idx = i;

				if( MatchBrace( i+1, match_idx-1 ) == false ) {
					return false;
				}

				i = match_idx+1;
			}

			if( token->lexical == "{" ) {
				int match_idx = FindMatchCurlBraceIdx( start_idx, end_idx, i );
				if( match_idx < 0 ) {
					fprintf( stderr, "match fail %d -> ?\n", i );
					return false;
				}
				token->match_idx = match_idx;
				token_list.GetAt( match_idx ) -> match_idx = i;
				for( int j=i+1; j<=match_idx-1; j++ ) {
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
				CUJsonParserToken *token = token_list.GetAt(i);
				if( token->lexical == "]" ) {
					int j=token->match_idx;

					fprintf( stderr, "%d ~ %d [] \n", j, i );
				}

			}

			return false;


		/*
		for( int i=start_idx; i<=end_idx; i++ )
		{
			CUJsonParserToken *token1 = token_list.GetAt( i );
			if( token1->match_idx != -1 ) {
				CUTreeNode *child = tree.AddChildNode( root );
			}
			else {
				CUJsonParserToken *token2 = token_list.GetAt(i+1);
				CUTreeNode *child = tree.AddChildNode( root );
			//	child->lexical =  token2->lexical;
				i++;
			}

		}
		*/

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


	////////////////////////////////////////////////////////////////////
	void CUJsonParser::Print( FILE *fp )
	{
	//	tree.Print( fp );
		token_list.Print();
	}



}

// EOF ㅁ

