/*
	작성자	:	이승욱
	작성일	:	09.12.26
	버전	:	0.1.0
	설명	:	flist 파일 처리 라이브러리
	미구현	:	???
	버그	:	???
*/

#ifndef ___uflistfile___
#define ___uflistfile___

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ustringlist.h"
#include "utextfile.h"

namespace ulib {

	////////////////////////////////////
	class CUFlistFile	{
	public:
		// 생성자 소멸자
		CUFlistFile( CUString arg_filename );
		CUFlistFile( char *arg_filename );
		~CUFlistFile();

	public:
		bool Open( CUString arg_filename );
		bool Open( char *arg_filename );
		bool IsOpen();

		bool CheckOpen();
		bool CheckList( bool print );
		bool GetFileContent( int i, CUString &str );
		char *GetFilename( int i );

		int GetNumFile();

	private:
		bool CloseFile();

	private:
		CUTextFile file;
		CUStringList file_list;

	};

}
#endif

