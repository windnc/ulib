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
#include "ulist.h"

namespace ulib {


	////////////////////////////////////////////////////////////
	class CUTreeNode
	{
	public:
		int id;
		CUTreeNode( int id );
		~CUTreeNode();

	public:
		void SetData( void *arg_data, short arg_data_size );
		void *GetData();
		void AddChild( CUTreeNode *child );
		CUTreeNode* GetChild( int idx );

	public:
		void *data;			///< 노드에 저장할 데이타
		CUTreeNode *parent;
		CUList child_list;
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
		int GetNumNode();
		CUTreeNode* GetRootNode();
		bool IsEmpty();

		CUTreeNode * AddChildNode( CUTreeNode *parent );

		void Verbose( int arg_verbose = 0 );
		void Clear();
		void Print( FILE *fp, CUTreeNode *node, int level );

	private:

		CUTreeNode * AllocateNode();
		CUList node_list;
		int verbose;
	};


}
#endif

// EOF ㅁ

