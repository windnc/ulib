/**
	@file		ustringdic.cpp
	@brief		ustringdiccpp
	@author		swlee
	@date		July. 11, 2013 ~
	@version	0.1
	@todo		
	@warning	
	@bug		
*/
#include "ustringdic.h"

namespace ulib
{

	////////////////////////////////////////////////////////////
	/**
		@brief	생성자
	*/
	////////////////////////////////////////////////////////////
	CUStringDic::CUStringDic()
	{
	}


	////////////////////////////////////////////////////////////
	/**
		@brief	소멸자
	*/
	////////////////////////////////////////////////////////////
	CUStringDic::~CUStringDic()
	{
		Clear();
	} 


	////////////////////////////////////////////////////////////
	void CUStringDic::Clear()
	{
	}


	////////////////////////////////////////////////////////////
	bool CUStringDic::Binarize( char *fn, char *out_prefix )
	{
		CUTextFile file( fn, "r" );
		if( file.IsOpen() == false )	return false;

		// check valid format
		int num_record = 0;
		vector<string> str_vec;
		while( true ) {
			CUString line;
			if( file.ReadLine( line ) == false ) break;

			int idx = line.Find("\t" );
			if( idx < 0 )	return false;

			line.SetAt( idx, '\0' );
			char *skey = line.GetStr();
			str_vec.push_back( skey );
			num_record++;
		}
		fprintf( stderr, "%d\n", num_record );


		// start to write
		vector<long> start_addr_vec;
		vector<long> end_addr_vec;
		char out_fn[1024];
		sprintf( out_fn, "%s.sdata", out_prefix );
		CUTextFile file_sdata( out_fn, "w" );
		if( file_sdata.IsOpen() == false )	{
			return false;
		}
		num_record = 0;
		file.MoveToStart();
		while( true ) {
			CUString line;
			if( file.ReadLine( line ) == false ) break;
			int idx = line.Find("\t" );

			line.SetAt( idx, '\0' );
			char *sdata = line.GetStr()+idx+1;

			start_addr_vec.push_back( ftell( file_sdata.GetFP() ));
			fprintf( file_sdata.GetFP(), "%s", sdata );
			end_addr_vec.push_back( ftell( file_sdata.GetFP() ));
			fprintf( file_sdata.GetFP(), "\n" );

			num_record++;
		}

		sprintf( out_fn, "%s.skey", out_prefix );
		CUTextFile file_skey( out_fn, "w" );
		if( file_skey.IsOpen() == false )	{
			return false;
		}

		list<int> begin_queue;
		list<int> end_queue;
		begin_queue.push_back( 0 );
		end_queue.push_back(str_vec.size()-1);
		while( true ) {
			if( begin_queue.size() == 0 )	break;

			int begin = begin_queue.front(); begin_queue.pop_front();
			int end = end_queue.front(); end_queue.pop_front();
			if( begin == end ) {
//				fprintf( stderr, "%d - %d %d \n", begin, end, begin );
				fprintf( file_skey.GetFP(), "%s\t%ld\t%ld\n",
						str_vec[ begin ].c_str(),
						start_addr_vec[ begin ],
						end_addr_vec[ begin] );
				continue;
			}
			else if( begin > end ) {
				continue;
			}
			int mid = begin+ ( (end-begin)/2 );
			//fprintf( stderr, "%d - %d %d\n", begin, end, mid );
			fprintf( file_skey.GetFP(), "%s\t%ld\t%ld\n",
					str_vec[ mid ].c_str(),
					start_addr_vec[ mid ],
					end_addr_vec[ mid ] );

			begin_queue.push_back( begin );
			end_queue.push_back( mid-1 );
			begin_queue.push_back( mid+1 );
			end_queue.push_back( end );
		}



		return true;


		/*


		file.MoveToStart();
		num_record = 0;
		while( true ) {
			CUString line;
			if( file.ReadLine( line ) == false ) break;

			int idx = line.Find("\t" );
			if( idx < 0 )	return false;




			//CUStringDicData &d = data_array[ num_record ];
			//d.skey = skey;
			//d.sdata = sdata;

			num_record++;

			// add leaf data to internal node
			if( num_record % MAX_CHILD == MAX_CHILD-1 ) {
				int parent_idx = num_record / (MAX_CHILD * MAX_CHILD );
				CUStringDicNode &parent = node_array[ parent_idx ];
				parent.AddData( skey );
			}

		}

		// propagate parent to root
		int first_idx = 0;
		int last_idx = num_record / (MAX_CHILD*MAX_CHILD);
		while( true ) {
			for( int i=first_idx; i<=last_idx; i++) {
				if( i % MAX_CHILD == MAX_CHILD-1 || i == last_idx ) {
					int parent_idx = last_idx + (i/MAX_CHILD/MAX_CHILD) + 1;
//					fprintf( stderr, "%d~%d %d %d\n", first_idx, last_idx, i, parent_idx );
					CUStringDicNode &parent = node_array[ parent_idx ];
					CUStringDicNode &child = node_array[ i ];
					parent.AddChild( child.GetLastBoundary(), i );
				}
			}

			break;
		}
		//fprintf( stderr, "%d\n", num_node );

		*/
		/*
		for( int i=0; i<num_node; i++ ) {
			CUStringDicNode &parent = node_array[ i ];
			if( parent.link_data == true ) {
				fprintf( stderr, "%d node\t%d\t", i, parent.num_child );
				for( int j=0; j<parent.num_child; j++ ) {
					fprintf( stderr, "%s  ", parent.boundary[j] );
				}
				fprintf( stderr, "\n" );
			}
		}
		*/

		/*
		for( int i=0; i<num_node; i++ ) {
			CUStringDicNode &parent = node_array[ i ];
			if( parent.link_data == false ) {
				fprintf( stderr, "%d node\t%d\t", i, parent.num_child );
				for( int j=0; j<parent.num_child; j++ ) {
					fprintf( stderr, "%s  ", parent.boundary[j] );
				}
				fprintf( stderr, "\n" );
			}
		}

		root = &node_array[ num_node-1 ];


		fprintf( stderr, "ROOT\n" );
		fprintf( stderr, "   %d\n", root->num_child );
		for( int i=0; i<root->num_child; i++ ) {
			fprintf( stderr, "   %s\n", root->boundary[i] );
		}
		*/

		return true;
	}

}

// EOF ㅁ

