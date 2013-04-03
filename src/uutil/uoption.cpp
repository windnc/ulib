/**
	@file		uoption.cpp
	@brief		uoption.cpp
	@author		swlee
	@date		Apr. 3, 2013
	@version	0.0.1
	@todo		
	@warning	
	@bug		
	@note		
*/

#include "ulib.h"
using namespace std;


namespace ulib {


	////////////////////////////////////////////////////////////////////
	CUOption::CUOption()
	{
	}


	////////////////////////////////////////////////////////////////////
	bool CUOption::Load( int argc, char *argv[] )
	{
		option_map.clear();
		for( int i=1; i<argc; i++ )
		{
			CUString key = argv[i];
			CUString value = argv[i+1];
			i++;

			if( key.GetAt(0) != '-' )	{
				fprintf( stderr, "ERROR: invalud key [%s]\n", key.GetStr() );
				return false;
			}

			key = key.Mid(1);
			option_map[ key.GetStr() ] = value.GetStr();
		}

		CUString tmp = "conf";
		CUString conf_fn;
		if( this->GetValue( tmp, conf_fn ) ) {
			if( conf_file.Load( conf_fn ) == false ) {
				fprintf( stderr, "ERROR: fail to open conf file [%s]\n", conf_fn.GetStr() );
				return false;
			}
			else {
				return true;
			}
		}
		else {
			return true;
		}
	}



	////////////////////////////////////////////////////////////////////
	void CUOption::Print( FILE *fp )
	{
		if( fp == NULL )	return;

		if( conf_file.IsLoad() ) {
			fprintf( fp, "Config file\n" );
			conf_file.Print( fp );
			fprintf( fp, "\n" );
		}


		fprintf( fp, "Command line parameter\n" );
		fprintf( fp, "==================\n" );
		map<string, string>::iterator itr = option_map.begin();
		while( itr != option_map.end() ) {
			fprintf( fp, "[%s] => [%s]\n", itr->first.c_str(), itr->second.c_str() );
			itr++;
		}
		fprintf( fp, "==================\n" );

	}


	////////////////////////////////////////////////////////////////////
	bool CUOption::GetValue( CUString &key, CUString &value )
	{
		map<string, string>::iterator itr = option_map.find( key.GetStr() );
		if( itr != option_map.end() )	{
			value = itr->second.c_str();
			return true;
		}

		return conf_file.GetValue( key, value );
	}

}

// EOF ㅁ

