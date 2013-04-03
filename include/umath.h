#ifndef ___umath___
#define ___umath___

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// ㅁ

namespace ulib {

	class CUMath
	{
		public:
			CUMath();
			~CUMath();

			static double NormalDist( double x, double mean, double std_dev );
	} ;

}

#endif


