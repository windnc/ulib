#include "uindexfile.h"

namespace ulib {

	///////////////////////////////////////////////////////////////////////////
	CUIndexFile::CUIndexFile()
	{
	}


	///////////////////////////////////////////////////////////////////////////
	CUIndexFile::~CUIndexFile()
	{
		Close();
	}


	///////////////////////////////////////////////////////////////////////////
	bool CUIndexFile::IsLoaded()
	{
		if( key_file.IsOpen() == false )	return false;
		if( value_file.IsOpen() == false )	return false;
		return true;
	}


	///////////////////////////////////////////////////////////////////////////
	void CUIndexFile::Close()
	{
		if( key_file.IsOpen() == true )	key_file.CloseFile();
		if( value_file.IsOpen() == true )	value_file.CloseFile();
	}


	///////////////////////////////////////////////////////////////////////////
	bool CUIndexFile::Create( char *prefix )
	{
		Close();

		char buf[1024];
		sprintf( buf, "%s.uidx-key", prefix );
		if( key_file.OpenFile( buf, "w" ) == false )
		{
			return false;
		}

		sprintf( buf, "%s.uidx-value", prefix );
		if( value_file.OpenFile( buf, "wb" ) == false )
		{
			return false;
		}

		return true;
	}


	///////////////////////////////////////////////////////////////////////////
	bool CUIndexFile::Load( char *prefix )
	{
		Close();
		char buf[1024];
		sprintf( buf, "%s.uidx-key", prefix );
		if( key_file.OpenFile( buf, "r" ) == false )
		{
			return false;
		}

		sprintf( buf, "%s.uidx-value", prefix );
		if( value_file.OpenFile( buf, "r" ) == false )
		{
			return false;
		}

		info_map.clear();
		while( true )
		{
			CUString line;
			if( key_file.ReadLine( line ) == false ) break;
			CUStringList list( line, "\t" );
			if( list.GetSize() != 4 )	{
				fprintf( stderr, "Error: Invalid format: %s\n", line.GetStr() );
				return false;
			}

			if( info_map.find( list.GetAt(0) ) != info_map.end() )
			{
				fprintf( stderr, "Error: Duplicated key: %s\n", list.GetAt(0) );
				return false;
			}


			CUIndexFileInfo info;
			info.start = atol( list.GetAt(1) );
			info.end   = atol( list.GetAt(2) );
			if( strcmp( list.GetAt(3), "0" ) == 0 ) info.enable = false;
			else info.enable = true;

			info_map[ list.GetAt(0) ] = info;
		}

		return true;
	}


	///////////////////////////////////////////////////////////////////////////
	bool CUIndexFile::Insert( char *key, char *value )
	{
		if( IsLoaded() == false )	return false;
		map<string, CUIndexFileInfo>::iterator itr = info_map.find( key );
		if( itr != info_map.end() )	return false;

		CUIndexFileInfo info;

		info.start = ftell( value_file.GetFP() );
		fprintf( value_file.GetFP(), "%s\n", value );
		info.end = ftell( value_file.GetFP() );

		info_map[ key ] = info;

		fprintf( key_file.GetFP(), "%s\t%ld\t%ld\t1\n", key, info.start, info.end );
		return true;
	}


	///////////////////////////////////////////////////////////////////////////
	bool CUIndexFile::Insert( char *key, char *value, int len )
	{
		if( IsLoaded() == false )	return false;
		map<string, CUIndexFileInfo>::iterator itr = info_map.find( key );
		if( itr != info_map.end() )	return false;

		CUIndexFileInfo info;

		info.start = ftell( value_file.GetFP() );
		fwrite( value, 1, len, value_file.GetFP()  );
		fprintf( value_file.GetFP(), "\n" );
		info.end = ftell( value_file.GetFP() );

		info_map[ key ] = info;

		fprintf( key_file.GetFP(), "%s\t%ld\t%ld\t1\n", key, info.start, info.end );
		return true;
	}


	///////////////////////////////////////////////////////////////////////////
	CUStringList CUIndexFile::GetKeyList()
	{
		CUStringList list;
		map<string,CUIndexFileInfo>::iterator itr = info_map.begin();
		while( itr != info_map.end() )
		{
			list.PushBack( itr->first.c_str() );
			itr++;
		}
		return list;

	}


	///////////////////////////////////////////////////////////////////////////
	bool CUIndexFile::GetInfo( char *key, CUIndexFileInfo &info )
	{
		map<string, CUIndexFileInfo>::iterator itr = info_map.find( key );
		if( itr == info_map.end() )	return false;

		info = itr->second;
		return true;
	}


	///////////////////////////////////////////////////////////////////////////
	bool CUIndexFile::GetValue( CUIndexFileInfo info, CUString &ret )
	{
		if( IsLoaded() == false )	return false;
		if( info.enable == false )	return false;

		int len = info.end - info.start;
		if( len < 0 )	return false;

		char *buf = new char[len+1];
		fseek( value_file.GetFP(), info.start, SEEK_SET );
		fread( buf, len, sizeof(char),  value_file.GetFP() );
		buf[len] = '\0';

		ret = buf;
		delete buf;

		return true;
	}


	///////////////////////////////////////////////////////////////////////////
	bool CUIndexFile::GetValue( CUIndexFileInfo info, void *ret )
	{
		if( IsLoaded() == false )	return false;
		if( info.enable == false )	return false;

		int len = info.end - info.start;
		if( len < 0 )	return false;

		fseek( value_file.GetFP(), info.start, SEEK_SET );
		fread( ret, len, sizeof(char),  value_file.GetFP() );

		return true;
	}


	///////////////////////////////////////////////////////////////////////////
	bool CUIndexFile::GetValue( char *key, CUString &ret )
	{
		CUIndexFileInfo info;
		if( GetInfo(key, info ) == false )	return false;

		return GetValue( info, ret );
	}


	///////////////////////////////////////////////////////////////////////////
	bool CUIndexFile::GetValue( char *key, void *ret )
	{
		CUIndexFileInfo info;
		if( GetInfo(key, info ) == false )	return false;

		return GetValue( info, ret );
	}

}

// EOF ㅁ

