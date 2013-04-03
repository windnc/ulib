CC=g++
CFLAGS=-O2 -Wall -Wno-write-strings
PREFIX=`echo ~`/.lib/ulib

OBJECTS  = src/ustring/ustring.o src/ustring/ustringlist.o src/ustring/ustringlistro.o
OBJECTS += src/uadt/ustack.o src/uadt/ulist.o 
OBJECTS += src/ufile/ufile.o src/ufile/udir.o src/ufile/utextfile.o 
OBJECTS += src/ufile/uflistfile.o src/ufile/uconfigfile.o
OBJECTS += src/uutil/uprogress.o src/uutil/ucounter.o src/uutil/umath.o 
OBJECTS += src/ufunc/ufunc.o 

INC = -Iinclude

# ㅁ
all:    ${OBJECTS} 
	mkdir -p lib
#	ar -rscv -o lib/ulib.a ${OBJECTS}
	ar -r lib/ulib.a ${OBJECTS}
	ranlib lib/ulib.a

ctags:
	ctags -R

install:
	mkdir -p ${PREFIX}
	rm -rf ${PREFIX}
	mkdir ${PREFIX}
	cp -R include ${PREFIX}
	mv ${PREFIX}/include/ulib.h.org ${PREFIX}/include/ulib.h
	cp -R lib ${PREFIX}
	rm -rf ${PREFIX}/include/.svn
	rm -rf ${PREFIX}/lib/.svn

.cpp.o:
	${CC} ${CFLAGS} -c $< -o $*.o ${INC}

clean:
	rm -rf tags
	rm -rf ${OBJECTS}
	rm -rf */*_test
	rm -rf lib/ulib.a
	rm -rf lib/ustring.a

