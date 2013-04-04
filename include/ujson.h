/*
	작성자	:	swlee
	작성일	:	Apr. 4, 2013
	버전	:	0.1.0
	설명	:	
	미구현	:	
	버그	:	
*/

#ifndef ___ujson___
#define ___ujson___

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "uparser.h"
#include "ustring.h"


namespace ulib {

	class CUJsonContainer;
	class CUJsonItem{
	public:

		CUString key;
		CUString value;
		CUJsonContainer *value2;

		CUJsonItem() {
			value2 = NULL;
		}
	};
	typedef map<string, CUJsonItem> item_map_t;
	class CUJsonContainer {
	public:
		CUString name;
		item_map_t item_map;
	};


	class CUJsonToken {
	public:
		CUString lexical;
		CUString type;
		int match_idx;
		CUJsonToken()
		{
			match_idx=-1;
		}
	};


	//////////////////////////////////////////////
	class CUJsonTokenList : public CUList {
	public:
		void PushBack( CUString str );
		CUJsonToken *GetAt( int i );
		void Print();
	};


	///////////////////////////////////////////
	class CUJson: public CUParser  {
	public:
		CUJson();
		~CUJson();
	public:

		virtual bool Load( CUString &str );
		virtual bool ToString( CUString &ret );

		bool Tokenize();
		bool MatchBrace( int start_idx, int end_idx );
		bool Parse();

	public:
		CUString str;
		CUJsonTokenList token_list;
		CUJsonContainer container;
		
	private:
		void Preproc();
		int FindMatchBraceIdx( int start_idx, int end_idx, int pos ); 
		int FindMatchCurlBraceIdx( int start_idx, int end_idx, int pos ); 

	private:


	};

}

#endif

// EOF ㅁ

