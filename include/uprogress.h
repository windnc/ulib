#ifndef ___uprogress___
#define ___uprogress___

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ustring.h"

namespace ulib  {

	/**
	@file		ustring.h
	@brief		ustring header
	@author		이승욱
	@date		06.09.21
	@version	0.9.1
	@todo		Format 구현, 메모리 효율성 개선
	@warning	???
	@bug		???
	@note		Release0.9
	*/
	class CUProgress {
	public:
		CUProgress();
		void Begin();
		void End();
		double GetElapsedSec();
		double GetElapsedSec( clock_t now_clock );

		void SetMaxCount( int max_cnt );
		float GetPercent( int now_cnt );
		void PrintPercent( FILE *fp, int now_cnt, char msg[]="\n" );
		void PrintElapsedTime( FILE *fp );


	private:
		clock_t begin_clock;
		clock_t end_clock;
		unsigned long max_cnt;
	};

}

#endif

