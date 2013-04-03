/**
	@file		ucounter.cpp
	@brief		ucounter.cpp
	@author		이승욱
	@date		08.11.23
	@version	0.0.1
	@todo		
	@warning	???
	@bug		???
	@note		
*/
#include "ucounter.h"

namespace ulib {

	////////////////////////////////////////////////////////////////////
	inline CUCounter::CUCounter()
	{
		total_count = 0;
	}


	////////////////////////////////////////////////////////////////////
	inline unsigned long CUCounter::GetNumItem()
	{
		return str_cnt_map.size();
	}

	////////////////////////////////////////////////////////////////////
	inline unsigned long CUCounter::GetTotalCount()
	{
		return total_count;
	}

	////////////////////////////////////////////////////////////////////
	void CUCounter::AddItem( long item, unsigned long num )
	{
		char buf[64];
		sprintf( buf, "%ld", item );
		AddItem( buf, num );
	}


	////////////////////////////////////////////////////////////////////
	void CUCounter::AddItem( char * item, unsigned long num )
	{
		std::map<std::string, unsigned long>::iterator itr;
		itr = str_cnt_map.find( item );
		if( itr == str_cnt_map.end() )	{
			str_cnt_map[ item ] = num;
		}
		else	{
			(itr->second)+=num;
		}

		total_count += num;
	}


	////////////////////////////////////////////////////////////////////
	bool CUCounter::GetCount( char *item, unsigned long &ret )
	{
		std::map<std::string, unsigned long>::iterator itr;
		itr = str_cnt_map.find( item );
		if( itr == str_cnt_map.end() )	return false;

		ret = itr->second;
		return true;
	}


	////////////////////////////////////////////////////////////////////
	void CUCounter::Print( FILE *fp, char mode[], char sort )
	{
		bool print_count = false;
		bool print_ratio = false;
		if( strcmp( mode, "I" ) == 0 )	{
		}
		else if( strcmp( mode, "IC" ) == 0 )	{
			print_count = true;
		}
		else if( strcmp( mode, "IR" ) == 0 )	{
			print_ratio = true;
		}
		else if( strcmp( mode, "ICR" ) == 0 || strcmp( mode, "IRC") == 0 )	{
			print_count = true;
			print_ratio = true;
		}

		// sort by count
		if( sort == 'C' )	{
			std::map<std::string, unsigned long>::iterator itr;
			itr = str_cnt_map.begin();
			std::list<CStrCnt> str_cnt_list;
			while( itr != str_cnt_map.end() )	{
				CStrCnt new_node( itr->first, itr->second );
				str_cnt_list.push_back( new_node );
				itr++;
			}
			
			str_cnt_list.sort( CStrCntSort() );

			std::list<CStrCnt>::iterator itr2;
			itr2 = str_cnt_list.begin();
			while( itr2 != str_cnt_list.end() ) {


				fprintf( fp, "%s", itr2->str.c_str() );
				if( print_ratio )	{
					fprintf( fp, "\t%1.8e", (double)itr2->cnt/(double)GetTotalCount() );
				}
				if( print_count )	{
					fprintf( fp, "\t%lu", itr2->cnt );
				}
				fprintf( fp, "\n" );
				itr2++;
			}

		}

		else	{
			std::map<std::string, unsigned long>::iterator itr;
			itr = str_cnt_map.begin();
			while( itr != str_cnt_map.end() )	{
				fprintf( fp, "%s", itr->first.c_str() );
				if( print_count )	{
					fprintf( fp, "\t%lu", itr->second );
				}
				if( print_ratio )	{
					fprintf( fp, "\t%1.8e", (double)itr->second/(double)GetTotalCount() );
				}
				fprintf( fp, "\n" );

				itr++;
			}
		}
	}

}

// EOF
