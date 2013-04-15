CC=g++
CFLAGS=-O2 -Wall -Wno-write-strings
OBJECT=../lib/ulib.a

all: 
	${CC} ${CFLAGS} -o ujson_test ./ujson_test.cpp -I../include ${OBJECT}
	

test:
	${CC} ${CFLAGS} -o ustringtree_test ./ustringtree_test.cpp -I../include ${OBJECT}
	${CC} ${CFLAGS} -o ustringlist_test ./ustringlist_test.cpp -I../include ${OBJECT}
	${CC} ${CFLAGS} -o ulist_test ./ulist_test.cpp -I../include ${OBJECT}
	${CC} ${CFLAGS} -o utree_test ./utree_test.cpp -I../include ${OBJECT}
	${CC} ${CFLAGS} -o ustringnode_test ./ustringnode_test.cpp -I../include ${OBJECT}
	${CC} ${CFLAGS} -o unode_test ./unode_test.cpp -I../include ${OBJECT}
	${CC} ${CFLAGS} -o ustring_test ./ustring_test.cpp -I../include ${OBJECT}
	${CC} ${CFLAGS} -o ustringlistro_test ./ustringlistro_test.cpp -I../include ${OBJECT}
	${CC} ${CFLAGS} -o uprogress_test ./uprogress_test.cpp -I../include ${OBJECT}
	${CC} ${CFLAGS} -o umath_test ./umath_test.cpp -I../include ${OBJECT}
	${CC} ${CFLAGS} -o uindexfile_test ./uindexfile_test.cpp -I../include ${OBJECT}
	${CC} ${CFLAGS} -o uoption_test ./uoption_test.cpp -I../include ${OBJECT}
#	${CC} ${CFLAGS} -o ustringmap_test ./ustringmap_test.cpp ustringmap.cpp -I../include ${OBJECT}
#	${CC} ${CFLAGS} -o ustringvec_test ./ustringvec_test.cpp ustringvec.cpp -I../include ${OBJECT} 
#	${CC} ${CFLAGS} -o ustringmatrix_test ./ustringmatrix_test.cpp ../ufile/utextfile.cpp ustringmatrix.cpp ustringlist.cpp ustringlistsn.cpp -I../include ${OBJECT} 
#	${CC} ${CFLAGS} -o uhtmlstring_test ./uhtmlstring_test.cpp uhtmlstring.cpp ../ufile/utextfile.cpp ustringlist.cpp ustringlistsn.cpp -I../include ${OBJECT} 

clean:
	rm -rf ustring_test ustringlist_test ustringlistro_test
	rm -rf uprogress_test
	rm -rf umath_test uindexfile_test tiny.uidx-*

# ㅁ
