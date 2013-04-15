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
	CUJsonTreeNode::CUJsonTreeNode()
	{
	}

	////////////////////////////////////////////////////////////
	void CUJsonTreeNode::SetData( char* str )
	{
		label = str;
	}

	////////////////////////////////////////////////////////////
	void CUJsonTreeNode::AddChild( CUJsonTreeNode *child )
	{
		child_list.PushBack( (void*)&child, sizeof(child) );
	}


	////////////////////////////////////////////////////////////
	CUJsonTreeNode* CUJsonTreeNode::GetChild( int idx )
	{
		CUJsonTreeNode *node;
		if( child_list.GetAt(idx, (void*)&node ) == false ) {
			return NULL;
		}
		else {
			return node;
		}
	}


	////////////////////////////////////////////////////////////
	CUJsonTreeNode* CUJsonTreeNode::Find( char *label )
	{
		for( int i=0; i<child_list.GetSize(); i++ )
		{
			CUJsonTreeNode *node;
			if( child_list.GetAt(i, (void*)&node ) == false ) {
				return NULL;
			}

			if( node->label == label )	return node;

		}

		return NULL;
	}


	////////////////////////////////////////////////////////////
	void CUJsonTreeNode::Print( FILE *fp = stderr )
	{
		for( int i=0; i<depth; i++ ) {
			fprintf( fp, "    " );
		}

		fprintf( fp, "[%s] [%s]=[%s] (%s)\n", label.GetStr(), name.GetStr(), value_str.GetStr(), value_type.GetStr() );
	}


	////////////////////////////////////////////////////////////////////
	void CUJsonTree::Print( FILE *fp = stderr, CUJsonTreeNode *root = NULL )
	{
		if( root == NULL )	root = GetRootNode();

		root->Print( fp );
		for( int i=0; i<root->GetNumChild(); i++ )
		{
			Print( fp, root->GetChild(i) );
		}
	}

	////////////////////////////////////////////////////////////////////
	CUJsonTree::CUJsonTree()
	{
	}

	////////////////////////////////////////////////////////////////////
	CUJsonTree::~CUJsonTree()
	{
	}


	////////////////////////////////////////////////////////////////////
	CUJsonTreeNode* CUJsonTree::GetRootNode()
	{
		CUJsonTreeNode *node = NULL;
		if( node_list.GetSize() == 0 )	{
			node = AllocateNode();
			node->label = "ROOT";
			node->value_str = "";
			node->value_type = "";
		}
		else {
			node_list.GetAt(0, (void*)&node );
		}
		return node;
	}

	////////////////////////////////////////////////////////////
	CUJsonTreeNode * CUJsonTree::AddChildNode( CUJsonTreeNode *parent )
	{
		CUJsonTreeNode *node = AllocateNode();
		node->depth = parent->depth+1;
		node->parent = parent;
		parent->AddChild( node );

		return node;
	}


	////////////////////////////////////////////////////////////////////
	CUJsonTreeNode* CUJsonTree::AllocateNode()
	{
		int node_id = node_list.GetSize();
		CUJsonTreeNode *node = new CUJsonTreeNode();
		node->id = node_id;
		node_list.PushBack( (void*)&node, sizeof(node) );

		return node;
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
		lexical.Replace( "___BACK_X__", "\\" );
		lexical.Replace( "___QUOT_X__", "\"" );
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
			tok->lexical.Trim("\"");
			tok->lexical.Replace("\\/", "/" );
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
			return -1;
		}

		return CUList::PushBack( (void*)&tok, sizeof(tok) );
	}

	bool CUJsonParserTokenList::AddToken( char *lexical )
	{
		CUString str = lexical;
		if( this->PushBack( str ) < 0 )	return false;
		return true;
	}

	bool CUJsonParserTokenList::AddToken( CUString &lexical )
	{
		if( this->PushBack( lexical ) < 0 )	return false;
		return true;
	}



	////////////////////////////////////////////////////////////////////
	void CUJsonParserTokenList::Print()
	{
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
				if( token_list.AddToken( token ) == false )	return false;
				pos = end+1;
			}
			else if( ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ',' || ch == ':' ) { 

				char tmp[12];
				sprintf( tmp, "%c", ch );
				if( token_list.AddToken( tmp ) == false )	return false;
				pos++; 
			}
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
				if( token_list.AddToken( token ) == false )	return false;
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
	bool CUJsonParser::Parse( int start_idx=-1, int end_idx=-1, CUJsonTreeNode *root = NULL )
	{
		if( start_idx == -1 ) start_idx = 0;
		if( end_idx == -1 ) end_idx = token_list.GetSize()-1;
		if( root == NULL ) root = tree.GetRootNode();
		if( end_idx< 0 )	return false;;


		for( int i=start_idx; i<=end_idx; i++ ) {
			CUJsonParserToken *token = token_list.GetAt(i);


			if( token->type == ":" ) {
				CUJsonParserToken *token_prev = token_list.GetAt(i-1);
				CUJsonParserToken *token_next = token_list.GetAt(i+1);
				if( token_prev == NULL || token_next == NULL )	return false;

				if( token_next->type == "OBJ_BEGIN" ) {
					CUJsonTreeNode *node = tree.AddChildNode( root );
					node->label = token_prev->lexical;
					node->name = token_prev->lexical;
					node->value_type = "OBJ";
					token->consumed = true;
					token_prev->consumed = true;
					token_next->consumed = true;
					CUJsonParserToken *token_match = token_list.GetAt( token_next->match_idx );
					token_match->consumed = true;
					if( Parse( i+1, token_next->match_idx, node ) == false )	return false;
					i=token_next->match_idx+1;
				}
				else if( token_next->type == "ARR_BEGIN" ) {
					CUJsonTreeNode *node = tree.AddChildNode( root );
					node->label = token_prev->lexical;
					node->name = token_prev->lexical;
					node->value_type = "ARR";
					token->consumed = true;
					token_prev->consumed = true;
					token_next->consumed = true;
					CUJsonParserToken *token_match = token_list.GetAt( token_next->match_idx );
					token_match->consumed = true;
					if( Parse( i+1, token_next->match_idx, node ) == false )	return false;
					i=token_next->match_idx+1;
				}
				else {
					CUJsonTreeNode *node = tree.AddChildNode( root );
					node->label = token_prev->lexical;
					node->name = token_prev->lexical;
					node->value_str = token_next->lexical;
					node->value_type = token_next->type;
					token->consumed = true;
					token_prev->consumed = true;
					token_next->consumed = true;
				}


			}



		}

		// only when final
		if( start_idx == 0 && end_idx == token_list.GetSize()-1 ) {
			for( int i=1; i<token_list.GetSize()-1; i++ ) { // skip the first and last {, }
				CUJsonParserToken *token = token_list.GetAt(i);
				if( token->consumed == false )	{
					if( token->type == "," ) {
						continue;
					}

//					fprintf( stderr, "[%s] %d\n", token->lexical.GetStr() ,i );
				}

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
			
			token_list.Print();
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
		str.Replace( "\\\\", "___BACK_X__" );
		str.Replace( "\\\"", "___QUOT_X__" );
	}


	////////////////////////////////////////////////////////////////////
	bool CUJsonParser::ToString( CUString &ret )
	{
		return true;
	}


	////////////////////////////////////////////////////////////////////
	CUJsonTreeNode *CUJsonParser::GetRootNode()
	{
		return tree.GetRootNode();
	}


	////////////////////////////////////////////////////////////////////
	void CUJsonParser::Print( FILE *fp = stderr )
	{
		tree.Print( fp, GetRootNode() );
	//	token_list.Print();
	}



}

// EOF ㅁ

