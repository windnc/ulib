/**
	@file		uconfigfile.h
	@brief		uconfigfile header
	@author		이승욱
	@date		06.07.19
	@version	0.5.0
	@todo		configure 파일을 처리하는 클래스
	@warning	???
	@bug		???
	@note		<key,value>를 stl의 map을 이용하여 구현
*/

#ifndef ___uconfigfile___
#define ___uconfigfile___

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <string>
#include "utextfile.h"
#include "ustringlist.h"
#include "udir.h"

using namespace std;

namespace ulib {

	////////////////////////////////////////////////
	/**
		@class		CUConfigFile
		@brief		Configure 클래스
		@date		06.07.19
		@author		이승욱
		@warning	???
		@todo		???
		@bug		???
		@note		윈도우즈의 ini파일과 같이 환경설정을 저장하는 파일을 처리하는 클래스.\n
	*/
	////////////////////////////////////////////////

	// config 클래스
	class CUConfigFile	{
	public:
		// 생성자, 소멸자
		CUConfigFile();
		CUConfigFile( char fn[] );
		~CUConfigFile();

		bool Load( CUString arg_filename );
		bool IsLoad();
		bool GetValue( CUString key, CUString &ret_value );
		bool SetValue( CUString key, CUString value );
		bool HaveValue(CUString key );
		bool CheckValue(CUString key );
		void Print( FILE *fp );
		void GetKeyList( CUStringList &key );


	private:
		CUString filename;	///< 파일이름
		//CUStringList data;	///< 저장되는 값
		map<string, string> key_value_map;
		CUTextFile config_file; ///< 텍스트 파일처리 클래스
	};


}

#endif
