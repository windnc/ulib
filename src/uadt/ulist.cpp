/**
	@file		ulist.cpp
	@brief		ulist cpp
	@author		swlee
	@date		Jul. 15, 2006 ~
	@version	0.7
	@todo		
	@warning	
	@bug		
*/
#include "ulist.h"

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
	CUListNode::CUListNode( void *arg_data, short arg_data_size )	
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
		@brief	소멸자
	*/
	////////////////////////////////////////////////////////////
	inline CUListNode::~CUListNode()
	{
		// dealloc
		if( data )	free(data);
	} 

	////////////////////////////////////////////////////////////
	/**
		@brief	data를 구함
		@return	data의 시작 주소를 리턴
	*/
	////////////////////////////////////////////////////////////
	inline void *CUListNode::GetData()
	{
		if( data == NULL )	return NULL;
		else				return data;
	} 


	////////////////////////////////////////////////////////////
	/**
		@brief	다음 node가 있는지 체크
		@return	있다면 true
	*/
	////////////////////////////////////////////////////////////
	inline bool CUListNode::HaveNext()
	{
		if( next == NULL )	return false;
		else				return true;
	} 


	////////////////////////////////////////////////////////////
	/**
		@brief	이전 node가 있는지 체크
		@return	있다면 true
	*/
	////////////////////////////////////////////////////////////
	inline bool CUListNode::HavePrev()
	{
		if( prev == NULL )	return false;
		else				return true;
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
	CUList::CUList( int arg_verbose )
	{
		Verbose( arg_verbose );
		if( verbose >= 1)	{
			printf( "CUList Create ... \n" ); fflush( stdout );
		}

		head = new CUListNode( (void*)"head", strlen("head")+1 );	
		tail = new CUListNode( (void*)"tail", strlen("tail")+1 );
		head->prev = NULL;
		head->next = tail;
		tail->prev = head;
		tail->next = NULL;
		cur_node = head;
		size = 0;	

		if( verbose >= 1)	{
			printf( "CUList Create ... [OK]\n" ); fflush( stdout );
		}
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	소멸자
	*/
	////////////////////////////////////////////////////////////
	CUList::~CUList()
	{
		if( verbose >= 1)	{
			printf( "CUList Release ... \n" ); fflush( stdout );
		}

		Clear();
		if(	head )	delete head;
		if( tail )	delete tail;

		if( verbose >= 1)	{
			printf( "CUList Release ... [OK]\n" ); fflush( stdout );
		}
		
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	메시지를 화면에 출력할 정도를 설정
		@param	arg_verbose 메시지를 화면에 출력할 정도
		@note	0 : 출력 안함\n
				1 : 생성, 해제, Clear 상황을 출력\n
				2 : Push, Pop 상황을 출력\n
		@see	CUList()
	*/
	////////////////////////////////////////////////////////////
	inline void CUList::Verbose( int arg_verbose )
	{
		verbose = arg_verbose;
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	비어있는지 체크
		@return	비어있다면 true
		@see	GetSize(), Clear()
	*/
	////////////////////////////////////////////////////////////
	bool CUList::IsEmpty()
	{
		if( size <= 0 )	return true;
		return false;
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	char *를 list의 제일 앞에 추가
		@param	push_data	추가할 char *
		@see	PushBack(), PopFront()
	*/
	////////////////////////////////////////////////////////////
	long CUList::PushFront( char* push_data )	
	{
		return PushFront( (void *)push_data, strlen( push_data ) +1 );
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	data를 list의 제일 앞에 추가
		@param	push_data	추가할 data의 시작 주소
		@param	data_size	추가할 data의 크기
		@see	PushBack(), PopFront()
	*/
	////////////////////////////////////////////////////////////
	long CUList::PushFront( void* push_data, short data_size )	
	{
		if( verbose >= 2)	{
			printf( "CUList PushFront... \n" ); fflush( stdout );
		}

		CUListNode *new_node = new CUListNode( push_data, data_size );
		new_node->next = head->next;
		new_node->prev = head;
		head->next = new_node;
		new_node->next->prev = new_node;
		size++;

		if( verbose >= 2)	{
			printf( "CUList PushFront... [OK]\n" ); fflush( stdout );
		}
		return size;
	}


	////////////////////////////////////////////////////////////
	/**
		@brief char*를 list의 제일 뒤에 추가
		@param	push_data	추가할 char *
		@see	PushFront(), PopBack()
	*/
	////////////////////////////////////////////////////////////
	long CUList::PushBack( char* push_data )	
	{
		return PushBack( (void *)push_data, strlen(push_data)+1 );
	}


	////////////////////////////////////////////////////////////
	/**
		@brief data를 list의 제일 뒤에 추가
		@param	push_data	추가할 data의 시작 주소
		@param	data_size	추가할 data의 크기
		@see	PushFront(), PopFront()
	*/
	////////////////////////////////////////////////////////////
	long CUList::PushBack( void* push_data, short data_size )
	{
		if( verbose >= 2)	{
			printf( "CUList PushBack... \n" ); fflush( stdout );
		}

		CUListNode *new_node = new CUListNode( push_data, data_size );
		CUListNode *last_node = tail->prev;
		last_node->next = new_node;
		new_node->prev = last_node;
		new_node->next = tail;
		tail->prev = new_node;
		size++;

		if( verbose >= 2)	{
			printf( "CUList PushBack... [OK]\n" ); fflush( stdout );
		}
		return size;
	}


	////////////////////////////////////////////////////////////
	/**
		@brief 현재 선택된 node의 data를 구함
		@param	ret_data	결과를 복사할 data의 시작 주소
		@return		선택된 node가 있다면 true
	*/
	////////////////////////////////////////////////////////////
	bool CUList::GetCurNodeData( void *ret_data )
	{
		if( cur_node == NULL )	return false;
		else	{
			memcpy( ret_data, cur_node->data, cur_node->data_size );
			return true;
		}
	}

	////////////////////////////////////////////////////////////
	/**
		@brief List의 제일 처음 node를 가리키게 설정
		@see	MoveToEnd(),  MoveToPrev(), MoveToNext()
	*/
	////////////////////////////////////////////////////////////
	void CUList::MoveToStart()
	{
		cur_node = head;
	}


	////////////////////////////////////////////////////////////
	/**
		@brief list의 제일 끝 node를 가리키게 설정
		@see	MoveToStart(), MoveToPrev(), MoveToNext()
	*/
	////////////////////////////////////////////////////////////
	void CUList::MoveToEnd()
	{
		cur_node = tail;
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	다음 node를 가리키게 설정
		@see	MoveToPrev(), MoveToStart(), MoveToEnd()
	*/
	////////////////////////////////////////////////////////////
	bool CUList::MoveToNext()
	{
		if( cur_node->HaveNext() )	{
			if( cur_node->next == tail )	{
				return false;
			}
			else	{
				cur_node = cur_node->next;
				return true;
			}
		}
		else	{
			return false;
		}
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	이전 node를 가리키게 설정
		@see	MoveToNext(), MoveToStart(), MoveToEnd()
	*/
	////////////////////////////////////////////////////////////
	bool CUList::MoveToPrev()
	{
		if( cur_node->HavePrev() )	{
			if( cur_node->prev == head )	{
				return false;
			}
			else	{
				cur_node = cur_node->prev;
				return true;
			}
		}
		else	{
			return false;
		}
	}




	////////////////////////////////////////////////////////////
	/**
		@brief	임의의 위치의 node의 data를 가져옴
		@param	nPos	구할 위치
		@param	ret_data	결과를 복사할 data의 시작 주소
		@return	list 안에 있는 node라면 true
		@see	PopAt()
	*/
	////////////////////////////////////////////////////////////
	bool CUList::GetAt( long nPos, void *ret_data )	
	{
		if( IsEmpty() )	return false;
		if( nPos < 0 )	return false;
		if( nPos >= GetSize() )	return false;

		long now = 0;
		CUListNode *tmp_node = head->next;
		while( tmp_node != tail )	{
			if( now >= nPos )	break;
			tmp_node = tmp_node->next;
			now++;
		}
		if( tmp_node == NULL )	return false;
		else	{
			memcpy( ret_data, tmp_node->data, tmp_node->data_size );
			return true;
		}
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	임의의 위치의 node의 data를 가져오고 list에서 삭제
		@param	nPos	구할 위치
		@param	ret_data	결과를 복사할 data의 시작 주소
		@return	list 안에 있는 node라면 true
		@see	GetAt()
	*/
	////////////////////////////////////////////////////////////
	bool CUList::PopAt( long nPos, void *ret_data )	
	{
		if( verbose >= 2)	{
			printf( "CUList PopAt... \n" ); fflush( stdout );
		}

		// check
		if( nPos < 0 )	return false;
		if( nPos >= GetSize() )	return false;
		
		// find
		long now = 0;
		CUListNode *tmp_node = head->next;
		if( tmp_node == tail )	return false;
		
		while( tmp_node != tail )	{
			if( now >= nPos )	break;
			tmp_node = tmp_node->next;
			now++;
		}
		if( tmp_node == NULL )	return false;
		

		// copy
		//ret_data = malloc( tmp_node->data_size);
		memcpy( ret_data, tmp_node->data, tmp_node->data_size );

		// delete
		tmp_node->prev->next = tmp_node->next;
		tmp_node->next->prev = tmp_node->prev;
		delete tmp_node;

		size--;

		if( verbose >= 2)	{
			printf( "CUList PopAt... [OK]\n" ); fflush( stdout );
		}

		return true;
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	처음 node의 data를 가져오고 list에서 삭제
		@param	ret_data	결과를 복사할 data의 시작 주소
		@return	list가 비어있지 않다면 true
		@see	PopBack(), PopAt()
	*/
	////////////////////////////////////////////////////////////
	bool CUList::PopFront( void *ret_data )
	{
		if( verbose >= 2)	{
			printf( "CUList PopFront... \n" ); fflush( stdout );
		}

		// check
		if( IsEmpty() )	return false;

		// copy
		CUListNode *first_node = head->next;
		if( first_node == NULL )	return false;
		if( first_node == tail )	return false;
		memcpy( ret_data, first_node->data, first_node->data_size );
		
		// del
		head->next = first_node->next;
		first_node->next->prev = head;
		delete  first_node;
		size--;

		if( verbose >= 2)	{
			printf( "CUList PopFront... [OK]\n" ); fflush( stdout );
		}
		return true;
	}

	////////////////////////////////////////////////////////////
	/**
		@brief	마지막 node의 data를 가져오고 list에서 삭제
		@param	ret_data	결과를 복사할 data의 시작 주소
		@return	list가 비어있지 않다면 true
		@see	PopFront(), PopAt()
	*/
	////////////////////////////////////////////////////////////
	bool CUList::PopBack( void *ret_data)	
	{
		if( verbose >= 2)	{
			printf( "CUList PopBack... \n" ); fflush( stdout );
		}

		// check
		if( IsEmpty() )	return false;

		// copy
		CUListNode *last_node = tail->prev;
		if( last_node == NULL )	return false;
		if( last_node == head )	return false;
		memcpy( ret_data, last_node->data, last_node->data_size );
		
		// del
		tail->prev = last_node->prev;
		last_node->prev->next = tail;
		delete  last_node;
		size--;

		if( verbose >= 2)	{
			printf( "CUList PopBack... [OK]\n" ); fflush( stdout );
		}

		return true;
	}


	////////////////////////////////////////////
	/**
		@brief	list를 비움
	*/
	////////////////////////////////////////////
	void CUList::Clear()	
	{
		if( verbose >= 1)	{
			printf( "CUList Clear ... \n" ); fflush( stdout );
		}

		CUListNode *tmp_node = head->next;
		while( tmp_node != tail )	{
			CUListNode *del_node = tmp_node;
			tmp_node = tmp_node->next;
			delete del_node;
		}

		head->next = tail;
		tail->prev = head;
		size = 0;

		if( verbose >= 1)	{
			printf( "CUList Clear ... [OK]\n" ); fflush( stdout );
		}
	}

	////////////////////////////////////////////
	/**
		@brief	list의 크기를 구함
		@return	list의 lode수
	*/
	////////////////////////////////////////////
	long CUList::GetSize()
	{
		return size;
	}
}

// EOF

