/**
	@file		ustringtree.h
	@brief		ustringtree header
	@author		swlee
	@date		Apr. 15, 2013
	@version	0.1
	@todo		
	@warning	
	@bug		
*/
#ifndef ___ustringtree___
#define ___ustringtree___

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ustring.h"
#include "ustringnode.h"
#include "utree.h"

#define DELIMETER_CHARS   " #$%@*\n\t\"'-+=!?,./%<>()[]{}:;|"


namespace ulib {

	class CUStringTreeNode : public CUTreeNode {
	public:
		CUStringTreeNode();

	public:
		void AddChild( CUStringTreeNode *child );
		CUStringTreeNode* GetChild( int idx );
		void Print( FILE *fp );
		void SetData( char *str );
		void SetData( CUString str );
	};

	////////////////////////////////////////////////////////////
	/**
		@class		CUStringTree
		@brief		StringTree class
		@date		Apr 15, 2013 ~
		@author		swlee
		@warning	???
		@bug		???
		@note		???
	*/
	////////////////////////////////////////////////////////////
	class CUStringTree: public CUTree
	{
	public:
		CUStringTree();
		~CUStringTree();

	public:
		void Clear();

		CUStringTreeNode* GetRootNode();
		CUStringTreeNode* AddChildNode( CUStringTreeNode* parent );
		void Print( FILE *fp, CUStringTreeNode *root );


	private:
		CUStringTreeNode* AllocateNode();
	};

}

#endif

