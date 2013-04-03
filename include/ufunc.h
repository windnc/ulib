#ifndef ___ufunc___
#define ___ufunc___
#include <stdio.h>
#include <string.h>
#include "ustring.h"
#include "utextfile.h"

// ㅁ
namespace ulib {

bool LoadTextFile( char filename[], CUString &file_content );
bool GetElementByBoundTag( CUString &str, CUString &ret, char start[], char end[] );

CUString Bool2Str( bool expr );
bool Str2Bool( CUString str );
int Str2Int ( CUString str );
double Str2Real( CUString str );

}

#endif

