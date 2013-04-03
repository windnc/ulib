/*
	작성자	:	이승욱
	작성일	:	08.05.12
	버전	:	0.1.0
	설명	:	디렉토리 처리 함수
	미구현	:	???
	버그	:	???
*/

#ifndef ___udir___
#define ___udir___

#include <stdio.h>
#include <string.h>
#include "ustring.h"
#include "ustringlist.h"

namespace ulib {

#ifdef WIN32
#include "windows.h"

	/////////////////////////////
	class CUDir	{
	public:
		CUDir();
		~CUDir();
	public:
		bool GetFileList( CUStringList &list, char dir[], char ext[], bool subdir );
		CUString GetDirName();
		static CUString ExtractFilename( CUString &path );
		static CUString ExtractFilename( char path[] );
		static CUString ExtractExtension( CUString &file );

	private:
		HANDLE h_dir;
		CUString dirname;
	};
	/////////////////////////////
#else

#include <dirent.h>
class CUDir {
public:
	CUDir();
	CUDir( char arg_dirname[] );
	CUDir( CUString arg_dirname );
	~CUDir();

public:
	bool OpenDir( char arg_dirname[] );
	void CloseDir();
	bool IsOpen();
	bool ReadFile( CUString &arg_file );
	void MoveToStart();
	bool GetFileList( CUStringList &list, char extension[] = ""  );
	CUString GetDirName();
	static CUString ExtractFilename( CUString &path );
	static CUString ExtractFilename( char path[] );
	static CUString ExtractExtension( CUString &file );
	static CUString ExtractExtension( char *file );
	size_t GetNumFile();

	
private:
	DIR *p_dir;
	CUString dirname;
	
private:

};

#endif

}
#endif

