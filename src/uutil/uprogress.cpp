///////////////////////////////////////////////////////////////////
/**
	@file		ucounter.cpp
	@brief		ucounter.cpp
	@author		이승욱
	@date		08.11.23
	@version	0.0.1
	@todo		
	@warning	???
	@bug		???
	@note		
*/
///////////////////////////////////////////////////////////////////
#include "uprogress.h"

namespace ulib {

	///////////////////////////////////////////////////////////////////
	CUProgress::CUProgress()
	{
		begin_clock = -1;
		end_clock = -1;
		max_cnt  = 0;
	}

	///////////////////////////////////////////////////////////////////
	void CUProgress::Begin()
	{
		begin_clock = clock();
	}


	///////////////////////////////////////////////////////////////////
	void CUProgress::End()
	{
		end_clock = clock();
	}


	///////////////////////////////////////////////////////////////////
	double CUProgress::GetElapsedSec()
	{
		return (double)(end_clock-begin_clock)/CLOCKS_PER_SEC;
	}


	///////////////////////////////////////////////////////////////////
	double CUProgress::GetElapsedSec( clock_t now_clock )
	{
		return (double)(now_clock-begin_clock)/CLOCKS_PER_SEC;
	}


	///////////////////////////////////////////////////////////////////
	void CUProgress::SetMaxCount( int i )
	{
		max_cnt = i;
	}


	///////////////////////////////////////////////////////////////////
	float CUProgress::GetPercent( int now_cnt )
	{
		if( max_cnt == 0 )	return 0.0f;
		return (float)(now_cnt) / (float)max_cnt * 100.0f;
	}


	///////////////////////////////////////////////////////////////////
	void CUProgress::PrintPercent( FILE *fp, int now_cnt, char msg[] )
	{
		char buf[1024];
		sprintf( buf, "%3.2f%%", GetPercent(now_cnt) );
		CUString str = buf;
		str.SetColor( "light_blue" );
		fprintf( fp, "%s (%d/%lu) %1.2f sec   %s",
				str.GetStr(),  now_cnt, max_cnt,
				GetElapsedSec( clock() ),  msg );
	}


	///////////////////////////////////////////////////////////////////
	void CUProgress::PrintElapsedTime( FILE *fp )
	{
		char buf[1024];
		sprintf( buf, "%3.2f sec", GetElapsedSec() );
		CUString str = buf;
		str.SetColor( "light_blue" );
		fprintf( fp ,"%s\n", buf );
	}

}

// EOF
