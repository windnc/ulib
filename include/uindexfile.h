#ifndef __UINDEXFILE__
#define __UINDEXFILE__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ulib.h"
using namespace std;


namespace ulib {

	class CUIndexFileInfo {
	public:
		unsigned long start;
		unsigned long end;
		bool enable;

	public:
		CUIndexFileInfo()
		{
			start = end = 0;
			enable = true;
		}
		void Copy( CUIndexFileInfo &arg );
	};


	class CUIndexFile {
	public:
		CUIndexFile();
		~CUIndexFile();
	public:

		bool Load( char *prefix );
		bool IsLoaded();
		void Close();
		int GetNumRecord() {	return info_map.size(); }
		CUStringList GetKeyList();
		bool HaveKey( char *key );
		bool GetInfo( char *key, CUIndexFileInfo &info );
		bool GetInfo( char *key, unsigned long &start, unsigned long &end );
		bool GetValue( char *key, CUString &ret );
		bool GetValue( CUIndexFileInfo info, CUString &ret );
		bool GetValue( char *key, void *ret );
		bool GetValue( CUIndexFileInfo info, void *ret );

		bool Create( char *prefix );
		bool Insert( char *key, char *value );
		bool Insert( char *key, char *value, int len );

		void MoveToFirstRecord();
		bool IsLastRecord();
		bool MoveToNextRecord();
		bool GetCurrentRecord( CUString &key, CUString &value );

		//bool Delete( char *key );

		map<string, CUIndexFileInfo> info_map;

	private:
		CUTextFile key_file;
		CUTextFile value_file;
		CUString current_record_key;
		map<string, CUIndexFileInfo>::iterator info_map_itr;

	};

}

#endif

