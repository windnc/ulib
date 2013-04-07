/**
	@file		uparser.cpp
	@brief		uparser.cpp
	@author		swlee
	@date		Apr. 4, 2013
	@version	0.0.1
	@todo		
	@warning	
	@bug		
	@note		
*/
#include "uparser.h"

namespace ulib {

	////////////////////////////////////////////////////////////////////
	void CUParserTokenList::PushBack( CUString str )
	{
		CUParserToken *token = new CUParserToken();
		token->lexical = str;
		CUList::PushBack( (void *)&token, sizeof( token ) );
	}


	////////////////////////////////////////////////////////////////////
	CUParserToken * CUParserTokenList::GetAt( int i )
	{
		long addr=0;
		if( CUList::GetAt( i, (void *)&addr) == false )	return NULL;

		return (CUParserToken *)addr;
	}


	////////////////////////////////////////////////////////////////////
	void CUParserTokenList::Print()
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
			CUParserToken *token = GetAt(i);
			fprintf( stdout, "[%4d]", i );
			for( int j=0; j<token->level; j++ ) {
				fprintf( stdout, "    " );
			}
			//fprintf( stdout, "[%d] %s %d\n", i, token->lexical.GetStr(), token->match_idx );
			fprintf( stdout, "%s   <%d>\n", token->lexical.GetStr(), token->match_idx );
		}
		fprintf( stdout, "\n" );

	}
	////////////////////////////////////////////////////////////////////
	CUParser::CUParser()
	{
	}

	////////////////////////////////////////////////////////////////////
	CUParser::~CUParser()
	{
	}


	////////////////////////////////////////////////////////////////////
	bool CUParser::ToString( CUString &ret )
	{
		return true;
	}
}

// EOF ㅁ

