#ifndef ___ucounter___
#define ___ucounter___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <string>
#include <map>
#include <list>


namespace ulib {

	/**
		@file		ucounter.h
		@brief		ucounter header
		@author		이승욱
		@date		08.11.23
		@version	0.0.1
		@todo		
		@warning	???
		@bug		???
		@note		Release0.0
	*/
	class CUCounter {
	public:
		CUCounter();
		unsigned long GetNumItem();
		unsigned long GetTotalCount();
		void AddItem( char *item, unsigned long num = 1 );
		void AddItem( long item, unsigned long num = 1 );
		bool GetCount( char *item, unsigned long &ret );
		void Print( FILE *fp, char mode[]="IC", char sort='I' );

		std::map<std::string, unsigned long> str_cnt_map;

	private:
		unsigned long total_count;

		typedef class _str_cnt {
			public:
				std::string str;
				unsigned long cnt;
				_str_cnt( std::string arg_str, unsigned long arg_cnt )	{
					str = arg_str;
					cnt = arg_cnt;
				}

		} CStrCnt;

		typedef class _str_cnt_less {
			public:
				bool operator() ( const CStrCnt &a, const CStrCnt &b ) const	{
					return a.cnt > b.cnt;
				}
		} CStrCntSort; 
	};
}

#endif

