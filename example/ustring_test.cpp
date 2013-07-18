#include "ulib.h"
using namespace ulib;

void test_basic()
{
	printf( ">>>>>>>>> 기본\n" );
	CUString str="^^ 안녕하세요ㅋㅋㅋ^^";
	printf( "문자열:%s\n", str.GetStr() );
	printf( "문자열 길이(바이트):%d\n", str.GetLength());
	printf( "문자열 글자수:%d\n", str.GetCharLength() );
	printf( "\n" );
}


void test_substr()
{

	printf( ">>>>>>>>> 문자열 자르기\n" );
	CUString str="^^ 안녕하세요ㅋㅋㅋ-_-";
	printf( "문자열:%s\n", str.GetStr() );
	printf( "Left(2):%s\n", str.Left(2).GetStr() );
	printf( "Mid(4):%s\n", str.Mid(2).GetStr() );
	printf( "Right(3):%s\n", str.Right(3).GetStr() );
	printf( "SubStr(5,9):%s\n", str.SubStr(5,9).GetStr() );

	printf( "\n" );
}


void test_find()
{
	printf( ">>>>>>>>> 문자열 검색, 치환\n" );

	CUString str="^^ 안녕하세요 english Mixed ㅋㅋㅋ-_-";
	printf( "문자열:%s\n", str.GetStr() );

	int idx = str.Find( "APPLE" );
	if( idx < 0 )	{
		printf( "검색 실패: APPLE\n" );
	}
	else	{
		printf( "검색 성공: %d\n", idx );
	}

	CUString tmp="하세";
	idx = str.Find( tmp );
	if( idx < 0 )	{
		printf( "검색 실패: %s %d\n", tmp.GetStr(), idx );
	}
	else	{
		printf( "검색 성공: %s at %d\n", tmp.GetStr(), idx );
	}

	tmp = "H M";
	idx = str.FindCasefree( tmp );
	if( idx < 0 )	{
		printf( "검색 실패: %s\n", tmp.GetStr() );
	}
	else	{
		printf( "검색 성공: %s at %d\n", tmp.GetStr(), idx );
	}



	str.Replace("ㅋㅋㅋ", "ㅎㅎㅎ" );
	printf( "치환:%s\n", str.GetStr() );

	str.Replace("english", "한국어", true );
	printf( "치환:%s\n", str.GetStr() );
	
	printf( "\n" );
}


void test_capital()
{
	printf( ">>>>>>>>> 대소문자\n" );
	CUString str="Hello. 안녕하세요 CUString";
	printf( "문자열:%s\n", str.GetStr() );
	
	str.MakeToLower();
	printf( "MakeToLower:%s\n", str.GetStr() );
	str.MakeToUpper();
	printf( "MakeToUpper:%s\n", str.GetStr() );
	printf( "\n" );
}

void test_operator()
{
	printf( ">>>>>>>>> 연산자\n" );
	CUString str1 ="hello";
	CUString str2 = "bye";
	printf( "문자열1:%s\n", str1.GetStr() );
	printf( "문자열2:%s\n", str2.GetStr() );

	// +
	CUString str = str1 + str2;
	printf( "operator +: %s\n", str.GetStr() );

	// +=
	str += " ^^;";
	printf( "operator +=: %s\n", str.GetStr() );

	// ==
	printf( "operator ==: " );
	str = "hello";
	if( str == "hello" )	{
		printf( "%s == hello\n", str.GetStr() );
	}

	// +=
	printf( "operator !=: " );
	str = "hello";
	if( str != "___" )	{
		printf( "%s != ___\n", str.GetStr() );
	}
	printf( "\n" );
}

void test_debug()
{
	CUString t= "ab안녕하세요cd";
	printf( "%s\n", t.GetStr() );
	printf( "%d\n", t.GetLength() );
	printf( "%d\n", t.GetCharLength() );

	CUString str_org = "adk안녕하세요zzz";
	CUString str = str_org.GetChar(-2);
	printf( "[%s]\n", str.GetStr() );


	CUString str_org2 = "adk안녕하세요zzz";
	CUString str2 = str_org2.GetChars(-2,2);
	printf( "[%s]\n", str2.GetStr() );

	CUString str_org3 = "adk안녕하세요zzz";
	int diff = str_org3.DeleteChars(3,400);
	printf( "[%s]%d\n", str_org3.GetStr(), diff );

	CUString rev_test = "abcd1a234";
	int find = rev_test.ReverseFind( '4' );
	printf( "[%s]%d\n", rev_test.GetStr(), find );

	str = "a   b";
	str.Replace( "  ", "  " );
	printf( "%s\n", str.GetStr() );
}


