/*
	작성자	:	swlee
	작성일	:	Apr. 4, 2013
	버전	:	0.1.0
	설명	:	
	미구현	:	
	버그	:	
*/

#ifndef ___uparser___
#define ___uparser___

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ustring.h"
#include "utree.h"


namespace ulib {


	//////////////////////////////////////////////
	class CUParserToken {
	public:
		CUString lexical;
		CUString type;
		int match_idx;
		int level;
		bool consumed;

		CUParserToken()
		{
			match_idx=-1;
			level=0;
			consumed = false;
		}
	};


	//////////////////////////////////////////////
	class CUParserTokenList : public CUList {
	public:
		void PushBack( CUString str );
		CUParserToken *GetAt( int i );
		void Print();
	};


	//////////////////////////////////////////////
	class CUParser {
	public:
		CUParser();
		~CUParser();

	public:
		virtual bool ToString( CUString &ret ) = 0;
		virtual bool Tokenize() = 0;
		virtual CUTreeNode *GetRootNode() = 0;

	public:
		CUString str;
		CUParserTokenList token_list;
		CUTree tree;

	};

}

#endif

// EOF ㅁ

