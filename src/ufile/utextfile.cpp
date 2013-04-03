/*
	작성자	:	swlee
	작성일	:	Sep. 22, 2006
	버전	:	0.6.0
	설명	:	text file
	미구현	:	
	버그	:	write mode로 연 후 CloseFile()로 닫으면 그 이후에system명령어로 이 파일을 쓸려고 하면 에러
*/

#include "utextfile.h"

namespace ulib {

	//////////////////////////////////////////////////////////////////
	CUTextFile::CUTextFile( int arg_verbosity )
	{
		Verbosity( arg_verbosity );
		Init();
	}


	//////////////////////////////////////////////////////////////////
	CUTextFile::CUTextFile( CUString arg_file_name, CUString arg_file_mode, int arg_verbosity )
	{
		Verbosity( arg_verbosity );
		Init();
		OpenFile( arg_file_name, arg_file_mode );
	}


	//////////////////////////////////////////////////////////////////
	CUTextFile::~CUTextFile()
	{
		if( verbosity >= 1 )	{
			printf(	"CUTextFile Release...\n" );
			fflush( stdout );
		}

		CloseFile();

		if( verbosity >= 1 )	{
			printf(	"CUTextFile Release... [OK]\n" );
			fflush( stdout );
		}
	}


	//////////////////////////////////////////////////////////////////
	void CUTextFile::Init()
	{
		fp = NULL;
		content = NULL;
		file_size = UNKNOWN;
		num_line = UNKNOWN;
		now_line = 0;	 
	}


	//////////////////////////////////////////////////////////////////
	bool CUTextFile::OpenFile( CUString arg_file_name, CUString arg_file_mode )
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
	bool CUTextFile::CheckOpen( FILE *fp )
	{
		CUString color_str = GetFileName();
		color_str.SetColor( "light_blue" );
		fprintf( fp, "File open [%s]... ", color_str.GetStr() );
		if( IsOpen() )	{
			CUString msg = "OK";
			msg.SetColor( "light_blue" );
			fprintf( fp, "[%s]\n", msg.GetStr() );
			return true;
		}
		else	{
			CUString msg = "FAIL";
			msg.SetColor( "light_red" );
			fprintf( fp, "[%s]\n", msg.GetStr() );
			return false;
		}
		
	}


	////////////////////////////////////////////////////////
	void CUTextFile::CloseFile()
	{
		if( verbosity >= 2 )	{
			printf(	"CloseFile...\n" );
			fflush( stdout );
		}

		if( fp )	{
			fclose( fp );
			fp = NULL;
		}

		if( verbosity >= 1 )	{
			printf(	"CloseFile...[OK]\n" );
			fflush( stdout );
		}
	}


	//////////////////////////////////////////////////////////////////
	bool CUTextFile::ReopenFile( CUString arg_file_name, CUString arg_file_mode )
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
	bool CUTextFile::LoadToStr( CUString &str )
	{
		if( IsOpen() == false )	return false;
		str.Empty();
		MoveToStart();
		char *tmp = new char[file_size+5];

		/*
		while(1)	{
			CUString line;
			if( ReadLine( line ) == false )	break;
			str += line + "\n";
		}
		str.Replace( "\r", "" );
		*/

		fread( tmp, 1, file_size, GetFP() );
		tmp[ file_size ] = '\0';

		// check \0 
		for( int i=0; i<file_size; i++ )
		{
			if( tmp[i] == '\0' )
			{
				return false;
			}
		}

		str = tmp;
		delete tmp;

		str.Replace("\r", "");
		return true;
	}


	////////////////////////////////////////////////////////
	bool CUTextFile::LoadToMem()
	{
		if( IsOpen() == false )	return false;
		MoveToStart();
		content = new char[file_size+5];

		fread( content, 1, file_size, GetFP() );
		content[ file_size ] = '\0';
		return true;
	}


