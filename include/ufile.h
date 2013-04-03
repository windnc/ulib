/*
	작성자	:	이승욱
	작성일	:	08.05.12
	버전	:	0.1.0
	설명	:	파일 처리 라이브러리
	미구현	:	???
	버그	:	???
*/

#ifndef ___ufile___
#define ___ufile___

#include <stdio.h>
#include <string.h>
#include "ustring.h"

#ifndef UNKNOWN
#define UNKNOWN -1
#endif
#ifndef UFILE_BUFF_SIZE
#define UFILE_BUFF_SIZE 1024	// fgets로 읽을 버퍼의 크기( 최소 2 이상 )
#endif

namespace ulib {

	class CUFile	{
	public:
		// 생성자 소멸자
		CUFile( int verbosity = 0 );
		CUFile( CUString arg_file_name, CUString arg_file_mode = "rb", int verbosity = 0 );
		~CUFile();


	public:
		void Verbosity( int arg_verbosity );
		bool IsOpen();
		bool OpenFile( CUString arg_file_name, CUString arg_file_mode =  "r" );
		void CloseFile();
		bool ReopenFile( CUString arg_file_name, CUString arg_file_mode =  "r" );
		FILE *GetFP();
		void MoveToStart();
		void MoveToEnd();
		long GetFileSize();
		static long GetFileSize( CUString filename );
		static long GetFileSize( char filename[] );
		CUString GetFileName();
		CUString GetFileMode();

	public:
		
	private:
		CUString file_name;	// 파일명
		CUString file_mode;	// 파일모드
		FILE *fp;	// 파일포인터
		long file_size;	// 파일 크기	
		int verbosity;	// 메시지를 화면에 출력할 정도

	private:
		// 초기화
		void Init();

	};

}
#endif

