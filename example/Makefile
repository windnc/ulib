CC=g++
CFLAGS=-O2 -Wall -Wno-write-strings
OBJECT=../lib/ulib.a


all: 
	${CC} ${CFLAGS} -o ustring_test ./ustring_test.cpp -I../include ${OBJECT}
	${CC} ${CFLAGS} -o ustringlist_test ./ustringlist_test.cpp -I../include ${OBJECT}
	${CC} ${CFLAGS} -o ustringlistro_test ./ustringlistro_test.cpp -I../include ${OBJECT}
#	${CC} ${CFLAGS} -o ustringmap_test ./ustringmap_test.cpp ustringmap.cpp -I../include ${OBJECT}
#	${CC} ${CFLAGS} -o ustringvec_test ./ustringvec_test.cpp ustringvec.cpp -I../include ${OBJECT} 
#	${CC} ${CFLAGS} -o ustringmatrix_test ./ustringmatrix_test.cpp ../ufile/utextfile.cpp ustringmatrix.cpp ustringlist.cpp ustringlistsn.cpp -I../include ${OBJECT} 
#	${CC} ${CFLAGS} -o uhtmlstring_test ./uhtmlstring_test.cpp uhtmlstring.cpp ../ufile/utextfile.cpp ustringlist.cpp ustringlistsn.cpp -I../include ${OBJECT} 

clean:
	rm -rf ustring_test
	rm -rf ustringlist_test
	rm -rf ustringlistro_test

# ㅁ