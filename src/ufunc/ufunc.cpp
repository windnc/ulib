#include "ufunc.h"
namespace ulib {

	// ㅁ
	//////////////////////////////////////////////////////////////////////////////////////
	bool LoadTextFile( char filename[], CUString &file_content )
	{
		CUTextFile file( filename, "r" );
		if( file.IsOpen() == false ) return false;

		fseek( file.GetFP(), 0, SEEK_END );
		long size = ftell( file.GetFP() );
		fseek( file.GetFP(), 0, SEEK_SET );

		char *buff = new char[ size+1 ];
		fread( buff, sizeof(char), size, file.GetFP() );  
		buff[size] = '\0';
		file_content = buff;
		delete buff;

		return true;
	}


	//////////////////////////////////////////////////////////////////////////////////////
	bool GetElementByBoundTag( CUString &str, CUString &ret, char start[], char end[] )
	{
		int idx = str.Find( start );
		if( idx < 0 )	return false;

		int idx2 = str.Find( end, idx + strlen(start) );
		if( idx2 < 0 )	return false;

		ret = str.SubStr( idx+strlen(start), idx2 );

		return true;
	}


	//////////////////////////////////////////////////////////////////////////////////////
	CUString Bool2Str( bool expr )
	{
		if( expr == true )	return CUString("Y");
		else				return CUString("N");
	}


	//////////////////////////////////////////////////////////////////////////////////////
	bool Str2Bool( CUString str )
	{
		str.MakeToUpper();
		if( str == "1" || str == "TRUE" )	return true;

		return false;
	}


	//////////////////////////////////////////////////////////////////////////////////////
	int Str2Int( CUString str )
	{
		return atoi( str.GetStr() );
	}


	//////////////////////////////////////////////////////////////////////////////////////
	double Str2Real( CUString str )
	{
		return atof( str.GetStr() );
	}

}

// EOF

