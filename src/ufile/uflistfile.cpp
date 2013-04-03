/*
	작성자	:	swlee
	작성일	:	Dec. 26, 2009 ~
	버전	:	0.1.0
	설명	:	for flist
	미구현	:	
	버그	:	
*/

#include "uflistfile.h"

namespace ulib {

	///////////////////////////////////////////////////////////////
	inline CUFlistFile::CUFlistFile( CUString arg_filename )
	{
		CUFlistFile( arg_filename.GetStr() );
	}


	///////////////////////////////////////////////////////////////
	inline CUFlistFile::CUFlistFile( char *arg_filename )
	{
		Open( arg_filename );
	}


	///////////////////////////////////////////////////////////////
	inline CUFlistFile::~CUFlistFile()
	{
	}


	///////////////////////////////////////////////////////////////
	inline bool CUFlistFile::Open( CUString arg_filename )
	{
		return Open( arg_filename.GetStr() );
	}


	///////////////////////////////////////////////////////////////
	bool CUFlistFile::Open( char *arg_filename )
	{
		if( file.OpenFile( arg_filename ) == false )	return false;

		while( 1 )	{
			CUString line;
			if( file.ReadLine( line ) == false ) break;
			file_list.PushBack( line );
		}
		return true;
	}


	///////////////////////////////////////////////////////////////
	inline int CUFlistFile::GetNumFile()
	{
		return file_list.GetSize();
	}


	///////////////////////////////////////////////////////////////
	inline bool CUFlistFile::IsOpen()
	{
		return file.IsOpen();
	}


	///////////////////////////////////////////////////////////////
	inline bool CUFlistFile::CheckOpen()
	{
		return file.CheckOpen();
	}


	///////////////////////////////////////////////////////////////
	inline char *CUFlistFile::GetFilename( int i )
	{
		if( (int)file_list.GetSize() < i )	return NULL;
		return file_list.GetAt(i);
	}


	///////////////////////////////////////////////////////////////
	inline bool CUFlistFile::CheckList( bool print )
	{
		for( int i=0; i<GetNumFile(); i++ )	{

			if( print == true )	{
				fprintf( stderr, "[%d] ", i+1 );
			}

			char *fn = GetFilename( i );
			if( fn == NULL )	{
				if( print == true )	{
					fprintf( stderr, "NULL [FAIL]\n"  );
				}
				return false;
			}

			if( print == true )	{
				fprintf( stderr, "%s ", fn );
			}

			CUTextFile f( fn, "r" );
			if( f.IsOpen() == false )	{
				if( print == true ) {
					fprintf( stderr, "[FAIL]\n" );
				}
				return false;
			}
			if( print == true )	{
				fprintf( stderr, "[OK]\n" );
			}
		}

		return true;
	}


	///////////////////////////////////////////////////////////////
	bool CUFlistFile::GetFileContent( int i, CUString &str )
	{
		char *fn = GetFilename(i);
		if( fn == NULL )	return false;

		CUTextFile f( fn, "r" );
		if( f.IsOpen() == false )	return false;

		f.LoadToStr( str );
		return true;
	}

}

// EOF

