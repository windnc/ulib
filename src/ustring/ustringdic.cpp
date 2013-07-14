/**
	@file		ustringdic.cpp
	@brief		ustringdiccpp
	@author		swlee
	@date		July. 11, 2013 ~
	@version	0.1
	@todo		
	@warning	
	@bug		
*/
#include "ustringdic.h"

namespace ulib
{

	/*
	bool SortDicEntry( const CUStringDicEntry &a, const CUStringDicEntry &b ) {
		CUString str1 = a.key;
		char *str11 = str1.GetStr();
		CUString str2 = b->key;
		char *str22 = str2.GetStr();
		return strcmp( str11, str22 ) < 0;
		//return strcmp( (const)a.key.GetStr(), (const)b.key.GetStr() ) < 0;
		//return strcmp( (const char*)a.key.GetStr(), (const char*)b.key.GetStr() ) < 0;
	}
	*/
	bool SortDicEntry2( CUStringDicEntry *a, CUStringDicEntry *b ) {
		CUString str1 = a->key;
		char *str11 = str1.GetStr();
		CUString str2 = b->key;
		char *str22 = str2.GetStr();
		return strcmp( str11, str22 ) < 0;
		//return strcmp( (const)a.key.GetStr(), (const)b.key.GetStr() ) < 0;
		//return strcmp( (const char*)a.key.GetStr(), (const char*)b.key.GetStr() ) < 0;
	}