	////////////////////////////////////////////////////////
	inline bool CUTextFile::IsOpen()
	{
		if( fp == NULL )	return false;
		else				return true;
	}


	////////////////////////////////////////////////////////
	inline FILE *CUTextFile::GetFP()
	{
		return fp;
	}

	//////////////////////////////////////////////////////////////////
	inline CUString CUTextFile::GetFileName()
	{
		return file_name;
	}


	//////////////////////////////////////////////////////////////////
	inline CUString CUTextFile::GetFileMode()
	{
		return file_mode;
	}

	//////////////////////////////////////////////////////////////////
	inline void CUTextFile::Verbosity( int arg_verbosity )
	{
		verbosity = arg_verbosity;
	}


	//////////////////////////////////////////////////////////////////
	long CUTextFile::GetNumLine()
	{
		
		// check
		if( !IsOpen() )	{		
			return UNKNOWN;
		}

		// 이미 계산 되어져 있으면 바로 리턴
		if( num_line != UNKNOWN )	{
			return num_line;
		}

		MoveToEnd();
	//	size_t max_byte = ftell( GetFP() );
	//	size_t total_byte = 0;
		num_line = 0;
		now_line = 0;
		MoveToStart();

		char buf[UFILE_BUFF_SIZE];
		while(1)	{
			// byte단위로 읽음
			size_t read_byte = fread( buf, sizeof(char), UFILE_BUFF_SIZE, GetFP() );
			if( read_byte < 0 )	return UNKNOWN;

			// 파일의 끝까지 읽었는지 체크
			if( read_byte == 0 )	{
				break;
			}
		
			// 읽은 byte내에 \n 개수를 셈
			for( size_t i=0; i<read_byte; i++ )	{
				if( buf[i] == '\n' )	num_line++;
			}

		}

		MoveToStart();
		return num_line;
	}

	bool CUTextFile::MoveToLine( long sel_line )
	{
		// check
		if( !IsOpen() )	return false;
		if( !GetFP() )	return false;


		MoveToEnd();
		size_t max_byte = ftell( GetFP() );
		size_t total_byte = 0;
		MoveToStart();

		long tmp_line = 0;
		MoveToStart();
		char buf[UFILE_BUFF_SIZE];
		while(1)	{
			// byte단위로 읽음
			size_t read_byte = fread( buf, sizeof(char), UFILE_BUFF_SIZE, GetFP() );
		

			// 읽은 byte내에 \n 개수를 셈
			for( size_t i=0; i<read_byte; i++ )	{
				if( buf[i] == '\n' )	{
					if( tmp_line < sel_line )	{ 
						tmp_line++;
					}
					else	{
						fseek( fp, -(UFILE_BUFF_SIZE-i-1), SEEK_CUR );
						return true;
					}
				}
			}

			// 파일의 끝까지 읽었는지 체크
			total_byte += read_byte;
			if( total_byte >= max_byte )	break;

		}
		return false;
	}


	//////////////////////////////////////////////////////////////////
	inline long CUTextFile::GetFileSize()
	{
		return file_size;
	}


	//////////////////////////////////////////////////////////////////
	inline void CUTextFile::MoveToStart()
	{
		if( IsOpen() )	{
			fseek( fp, 0, SEEK_SET );
		}
	}

	//////////////////////////////////////////////////////////////////
	inline void CUTextFile::MoveToEnd()
	{
		if( IsOpen() )	{
			fseek( fp, 0, SEEK_END );
		}
	}


