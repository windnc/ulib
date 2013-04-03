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
	//		line.TrimLeft(" \t\"'");
	//		line.TrimRight(" \t\"'");

			if( line.IsEmpty() )	continue;
			if( line.GetAt(0) == '#' )	continue;

			int pos = line.Find( "=" );
			if( pos < 0 )	continue;


			CUString str_key = line.Left( pos );
			str_key.TrimRight( " \t" );
			str_key.TrimRight( "\"'" );

			CUString str_value = line.Mid( pos+1 );
	//		str_value.TrimLeft( " \t" );
	//		str_value.TrimLeft( "'\"" );

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
		// 파일이 열렸는지 검사
		if( IsLoad() == false )	return false;


		for( size_t i=0; i< data.GetSize(); i++ )	{
			CUString str;
			if( !data.GetAt( i, str ) )	return false;

			if( str.Find( key.GetStr() ) == 0 )	{
				ret_value = str.Mid( key.GetLength() + 1 );
				return true;
			}
		}
		return false;

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


		for( size_t i=0; i< data.GetSize(); i++ )	{
			CUString str;
			if( !data.GetAt( i, str ) )	return false;

			if( str.Find( key.GetStr() ) == 0 )	{
				return false;
				
			}
		}

		data.PushBack( key + CUString("\t" ) + value );
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
		// 파일이 열렸는지 검사
		if( IsLoad() == false )	return false;

		for( size_t i=0; i< data.GetSize(); i++ )	{
			CUString str;
			if( !data.GetAt( i, str ) )	return false;

			if( str.Find( key.GetStr() ) == 0 )	return true;
		}
		return false;
	}

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
}

// EOF

