/**
	@file		ulist.h
	@brief		ulist header
	@author		이승욱
	@date		06.07.15
	@version	0.7
	@todo		파일로 저장/로드
	@warning	???
	@bug		???
*/
#ifndef ___ulist___
#define ___ulist___

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


namespace ulib {

	////////////////////////////////////////////////////////////
	/**
		@class		CUListNode
		@brief		List Node 클래스
		@date		06.06.02
		@author		이승욱
		@warning	???
		@bug		???
		@note		???
	*/
	////////////////////////////////////////////////////////////
	class CUListNode
	{
	public:
		CUListNode( void *arg_data, short arg_data_size );
		~CUListNode();

	public:
		void *GetData();
		bool HaveNext();
		bool HavePrev();

	public:
		void *data;			///< 노드에 저장할 데이타
		short data_size;	///< 노드에 저장할 데이타 크기
		CUListNode *next;	///< 이전 노드
		CUListNode *prev;	///< 다음 노드
	};



	////////////////////////////////////////////////////////////
	/**
		@class		CUList
		@brief		List 클래스
		@date		06.06.02
		@author		이승욱
		@warning	???
		@bug		???
		@note		객체의 시작 주소와 크기를 입력하여 노드를 추가한다.\n
					길이가 정해지지 않은 객체( ex. 문자열 )은 동적 생성한 후
					시작 주소와	포인터크기(4)를 입력하여 노드를 추가한다.
	*/
	////////////////////////////////////////////////////////////
	class CUList
	{
	public:
		// 생성자, 소멸자
		CUList( int arg_verbose = 0 );
		~CUList();

	public:
		long GetSize();
		bool IsEmpty();

		// 추가
		void Verbose( int arg_verbose = 0 );
		long PushFront( void* push_data, short data_size );
		long PushBack( void* push_data, short data_size );
		long PushFront( char* push_data );
		long PushBack( char* push_data );

		bool PopFront( void *ret_data);
		bool PopBack( void *ret_data);
		bool PopAt( long nPos, void *ret_data );
		bool GetAt( long nPos, void *ret_data );

		void Clear();
		bool GetCurNodeData( void *ret_data );
		void MoveToStart();
		void MoveToEnd();
		bool MoveToNext();
		bool MoveToPrev();

	private:
		long size;	///< 리스트 크기
		CUListNode *head;	///< 리스트의 처음 노드
		CUListNode *tail;	///< 리스트의 마지막 노드
		CUListNode *cur_node;	///< 현재 선택된 노드
		int verbose;	///< msg 출력 모드
	};


}
#endif

