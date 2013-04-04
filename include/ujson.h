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



	class CUJson: public CUParser  {
	public:
		CUJson();
		~CUJson();
	public:

		virtual bool Load( CUString &str );
		virtual bool ToString( CUString &ret );

		bool Tokenize( CUString &str, CUStringList &token_list );
		bool Parse( CUStringList &token_list, CUJsonContainer *container, int start_idx, int end_idx );
		CUJsonContainer container;

	public:
		CUString str;
		
	private:


	private:


	};

}

#endif

// EOF ㅁ

