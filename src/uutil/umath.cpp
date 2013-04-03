/*
	작성자	:	이승욱
	작성일	:	09.01.27
	버전	:	0.1.0
	설명	:	
	미구현	:	???
	버그	:	???
*/

#include "umath.h"

namespace ulib {

	//////////////////////////////////////////////////////////////////
	CUMath::CUMath()
	{
	}


	//////////////////////////////////////////////////////////////////
	CUMath::~CUMath()
	{
	}


	////////////////////////////////////////////////////////////////////
	double CUMath::NormalDist( double x, double mean, double std_dev )
	{
		double pi = 3.14159265358979f;
		double e = 2.718281828459045f;

		double pt1 = 1.0f / ( std_dev * sqrt( 2.0f * pi ) );

		double num =  pow( x - mean, 2.0f );
		double denom = 2.0f * pow( std_dev, 2.0f );
		double pt2 = pow( e, (-1.0f * num  / denom ) );

		return pt1*pt2;
	}

}

// EOF
