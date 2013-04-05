/**
	@file		utree.h
	@brief		utree header
	@author		swlee
	@date		Apr. 5, 2013 ~
	@version	0.1
	@todo		
	@warning	
	@bug		
*/
#ifndef ___utree___
#define ___utree___

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utree.h"

namespace ulib {


	////////////////////////////////////////////////////////////
	class CUTreeNode
	{
	public:
		CUTreeNode( void *arg_data, short arg_data_size );
		~CUTreeNode();

	public:
		void *GetData();

	public:
		void *data;			///< 노드에 저장할 데이타
		short data_size;	///< 노드에 저장할 데이타 크기
	};



	////////////////////////////////////////////////////////////
	class CUTree
	{
	public:
		// 생성자, 소멸자
		CUTree( int arg_verbose = 0 );
		~CUTree();

	public:
		long GetSize();
		bool IsEmpty();

		void Verbose( int arg_verbose = 0 );
		void Clear();

	private:
		long size;
		CUTreeNode *root;
		int verbose;
	};


}
#endif

// EOF ㅁ

