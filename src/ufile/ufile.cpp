/*
	작성자	:	swlee
	작성일	:	May. 12, 2008
	버전	:	0.1.0
	설명	:	파일 처리 라이브러리
	미구현	:	
	버그	:	
*/

#include "ufile.h"

namespace ulib {

	//////////////////////////////////////////////////////////////////
	CUFile::CUFile( int arg_verbosity )
	{
		Verbosity( arg_verbosity );
		Init();
	}


	//////////////////////////////////////////////////////////////////
	CUFile::CUFile( CUString arg_file_name, CUString arg_file_mode, int arg_verbosity )
	{
		Verbosity( arg_verbosity );
		Init();
		OpenFile( arg_file_name, arg_file_mode );
	}


	//////////////////////////////////////////////////////////////////
	CUFile::~CUFile()
	{
		if( verbosity >= 1 )	{
			printf(	"CUFile Release...\n" );
			fflush( stdout );
		}

		CloseFile();

		if( verbosity >= 1 )	{
			printf(	"CUFile Release... [OK]\n" );
			fflush( stdout );
		}
	}


	//////////////////////////////////////////////////////////////////
	void CUFile::Init()
	{
		fp = NULL;
		file_size = UNKNOWN;
	}


	//////////////////////////////////////////////////////////////////
	bool CUFile::OpenFile( CUString arg_file_name, CUString arg_file_mode )
	{
		if( verbosity >= 2 )	{
			printf(	"OpenFile... %s(%s)\n", arg_file_name.GetStr(), arg_file_mode.GetStr() );
			fflush( stdout );
		}

		// check
		if( arg_file_name.IsEmpty() )	return false;
		if( arg_file_mode.IsEmpty() )		return false;

		// open
		file_name = arg_file_name;
		file_mode = arg_file_mode;
		fp = fopen( file_name.GetStr(), file_mode.GetStr() );
		if( !fp ) 	{
			return false;
		}

		// get file size
		MoveToEnd();
		file_size = ftell( fp );
		MoveToStart();

		if( verbosity >= 1 )	{
			printf(	"OpenFile... [OK]\n" );
			fflush( stdout );
		}
		return true;
	}

	////////////////////////////////////////////////////////
	void CUFile::CloseFile()
	{
		if( verbosity >= 2 )	{
			printf(	"CloseFile...\n" );
			fflush( stdout );
		}

		if( fp )	{
			fclose( fp );
		}

		if( verbosity >= 1 )	{
			printf(	"CloseFile...[OK]\n" );
			fflush( stdout );
		}
	}

	//////////////////////////////////////////////////////////////////
	bool CUFile::ReopenFile( CUString arg_file_name, CUString arg_file_mode )
	{
		if( verbosity >= 2 )	{
			printf(	"ReopenFile... %s(%s)\n", arg_file_name.GetStr(), arg_file_mode.GetStr() );
			fflush( stdout );
		}

		CloseFile();
		return OpenFile( arg_file_name, arg_file_mode );

		if( verbosity >= 2 )	{
			printf(	"ReopenFile... [OK]\n" );
			fflush( stdout );
		}

	}


	////////////////////////////////////////////////////////
	bool CUFile::IsOpen()
	{
		if( fp == NULL )	return false;
		else				return true;
	}


	////////////////////////////////////////////////////////
	inline FILE *CUFile::GetFP()
	{
		return fp;
	}

	//////////////////////////////////////////////////////////////////
	inline CUString CUFile::GetFileName()
	{
		return file_name;
	}


	//////////////////////////////////////////////////////////////////
	inline CUString CUFile::GetFileMode()
	{
		return file_mode;
	}

	//////////////////////////////////////////////////////////////////
	inline void CUFile::Verbosity( int arg_verbosity )
	{
		verbosity = arg_verbosity;
	}


	//////////////////////////////////////////////////////////////////
	inline long CUFile::GetFileSize()
	{
		return file_size;
	}


	//////////////////////////////////////////////////////////////////
	inline long CUFile::GetFileSize( CUString filename )
	{
		return GetFileSize( filename.GetStr() );
	}

	//////////////////////////////////////////////////////////////////
	long CUFile::GetFileSize( char filename[] )
	{
		FILE *fp = fopen( filename, "rb" );
		if( fp == NULL )	return -1;

		fseek( fp, 0, SEEK_END );
		long file_size = ftell( fp );
		fclose(fp);

		return file_size;
	}


	//////////////////////////////////////////////////////////////////
	inline void CUFile::MoveToStart()
	{
		if( IsOpen() )	{
			fseek( fp, 0, SEEK_SET );
		}
	}

	//////////////////////////////////////////////////////////////////
	inline void CUFile::MoveToEnd()
	{
		if( IsOpen() )	{
			fseek( fp, 0, SEEK_END );
		}
	}

}

// EOF

