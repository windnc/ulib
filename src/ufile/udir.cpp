#include "udir.h"

namespace ulib {

	#ifdef WIN32
	CUDir::CUDir()
	{
	}

	CUDir::~CUDir()
	{
	}

	bool CUDir::GetFileList( CUStringList &list, char dir[], char ext[], bool subdir )
	{
		HANDLE handle;
		WIN32_FIND_DATA find_data;

		char szPath[MAX_PATH];
		sprintf( szPath, "%s\\%s", dir, ext );
		
		handle = ::FindFirstFile(szPath, &find_data);
		//지정한 디렉토리가 path가 잘못되었다면 
		if(handle == INVALID_HANDLE_VALUE) return false;      
		list.Clear();
		CUStringList dir_stack;
		do {
			/*
			if(info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){ 
				if(info.cFileName[0] != '.'){     //하위폴더로..
					sprintf(szPath, "%s%s\\*.*", pPath, info.cFileName);
					FindFileName(szPath);     // 해당 하위폴더를 검색한다.
				}
			} else {
				//파일 이름을 얻오온다..저장하던지 아니면 원하는 처리를 한다.
				//filenum++;
				//strcpy(m_strFilesPath[filenum], info.cFileName);
			}
			*/
			//fprintf( stderr, "%s\n", find_data.cFileName );
			if( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )		{
				if( subdir)	{
				}
			}
			else	{
				list.PushBack( CUString(dir)+CUString("\\") + find_data.cFileName );
			}

		} while (::FindNextFile(handle, &find_data));

		::FindClose(handle);
		return true;
	}



	//////////////////////////////////////////////////////////////////////////
	#else

	CUDir::CUDir()
	{
		p_dir = NULL;
	}

	CUDir::CUDir( CUString arg_dirname )
	{
		OpenDir( arg_dirname.GetStr() );
	}

	CUDir::CUDir( char arg_dirname[] )
	{
		CUDir();
		OpenDir( arg_dirname );
	}

	CUDir::~CUDir()
	{
		if( IsOpen() )	CloseDir();
	}

	bool CUDir::OpenDir( char arg_dirname[] )
	{
		if( strlen( arg_dirname ) == 0 )	return false;
		p_dir = opendir( arg_dirname );
		if( p_dir == false )	return false;

		dirname = arg_dirname;
		dirname.TrimRight("/");
		return true;
	}

	void CUDir::CloseDir()
	{
		if( p_dir == NULL )	return;
		closedir( p_dir );
	}


	bool CUDir::ReadFile( CUString &arg_filename )
	{
		if( IsOpen() == false )	return false;
		if( p_dir == NULL )	return false;
		struct dirent *p_file = readdir( p_dir );
		if( p_file == NULL )	return false;



		arg_filename = p_file->d_name;
		//fprintf( stderr, "[%s]\n", arg_filename.GetStr() );
		
		// .이나 ..이면 스킵
		if( arg_filename == "." || arg_filename == ".." )	{
			if( ReadFile( arg_filename ) == false )	return false;
		}

		// 디렉토리면 스킵
		DIR *tmp = opendir( arg_filename.GetStr() );
		if( tmp != NULL )	{
			closedir( tmp );
			if( ReadFile( arg_filename ) == false )	return false;
		}

		return true;
	}


	void CUDir::MoveToStart()
	{
		if( p_dir == NULL )	return;
		rewinddir( p_dir );
	}


	bool CUDir::IsOpen()
	{
		if( p_dir == NULL )	return false;	
		return true;
	}

	size_t CUDir::GetNumFile()
	{
		if( IsOpen() == false )	return 0;
		if( p_dir == NULL )	return false;

		MoveToStart();
		int num_file = 0;

		while(1)	{
			struct dirent *p_file = readdir( p_dir );
			if( p_file == NULL )	break;

			CUString filename = p_file->d_name;
			// .이나 ..이면 스킵
			if( filename == "." || filename == ".." )	continue;

			// 디렉토리면 스킵
			DIR *tmp = opendir( filename.GetStr() );
			if( tmp != NULL )	{
				closedir( tmp );
				continue;
			}

			num_file++;
		}
		MoveToStart();

		return num_file;
		
	}


	bool CUDir::GetFileList( CUStringList &list, char extension[] )
	{
		if( IsOpen() == false )	return false;
		list.Clear();
		MoveToStart();
		while(1)	{
			CUString file;
			if( ReadFile( file ) == false )	break;

			CUString filter_ext = extension;
			if( filter_ext.IsEmpty() == true || filter_ext == CUString("*") )	{
				file = GetDirName() + CUString("/") + file;
				list.PushBack( file );
			}
			else	{
				CUString now_ext = ExtractExtension( file );
				if( now_ext == filter_ext )	{
					file = GetDirName() + CUString("/") + file;
					list.PushBack( file );
				}

			}
		
		}
		MoveToStart();
		return true;
	}


	#endif






	CUString CUDir::GetDirName()
	{
		return dirname;
	}


	CUString CUDir::ExtractFilename( CUString &full_filename )
	{
		int idx = full_filename.ReverseFind( '/' );
		if( idx <0 )	return full_filename;
		return CUString( full_filename.Mid( idx+1 ) );
	}

	CUString CUDir::ExtractFilename( char full_filename[] )
	{
		CUString tmp_str = full_filename;
		return ExtractFilename( tmp_str );
	}

	CUString CUDir::ExtractExtension( char *filename )
	{
		CUString tmp = filename;
		return ExtractExtension( tmp );
	}

	CUString CUDir::ExtractExtension( CUString &filename )
	{
		int idx =filename.ReverseFind( '.' );
		if( idx < 0 )	return CUString("");
		return CUString( filename.Mid( idx+1 ) );

	}

}

// EOF

