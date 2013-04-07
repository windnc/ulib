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
		bool Parse( int start_idx, int end_idx, CUTreeNode *root );

	public:
		CUString str;
		
	private:
		void Preproc();
		int FindMatchBraceIdx( int start_idx, int end_idx, int pos ); 
		int FindMatchCurlBraceIdx( int start_idx, int end_idx, int pos ); 

	private:


	};

}

#endif

// EOF ㅁ