void test_checknum()
{
	printf( ">>>>>>>>> 숫자체크\n" );
	CUString str;
	str="123344";
	if(str.IsNumber() )	{
		fprintf(stderr, "%s is number\n", str.GetStr() );
	}
	else	{
		fprintf(stderr, "%s is not number\n", str.GetStr() );
	}

	str="12,344";
	if(str.IsNumber() )	{
		fprintf(stderr, "%s is number\n", str.GetStr() );
	}
	else	{
		fprintf(stderr, "%s is not number\n", str.GetStr() );
	}

	str="1344하이";
	if(str.IsNumber() )	{
		fprintf(stderr, "%s is number\n", str.GetStr() );
	}
	else	{
		fprintf(stderr, "%s is not number\n", str.GetStr() );
	}
	printf( "\n" );
	
}

void replace_test()
{
	CUString str;
	str = "hello this is my ... ";
	str = "abababab___";
	int num = str.Replace( "aba", "$" );
	str.Print( stderr );
	fprintf( stderr, "%s[%d]\n",str.GetStr(), num );

}


void test_trim()
{
	printf( ">>>>>>>>> Trim 테스트\n" );
	CUString str="^^ 안녕하세요ㅋㅋㅋ^^";
	CUString str_left = str;
	str_left.TrimLeft( "^\r;a\n" );
	printf( "TrimLeft:%s\n", str_left.GetStr() );

	CUString str_right = str;
	str_right.TrimRight( "^\r;a\n" );
	printf( "TrimRight:%s\n", str_right.GetStr() );
	CUString result_line;
	printf( "\n" );
}

void test_replace()
{
	printf( ">>>>>>>>> Replace 테스트\n" );
	CUString str;
	str = "hello this is my ... ";
	int num = str.Replace( "...", "" );
	str.Print( stderr );
	fprintf( stderr, "%s[%d]\n",str.GetStr(), num );
	printf( "\n" );
}


void test_alpha()
{
	printf( ">>>>>>>>> Alpha, Num, Ascii \n" );

	CUString str[10];
	str[0] = "hello";
	str[1] = "안녕하세요";
	str[2] = "10,233";
	str[3] = "4E-10";
	str[4] = "-32.32";
	str[5] = "이런건???23";
	str[6] = "★";


	for( int i=0; i<7; i++ )	{
	
		fprintf( stderr, "String: %s\n   ", str[i].GetStr() );
		if( str[i].IsNumber() == true )	{
			fprintf( stderr, "IsNumber : O   " );
		}
		else	{
			fprintf( stderr, "IsNumber : X   " );
		}

		if( str[i].IsASCII() == true )	{
			fprintf( stderr, "IsASCII: O   " );
		}
		else	{
			fprintf( stderr, "IsASCII: X   " );
		}

		if( str[i].IsAlpha() == true )	{
			fprintf( stderr, "IsAlpha: O   " );
		}
		else	{
			fprintf( stderr, "IsAlpha: X   " );
		}
		fprintf( stderr, "\n" );

	}

	printf( "\n" );

}

void test_remove()
{
	printf( ">>>>>>>>> remove\n" );
	CUString str( "abc de  eefa dsfjlk " );

	fprintf( stderr, "%s\n", str.GetStr() );
	str.Remove( "  " );
	fprintf( stderr, "%s\n", str.GetStr() );
	printf( "\n" );

}

