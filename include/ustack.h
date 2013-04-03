/**
	@file		ustack.h
	@brief		ustack header
	@author		이승욱
	@date		06.07.15
	@version	0.7
	@todo		???
	@warning	???
	@bug		???
*/

#ifndef ___ustack___
#define ___ustack___

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

namespace ulib {

	/**
		@class		CUStackNode
		@brief		Stack Node 클래스
		@date		06.07.11
		@author		이승욱
		@warning	???
		@bug		???
	*/
	class CUStackNode
	{
	public:
		CUStackNode( void *arg_data, short arg_data_size );
	public:
		void *data;		///<	저장할 데이타
		short data_size;	///< 저장할 데이타 크기
		CUStackNode *next;	///< 이전 노드
		CUStackNode *prev;///< 다음 노드
		
		
	};


	/**
		@class		CUStack
		@brief		Stack 클래스
		@date		06.07.11
		@author		이승욱
		@warning	???
		@bug		???
	*/
	class CUStack
	{
	public:
		CUStack( int arg_verbose = 0);
		~CUStack();

	public:
		void Verbose( int arg_verbose );
		long GetSize();
		bool GetTop( void *ret_data );
		long Push( void* arg_data, short arg_data_size );
		bool Pop( void* ret_data );
		void Clear();

	private:
		int verbose;	///< 메시지를 화면에 출력 정도
		long size;		///< stack 크기
		CUStackNode *head;	///< 처음 노드
		CUStackNode *top;	///< 마지막 노드
	};

}

#endif