	////////////////////////////////////////////////////////////
	/**
		@brief	생성자
	*/
	////////////////////////////////////////////////////////////
	CUStringDic::CUStringDic()
	{
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	소멸자
	*/
	////////////////////////////////////////////////////////////
	CUStringDic::~CUStringDic()
	{
		Clear();
	} 


	////////////////////////////////////////////////////////////
	void CUStringDic::Clear()
	{
	}


	////////////////////////////////////////////////////////////
	bool CUStringDic::LoadBinary( char *prefix )
	{
		char fn[1024];
		sprintf( fn, "%s.skey", prefix );
		CUTextFile file_skey( fn, "r" );
		if( file_skey.IsOpen() == false )	return false;

		entry_vec.clear();

		CUString line;
		if( file_skey.ReadLine( line ) == false ) return false;
		int num_record = atoi( line.GetStr() );

		while( true ) {
			CUString line;
			if( file_skey.ReadLine( line ) == false ) break;
			if( line.IsEmpty() ) {
				CUStringDicEntry* new_entry = new CUStringDicEntry();;
				entry_vec.push_back( new_entry );
			}
			else {
				CUStringListRO tok( line, "\t" );
				if( tok.GetSize() != 3 )	return false;

				CUStringDicEntry* new_entry = new CUStringDicEntry();;
				new_entry->key = tok.GetAt(0);
				new_entry->start_addr = atoi(tok.GetAt(1));
				new_entry->end_addr = atoi(tok.GetAt(2));
				entry_vec.push_back( new_entry );
			}
		}

		fprintf( stderr, "%d entries loaded\n", entry_vec.size() );
		this->prefix = prefix;
		return true;
	}

	bool CUStringDic::GetValue( char *str, CUString &result )
	{
		int idx = 0;

		/*
		// linear search for debug
		for( int i=0; i<entry_vec.size(); i++ ) {
			if( strcmp( str, entry_vec[ i ]->key.GetStr() ) == 0 )	{
				
				fprintf( stderr, "Find linear: %d\n", i );
				for( int t=i; t>0; ) {
					fprintf( stderr, "%d %s\n", t, entry_vec[t]->key.GetStr()  );
					if( t % 2 == 1 ) {
						t = (t-1)/2;
					}
					else {
						t = (t-2)/2;
					}
				}

				break;
				if( GetValueByAddr( entry_vec[i]->start_addr, entry_vec[i]->end_addr, result ) == false ) {
					return true;
				}
				else {
					return true;
				}
			}
		}
		*/

		while( true ) {
			if( idx > (int)entry_vec.size()-1)	 {
				break;
			}
//			fprintf( stderr, "%d %s\t", idx, entry_vec[idx]->key.GetStr() );
			CUStringDicEntry *entry = entry_vec[ idx ];
			int cmp = strcmp( str, entry->key.GetStr() );
			if( cmp == 0 )	{
				return GetValueByAddr( entry->start_addr, entry->end_addr, result );
			}
			
			if( cmp < 0 )	{
				idx = 2 * idx + 1;
//				fprintf( stderr, "left\n" );
			}
			else {
				idx = 2 * idx + 2;
//				fprintf( stderr, "right\n" );
			}
		}

		return false;
	}

	bool CUStringDic::GetValueByAddr( long start, long end, CUString &result )
	{
		char fn[1024];
		sprintf( fn ,"%s.sdata", this->prefix.GetStr() );
		FILE *fp = fopen( fn, "r" );
		if( !fp )	return false;

		fseek( fp, start, SEEK_SET );
		
		char *buf = new char[ end-start+1 ];
		fread( buf, sizeof(char), end-start, fp );
		buf[ end-start ] = '\0';
		result = buf;
		delete buf;
		fclose( fp );
		return true;

	}

	////////////////////////////////////////////////////////////
	bool CUStringDic::Binarize( char *fn, char *out_prefix )
	{
		CUTextFile file( fn, "r" );
		if( file.IsOpen() == false )	return false;

		// load key and check valid format
		int num_record = 0;
		while( true ) {
			CUString line;
			if( file.ReadLine( line ) == false ) break;

			int idx = line.Find("\t" );
			if( idx < 0 )	return false;

			line.SetAt( idx, '\0' );
			CUStringDicEntry* new_entry = new CUStringDicEntry();
			new_entry->key = line.GetStr();
			entry_vec.push_back( new_entry );
			num_record++;
		}
		fprintf( stderr, "%d\n", num_record );
		//std::sort( entry_vec.begin(), entry_vec.end(), SortDicEntry );
		std::sort( entry_vec.begin(), entry_vec.end(), SortDicEntry2 );

		// start to write
		char out_fn[1024];
		sprintf( out_fn, "%s.ssort", out_prefix );
		CUTextFile file_sort( out_fn, "w" );
		if( file_sort.IsOpen() == false )	{
			return false;
		}
		for( int i=0; i<entry_vec.size(); i++ ) {
			fprintf( file_sort.GetFP(), "%s\n", entry_vec[i]->key.GetStr() );
		}

		sprintf( out_fn, "%s.sdata", out_prefix );
		CUTextFile file_sdata( out_fn, "w" );
		if( file_sdata.IsOpen() == false )	{
			return false;
		}

		num_record = 0;
		file.MoveToStart();
		while( true ) {
			CUString line;
			if( file.ReadLine( line ) == false ) break;
			int idx = line.Find("\t" );

			line.SetAt( idx, '\0' );
			char *sdata = line.GetStr()+idx+1;

			entry_vec[ num_record ]->start_addr = ftell( file_sdata.GetFP() );
			fprintf( file_sdata.GetFP(), "%s", sdata );
			entry_vec[ num_record ]->end_addr = ftell( file_sdata.GetFP() );
			fprintf( file_sdata.GetFP(), "\n" );

			num_record++;
		}

		sprintf( out_fn, "%s.skey", out_prefix );
		CUTextFile file_skey( out_fn, "w" );
		if( file_skey.IsOpen() == false )	{
			return false;
		}
		fprintf( file_skey.GetFP(), "%d\n", num_record );

		list<int> begin_queue;
		list<int> end_queue;
		begin_queue.push_back( 0 );
		end_queue.push_back(entry_vec.size()-1);
		while( true ) {
			if( begin_queue.size() == 0 )	break;

			int begin = begin_queue.front(); begin_queue.pop_front();
			int end = end_queue.front(); end_queue.pop_front();
			if( begin == end ) {
				CUStringDicEntry* entry = entry_vec[ begin ];
//				fprintf( stderr, "%d - %d %d \n", begin, end, begin );
				fprintf( file_skey.GetFP(), "%s\t%ld\t%ld\n",
						entry->key.GetStr(),
						entry->start_addr,
						entry->end_addr );
			}
			else if( begin > end ) {
				fprintf( file_skey.GetFP(), "\n" );
			}
			else {
				int mid = (int) ceil( (double)begin+ ( (double)(end-begin)/2 ) );
				//fprintf( stderr, "%d - %d %d\n", begin, end, mid );
				CUStringDicEntry* entry = entry_vec[ mid ];
				fprintf( file_skey.GetFP(), "%s\t%ld\t%ld\n",
						entry->key.GetStr(),
						entry->start_addr,
						entry->end_addr );

				begin_queue.push_back( begin );
				end_queue.push_back( mid-1 );
				begin_queue.push_back( mid+1 );
				end_queue.push_back( end );
			}
		}

		return true;
	}
}

// EOF ㅁ

