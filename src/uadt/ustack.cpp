/**
	@file		ustack.cpp
	@brief		ustack cpp
	@author		swlee
	@date		Jul. 15, 2006 ~
	@version	0.7
	@todo		
	@warning	
	@bug		
*/
#include "ustack.h"

namespace ulib {

	////////////////////////////////////////////////////////////
	/**
		@brief	생성자
		@param	arg_data	추가할 data의 시작 주소
		@param	arg_data_size	추가할 data의 크기
		@warning	추가하려는 data가 동적으로 생성되었을 때:\n
					arg_data_size는 pointer의 크기(4byte)를 넣어주면 됨.\n
					동적 data의 해제는 나중에 직접 해줘야 함.
	*/
	////////////////////////////////////////////////////////////
	CUStackNode::CUStackNode( void *arg_data, short arg_data_size )	
	{
		// init
		data = next = prev = NULL;	
		data_size = 0;
		
		// check
		if( arg_data_size  <= 0 )	return;

		// alloc
		if( !(data = malloc( arg_data_size ) ) )	return;
		
		// set
		if( !memcpy( data, arg_data, arg_data_size ) )	{
			free(data);
			data = NULL; 
			return;
		}
		data_size = arg_data_size;
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	생성자
		@param	arg_verbose	메시지를 화면에 출력할 정도
		@note	0 : 출력 안함\n
				1 : 생성, 해제, Clear 상황을 출력\n
				2 : Push, Pop 상황을 출력\n
		@see	Verbose()
	*/
	////////////////////////////////////////////////////////////
	CUStack::CUStack( int arg_verbose )
	{		
		Verbose( arg_verbose );

		if( verbose >= 1)	{
			printf( "CUStack Create... \n" ); fflush( stdout );
		}

		size = 0;	
		head = new CUStackNode( (void*)"head", strlen( "head" )+1 );
		top = head;

		if( verbose >= 1)	{
			printf( "CUStack Create... [OK]\n" ); fflush( stdout );
		}
		
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	소멸자
	*/
	////////////////////////////////////////////////////////////
	CUStack::~CUStack()
	{
		if( verbose >= 1)	{
			printf( "CUStack Release... \n" ); fflush( stdout );
		}

		if( head )	delete head;

		if( verbose >= 1)	{
			printf( "CUStack Release... [OK]\n" ); fflush( stdout );
		}
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	메시지를 화면에 출력할 정도를 설정
		@param	arg_verbose	메시지를 화면에 출력할 정도
		@note	0 : 출력 안함\n
				1 : 생성, 해제, Clear 상황을 출력\n
				2 : Push, Pop 상황을 출력\n
	*/
	////////////////////////////////////////////////////////////
	void CUStack::Verbose( int arg_verbose )
	{
		verbose = arg_verbose;
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	stack의 data 수를 구함
		@return	data 수를 리턴
		@see	Pop()
	*/	
	////////////////////////////////////////////////////////////
	long CUStack::GetSize()
	{	
		return size;	
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	stack의 최상위 data를 구함
		@param	ret_data	결과를 복사할 data의 시작 주소
		@return	stack이 비어있다면 false
		@see	Pop()
	*/	
	////////////////////////////////////////////////////////////

	bool CUStack::GetTop( void *ret_data )
	{
		if( size <= 0 )	return false;
		if( top == NULL )	return false;

		// copy
		memcpy( ret_data, top->data, top->data_size );
		
		return true;
	}

	////////////////////////////////////////////////////////////
	/**
		@brief	stack의 모든 node를 비움
	*/	
	////////////////////////////////////////////////////////////
	void CUStack::Clear()
	{
		if( verbose >= 2)	{
			printf( "CUStack Clear ... \n" ); fflush( stdout );
		}

		CUStackNode *tmp_node = top;
		while( tmp_node != head )	{
			CUStackNode *del_node = tmp_node;
			tmp_node = tmp_node->prev;
			delete del_node;
		}
		size = 0;

		if( verbose >= 2)	{
			printf( "CUStack Clear ... [OK]\n" ); fflush( stdout );
		}
	}

	////////////////////////////////////////////////////////////
	/**
		@brief	stack에 data 추가
		@param	arg_data	추가할 data의 시작 번지
		@param	arg_data_size	추가할 data의 크기
		@return	추가 후 총 data 수
		@see	Pop()
	*/
	////////////////////////////////////////////////////////////
	long CUStack::Push( void* arg_data, short arg_data_size )	
	{
		if( verbose >= 2)	{
			printf( "CUStack Push... \n" ); fflush( stdout );
		}

		CUStackNode *new_node = new CUStackNode( arg_data, arg_data_size );
		top->next = new_node;
		new_node->prev = top;

		top = top->next;
		size++;

		if( verbose >= 2)	{
			printf( "CUStack Push... [OK]\n" ); fflush( stdout );
		}

		return size;
	}

	////////////////////////////////////////////////////////////
	/**
		@brief	stack의 최상위 node의 data 복사하고 node를 삭제
		@param	ret_data	결과를 복사할 data의 시작 주소
		@return	stack이 비어있었다면 false
		@sa	Push()
	*/
	////////////////////////////////////////////////////////////
	bool CUStack::Pop( void *ret_data )	
	{
		if( verbose >= 2)	{
			printf( "CUStack Pop... \n" ); fflush( stdout );
		}

		if( size <= 0 )	return false;
		if( top == NULL )	return false;

		// copy
		memcpy( ret_data, top->data, top->data_size );
		
		// del
		top = top->prev;
		delete top->next;
		size--;

		if( verbose >= 2)	{
			printf( "CUStack Push... [OK]\n" ); fflush( stdout );
		}

		return true;
	}

}

// EOF
