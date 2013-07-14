#include "ulib.h"
using namespace ulib;

void func1()
{
	char *buf = "Hello";
	CUniString str( buf, "ASCII" );
	fprintf( stderr, "Length: %d\n", str.GetLength() );
	fprintf( stderr, "# Uni Char: %d\n", str.GetNumUniChar() );


	CUTextFile file( "unistring_test.euckr", "r" );
	CUString bufstr;
	file.LoadToStr( bufstr );
	CUniString str_euckr( bufstr.GetStr(), "EUCKR" );
	fprintf( stderr, "Length: %d\n", str_euckr.GetLength() );
	fprintf( stderr, "# Uni Char: %d\n", str_euckr.GetNumUniChar() );
//	str_euckr.Print( stdout );

	char *buf2 = "He\\u0042ul\\u03B1lo \\ud638&\\uac10";
	CUniString str_aeu( buf2, "AsciiEscapedUnicode" );
	fprintf( stderr, "Length: %d\n", str_aeu.GetLength() );
	fprintf( stderr, "# Uni Char: %d\n", str_aeu.GetNumUniChar() );
	str_aeu.Print( stdout );


	CUTextFile file2( "unistring_test.json", "r" );
	CUString bufstr2;
	file2.LoadToStr( bufstr2 );
	CUniString str_json ( bufstr2.GetStr(), "AEU" );
	fprintf( stderr, "Length: %d\n", str_json.GetLength() );
	fprintf( stderr, "# Uni Char: %d\n", str_json.GetNumUniChar() );
	str_json.Print( stdout );

	CUTextFile file3( "unistring_test.aeu", "r" );
	CUString bufstr3;
	file3.LoadToStr( bufstr3 );
	CUniString str_aeu2( bufstr3.GetStr(), "AEU" );
	fprintf( stderr, "Length: %d\n", str_aeu2.GetLength() );
	fprintf( stderr, "# Uni Char: %d\n", str_aeu2.GetNumUniChar() );
	str_aeu2.Print( stdout );
	fprintf( stderr, "%s\n", str_aeu2.GetEncStr() );
}


int main()
{
	func1();
}

// EOF ㅁ