	////////////////////////////////////////////////////////
	bool CUTextFile::ReadLine( CUString &str )
	{	
		if( !IsOpen() )	return false;
		if( !GetFP() )	return false;
		
		str.Empty();

		// fget으로는 한 줄을 다 읽을 수 있는 보장이 없으므로
		// 확인이 될 때 까지 계속 읽으며 str의 뒤에 붙혀 넣는다.
		while(1)	{
			char buf2[UFILE_BUFF_SIZE];
			if(!fgets( buf2, UFILE_BUFF_SIZE, GetFP() ) )	{
				return false;
			}
			// 뒤에 붙힘
			str += buf2;

			// 버퍼가 꽉 찼다면
			if( strlen( buf2 ) >= UFILE_BUFF_SIZE-1 )	{
				// 이전에 \n, \r이 있다면 한 줄 읽은 것임.
				if( buf2[UFILE_BUFF_SIZE-2] == '\n' || buf2[UFILE_BUFF_SIZE-2] == '\r' )	{
					break;
				}
				// 버퍼가 꽉차고 \n으로 끝나지 않았으므로 읽을 부분이 더 남았음
				else	{
					// Do Nothing. ( fgets가 다시 호출 되도록 함. )
				}
			}
			// 버퍼가 꽉 차지 않았다면 한 줄 다 읽었음.
			else	{
				break;
			}
		}

		// newline 제거
	//	str.TrimRight( "\n\r" );
		str.Replace("\r", "" );
		str.TrimRight( "\n\r" );

		return true;
	}


	//////////////////////////////////////////////////////////////////
	char* CUTextFile::ReadLine()
	{
		if( content == NULL )	{
			if(	LoadToMem() == false ) return NULL;
			line_start_idx = 0;
		}

		char *ret = NULL;
		for( int i=line_start_idx; content[i] !='\0'; i++ )	{
			if( content[i] == '\n' )	{
				content[i] = '\0';
				for( int r=i-1; r>=0; i-- )	{
					if( content[r] == '\r' )	content[r] = '\0';
					else	break;
				}
				ret = content+line_start_idx;
			
				line_start_idx = i+1;
				break;
			}
		}
		return ret;
	}


	////////////////////////////////////////////////////////
	bool CUTextFile::WriteLine( CUString str )
	{	
		if( !IsOpen() )	return false;
		if( !GetFP() )	return false;

		fprintf( GetFP(), "%s\n", str.GetStr() );

		if( ftell(GetFP()) > file_size )	{
			file_size = ftell( GetFP() );
		}
		
		return true;
	}


	////////////////////////////////////////////////////////
	bool CUTextFile::WriteLog( CUString str )
	{
		if( !IsOpen() )	return false;
		if( !GetFP() )	return false;

		time_t t;
		time( &t );
		char *buf = ctime( &t );
		buf[ strlen( buf) -1 ] ='\0';
		fprintf( GetFP(), "%s:::%s\n", buf, str.GetStr() );
		Flush();
			
		return true;
	}


	////////////////////////////////////////////////////////
	inline void CUTextFile::Flush()
	{
		fflush( GetFP() );
	}

	/*
	CUString CUTextFile::GetLineMem( long sel_line )
	{
		return CUString("");
		long cnt_line=0;
		long start = 0;
		long end = -1;

		for( long i=0; i<GetFileSize(); i++ )	{
			if( mem[i] == '\n' )	{
				if( cnt_line == sel_line -1 )	{
					start = i + 1;
					i++;
				}
				else if( cnt_line == sel_line )	{
					end = i - 1;
					break;
				}
				cnt_line++;
			}
		}

		if( end == -1 )	{
			CUString t;
			return t;
		}

		CUString t( mem );
		t = t.SubStr( start, end+1 );
		return t;

	}




	bool CUTextFile::GetNextLineMem( CUString &str )
	{
		long start = offset;
		long end = -1;

		for( long i=start; i<size; i++ )	{
			if( buf[i] == '\n' )	{
				end = i;
				break;
			}
		}
		if( end == -1 )	{
			return false;
		}
		offset = end + 1;
		
		str.SetStr( buf );
		str = str.SubStr( start, end );
		return true;
	}

	*/ 





	/*
		060922	ReadNextLine 삭제, ReadLine 수정
		060810	버그수정 : utextfile(filename) 생성시 getnumline 0으로만 출력 
							getnumline의  fread로 체크 하는 부분 수정
	*/

}

// EOF

