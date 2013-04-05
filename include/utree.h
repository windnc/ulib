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
#include "unode.h"

namespace ulib {


	////////////////////////////////////////////////////////////
	class CUTreeNode : public CUNode
	{
	public:
		CUTreeNode();
		~CUTreeNode();

	public:
		void AddChild( CUTreeNode *child );
		CUTreeNode* GetChild( int idx );

	public:
		CUTreeNode *parent;
		CUList child_list;
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

