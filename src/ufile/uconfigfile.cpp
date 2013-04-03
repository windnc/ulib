/**
	@file		uconfigfile.cpp
	@brief		uconfigfile cpp
	@author		swlee
	@date		Jul. 19, 2006
	@version	0.5.0
	@todo		
	@warning	
	@bug		
	@note		Read-only, for now
*/


#include "uconfigfile.h"

namespace ulib {

	/////////////////////////////////////////////////////////////
	/**
		@brief	생성자
		@see	~CUConfigFile()
	*/	
	/////////////////////////////////////////////////////////////
	CUConfigFile::CUConfigFile()
	{	
		filename = "";
	}

	/////////////////////////////////////////////////////////////
	/**
		@brief	생성자
		@see	~CUConfigFile()
	*/	
	/////////////////////////////////////////////////////////////
	CUConfigFile::CUConfigFile( char fn[] )
	{	
		Load( fn );
	}



	/////////////////////////////////////////////////////////////
	/**
		@brief	소멸자
		@note	
		@see	CUString()
	*/	
	/////////////////////////////////////////////////////////////
	CUConfigFile::~CUConfigFile()
	{
	}



	/////////////////////////////////////////////////////////////
	/**
		@brief	파일을 읽어 항목별로 나누고 메모리에 로드함.
		@param	arg_filename	읽을 설정 파일
		@return	설정 파일을 읽어 메모리에 로드하면 true를, 그렇지 않으면 false를 반환
		@note	가장 먼저 나오는 = 문자를 기준으로 key, value로 나눔.
				key = value, "key" = "value", 'key' = 'value' 형식만 지원
		@see	
	*/	
	/////////////////////////////////////////////////////////////
	bool CUConfigFile::Load( CUString arg_filename )
	{
		/*
		if( CUDir::ExtractExtension( arg_filename ) != "conf" )	{
			return false;
		}
		*/

		filename = arg_filename;
		if( filename.IsEmpty() )	return false;

		config_file.OpenFile( filename, "r" );
		if( config_file.IsOpen() == false )	return false;
		
		config_file.MoveToStart();

		while(1)	{
			CUString line;
			if( !config_file.ReadLine( line ) )	break;

			if( line.IsEmpty() )	continue;
			if( line.GetAt(0) == '#' )	continue;

			int pos = line.Find( "=" );
			if( pos < 0 ) {
				fprintf( stderr, "ERROR: invalud format [%s]\n", line.GetStr() );
				return false;
			}

			CUString str_key = line.Left( pos );
			str_key.Trim( " \t" );

			CUString str_value = line.Mid( pos+1 );
			str_value.Trim(" \t" );

			SetValue( str_key, str_value );

		}

		return true;
	}



	/////////////////////////////////////////////////////////////
	/**
		@brief	key에 해당하는 value를 구함.
		@param	key	찾고자 하는 key
		@param	ret_value value를 저장할 변수
		@return	값을 찾으면 저장 후 true를 반환, 못찾으면 false를 반환
		@see	SetValue()
	*/	
	/////////////////////////////////////////////////////////////
	bool CUConfigFile::GetValue( CUString key, CUString &ret_value )
	{
		if( IsLoad() == false )	return false;

		map<string, string>::iterator itr = key_value_map.find( key.GetStr() );
		if( itr == key_value_map.end() )	return false;
		ret_value = itr->second.c_str();

		return true;
	}
		

	/////////////////////////////////////////////////////////////
	/**
		@brief	key에 value를 저장
		@param	key	저장하고자 하는 key
		@param	value 저장하고자 하는 value
		@return	추가하는 데 성공하면 true, 실패하면 false를 반환
				추가하려는 key가 이미 있다면 false를 반환
		@see	GetValue()
	*/	
	/////////////////////////////////////////////////////////////
	bool CUConfigFile::SetValue(CUString key, CUString value )
	{
		if( IsLoad() == false )	return false;

		key_value_map[ key.GetStr() ] = value.GetStr();

		return true;
	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	key에 해당하는 value가 존재하는지 검사
		@param	key	찾고자 하는 key
		@return	key가 존재하면 true를 그렇지 않으면 false를 반환
		@see	SetValue(), GetValue()
	*/	
	/////////////////////////////////////////////////////////////
	bool CUConfigFile::HaveValue( CUString key )
	{
		if( IsLoad() == false )	return false;

		map<string, string>::iterator itr = key_value_map.find( key.GetStr() );
		if( itr == key_value_map.end() )	return false;

		return true;
	}


	/////////////////////////////////////////////////////////////
	bool CUConfigFile::CheckValue( CUString key )
	{
		if( HaveValue( key ) ==  true )	return true;

		CUString msg = "Error";
		msg.SetColor( "light_red" );

		CUString key_msg = key;
		key_msg.SetColor( "light_blue" );

		fprintf( stderr, "%s, cannot find field: %s\n", msg.GetStr(), key_msg.GetStr() );

		return false;

	}


	/////////////////////////////////////////////////////////////
	/**
		@brief	파일을 열었는지 검사
		@return	파일이 열려 있으면 true를 그렇지 않으면 false를 반환
		@see	Load()
	*/	
	/////////////////////////////////////////////////////////////
	bool CUConfigFile::IsLoad()
	{
		if( config_file.IsOpen() )	{
			return true;
		}
		else	{
			return false;
		}
	}


	void CUConfigFile::Print( FILE *fp )
	{
		fprintf( fp, "==================\n" );
		map<string, string>::iterator itr = key_value_map.begin();
		while( itr != key_value_map.end() ) {
			fprintf( fp, "[%s] => [%s]\n", itr->first.c_str(), itr->second.c_str() );
			itr++;
		}
		fprintf( fp, "==================\n" );
	}
}

// EOF