void test_color()
{
	printf( ">>>>>>>>> color\n" );

	CUString str[16];
	for( int i=0; i<16; i++ )	{
		str[i] = "colored text ";
	}


	str[0].SetColor( "black" ); 	str[1].SetColor( "dark_gray" );
	str[2].SetColor( "gray" ); 		str[3].SetColor( "white" );
	str[4].SetColor( "red" ); 		str[5].SetColor( "light_red" );
	str[6].SetColor( "green" );		str[7].SetColor( "light_green" );
	str[8].SetColor( "brown" );		str[9].SetColor( "yellow" );
	str[10].SetColor( "blue" );		str[11].SetColor( "light_blue" );
	str[12].SetColor( "magenta" );	str[13].SetColor( "light_magenta" );
	str[14].SetColor( "cyan" );		str[15].SetColor( "light_cyan" );


	str[0] = CUString("black: " ) + str[0];
	str[1] = CUString("dgray: " ) + str[1];
	str[2] = CUString("gray: " ) + str[2];
	str[3] = CUString("white: " ) + str[3];
	str[4] = CUString("red: " ) + str[4];
	str[5] = CUString("light_red: " ) + str[5];
	str[6] = CUString("green: " ) + str[6];
	str[7] = CUString("light_green: " ) + str[7];
	str[8] = CUString("brown: " ) + str[8];
	str[9] = CUString("yellow: " ) + str[9];
	str[10] = CUString("blue: " ) + str[10];
	str[11] = CUString("light_blue: " ) + str[11];
	str[12] = CUString("magenta: " ) + str[12];
	str[13] = CUString("light_magenta: " ) + str[13];
	str[14] = CUString("cyan: " ) + str[14];
	str[15] = CUString("light_cyan: " ) + str[15];

	for( int i=0; i<16; i++ )	{
		str[i].Print();
	}
}

void test_format()
{
	printf( ">>>>>>>>> format\n" );
//	CUString str = "1234325323243";
//	SetNumberFormat();

	unsigned long num;
	CUString num_str;
	CUString file_str;
	num = 102;
	num_str.NumberFormat( num, num_str );
	file_str.FileSizeFormat( num, file_str );
	fprintf( stderr, "file: %ld -> %s %s\n", num, file_str.GetStr(), num_str.GetStr() );
	num = 20122;
	num_str.NumberFormat( num, num_str );
	file_str.FileSizeFormat( num, file_str );
	fprintf( stderr, "file: %ld -> %s %s\n", num, file_str.GetStr(), num_str.GetStr() );
	num = 4320122;
	num_str.NumberFormat( num, num_str );
	file_str.FileSizeFormat( num, file_str );
	fprintf( stderr, "file: %ld -> %s %s\n", num, file_str.GetStr(), num_str.GetStr() );
	num = 884320122;
	num_str.NumberFormat( num, num_str );
	file_str.FileSizeFormat( num, file_str );
	fprintf( stderr, "file: %ld -> %s %s\n", num, file_str.GetStr(), num_str.GetStr() );
	num = 5024320122;
	num_str.NumberFormat( num, num_str );
	file_str.FileSizeFormat( num, file_str );
	fprintf( stderr, "file: %ld -> %s %s\n", num, file_str.GetStr(), num_str.GetStr() );
	num = 60508824320122;
	num_str.NumberFormat( num, num_str );
	file_str.FileSizeFormat( num, file_str );
	fprintf( stderr, "file: %ld -> %s %s\n", num, file_str.GetStr(), num_str.GetStr() );
}

void test_del()
{
	CUString str = "hello<TAG>this should be deleted.</TAG>bye and <TAG>this also</TAG>bye";

	fprintf( stderr, "before:%s\n", str.GetStr() );
	int cnt = str.DeleteBoundTag( "<TAG>", "</TAG>" );
	fprintf( stderr, "after :%s\n%d", str.GetStr(), cnt );
	fprintf( stderr, "\n");
	fprintf( stderr, "\n");
	

}

void test_release()
{
	vector<CUString> vec_str;
	for( int i=0; i<10; i++ ) {
		CUString s = "tmp";
		vec_str.push_back( s );
	}
}

int main()
{
	test_basic();
	test_substr();
	test_find();
	test_capital();
	test_operator();
	test_checknum();
	test_trim();
	test_replace();

	test_alpha();

	test_remove();

	test_color();
	test_format();
	//test_debug();
	
	test_del();

	test_release();
	return 0;
}


// EOF ㅁ
