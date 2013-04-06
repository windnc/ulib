CC=g++
CFLAGS=-O2 -Wall -Wno-write-strings
PREFIX=`echo ~`/.lib/ulib

OBJECTS  = src/ustring/ustring.o src/ustring/ustringlist.o src/ustring/ustringlistro.o
OBJECTS += src/uadt/ustack.o src/uadt/ulist.o src/uadt/utree.o src/uadt/unode.o src/uadt/ustringnode.o
OBJECTS += src/ufile/ufile.o src/ufile/udir.o src/ufile/utextfile.o 
OBJECTS += src/ufile/uflistfile.o src/ufile/uconfigfile.o src/ufile/uindexfile.o
OBJECTS += src/uutil/uprogress.o src/uutil/ucounter.o src/uutil/umath.o src/uutil/uoption.o
OBJECTS += src/uparser/uparser.o src/uparser/ujson.o
OBJECTS += src/ufunc/ufunc.o 

INC = -Iinclude

all:    ${OBJECTS} 
	mkdir -p lib
#	ar -rscv -o lib/ulib.a ${OBJECTS}
	ar -r lib/ulib.a ${OBJECTS}
	ranlib lib/ulib.a
	cd example; make; cd ..

ctags:
	ctags -R
	mv tags ${PREFIX}/
	@echo Add 'set tags+=${PREFIX}/tags' in your .vimrc

doxygen:
	doxygen doxygen/config.doxygen

install:
	mkdir -p ${PREFIX}
	rm -rf ${PREFIX}
	mkdir ${PREFIX}
	cp -R include ${PREFIX}
	cp -R lib ${PREFIX}

.cpp.o:
	${CC} ${CFLAGS} -c $< -o $*.o ${INC}

clean:
	rm -rf tags
	rm -rf ${OBJECTS}
	rm -rf */*_test
	rm -rf lib/ulib.a
	rm -rf lib/ustring.a

# ㅁ
