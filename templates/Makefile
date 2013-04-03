CC=g++
CFLAGS=-O2 -Wno-write-strings

ULIB_DIR=`echo ~`/.lib/ulib/

ULIB_INC=-I${ULIB_DIR}include
ULIB_OBJ=${ULIB_DIR}lib/ulib.a

all:    
#	${CC} ${CFLAGS} txtfile.cpp -o txtfile ${ULIB_OBJ} ${ULIB_INC}
#	${CC} ${CFLAGS} txtfilemem.cpp -o txtfilemem ${ULIB_OBJ} ${ULIB_INC}
#	${CC} ${CFLAGS} flist.cpp -o flist ${ULIB_OBJ} ${ULIB_INC}
#	${CC} ${CFLAGS} dirproc.cpp -o dirproc ${ULIB_OBJ} ${ULIB_INC}
#	${CC} ${CFLAGS} confproc.cpp -o confproc ${ULIB_OBJ} ${ULIB_INC}

.cpp.o:
	${CC} ${CFLAGS} -c $< -o $*.o ${ULIB_INC} ${ULIB_OBJ}

clean:
	rm -rf *.o
	rm -rf txtfile
	rm -rf txtfilemem
	rm -rf flist
	rm -rf dirproc 
	rm -rf confproc 

# ㅁ