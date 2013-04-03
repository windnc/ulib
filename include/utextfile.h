/*
	작성자	:	이승욱
	작성일	:	06.09.23
	버전	:	0.6.0
	설명	:	텍스트 파일 처리 라이브러리
	미구현	:	???
	버그	:	???
*/

#ifndef ___utextfile___
#define ___utextfile___

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ustring.h"

#ifndef UNKNOWN
#define UNKNOWN -1
#endif
#ifndef UFILE_BUFF_SIZE
#define UFILE_BUFF_SIZE 1024	// fgets로 읽을 버퍼의 크기( 최소 2 이상 )
#endif

namespace ulib {

	class CUTextFile	{
	public:
		// 생성자 소멸자
		CUTextFile( int verbosity = 0 );
		CUTextFile( CUString arg_file_name, CUString arg_file_mode = "rb", int verbosity = 0 );
		~CUTextFile();


	public:
		void Verbosity( int arg_verbosity );
		bool IsOpen();
		bool OpenFile( CUString arg_file_name, CUString arg_file_mode =  "r" );
		bool CheckOpen( FILE *fp = stderr );
		void CloseFile();
		bool ReopenFile( CUString arg_file_name, CUString arg_file_mode =  "r" );
		FILE *GetFP();
		void MoveToStart();
		void MoveToEnd();
		long GetFileSize();
		CUString GetFileName();
		CUString GetFileMode();
		
		long GetNumLine();
		bool MoveToLine( long sel_line );
		bool ReadLine( CUString &str  );	// 한 줄의 내용을 읽음. 마지막에 \n 문자는 제거됨.
		char* ReadLine();
		bool WriteLine( CUString str  );	// 한 줄의 내용을 씀. 마지막에 \n 문자를 자동으로 추가.
		bool WriteLog( CUString str  );	// 로그 파일에 기록 (날짜가 같이 출력됨)
		//CUString GetLineMem( long sel_line );	
		//bool GetNextLineMem( CUString &str );
		//bool MoveToNextLine();

		bool LoadToStr( CUString &str );

	public:
		
	private:
		//char mem[UFILE_BUFF_SIZE];	//
		long num_line;	// 최대 라인수
		long now_line;	// 현재 라인
		CUString file_name;	// 파일명
		CUString file_mode;	// 파일모드
		FILE *fp;	// 파일포인터
		long file_size;	// 파일 크기	
		int verbosity;	// 메시지를 화면에 출력할 정도
		void Flush();

	private:
		// 초기화
		void Init();
		char *content;
		bool LoadToMem();
		int line_start_idx;

	};

}

#endif


