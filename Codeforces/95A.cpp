#include <algorithm>
#include <string>
#include <cstring>
#include <iostream>
#define repn( i , a , b ) for( int i = ( int ) a  ; i < ( int ) b ; i ++ )
#define rep( i , a ) repn( i , 0 , a )

using namespace std;

bool is_upper( char c ){
	return c >= 'A' and c <= 'Z';
}

char change_case( char c ){
	if( is_upper( c ) ) 	return c - 'A' + 'a';
	return c - 'a' + 'A';
}

void change_case_all( string s ){
	rep( i , s.size() ) 
		cout << change_case( s[ i ] );
	cout << endl;
}

int main(){
	string s;
	cin >> s;
	bool is_first_upper = is_upper( s[ 0 ] );
	bool is_all_upper = true;
	repn( i , 1 ,  s.size() ) if( !is_upper( s[ i ] ) ) {
		is_all_upper = false ; break ; 
	}
	if( is_all_upper )	change_case_all( s ) ; 
	else	cout << s << endl;
	return 0;
}	
