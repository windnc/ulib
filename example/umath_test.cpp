#include "umath.h"
using namespace ulib;

void func1()
{
	float mean = 25.0f;
	float std_dev = 40.0f;

	for( float i=0.0f; i<=150.0f; i+=5.0f )	{
		float m = CUMath::NormalDist( i, mean, std_dev );

		fprintf( stderr, "%1.2f -> %1.10f\n", i, m );
	}
}


int main()
{
	func1();
}

// EOF ㅁ

