#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int countN[ 10 ];

void add( int nr ){
	while( nr ){
		countN[ nr % 10 ]++;
		nr /=10;
	}
}

int main(){
	int test;
	cin >> test;
	while ( test-- ){
		memset( countN , 0 , sizeof countN );
		int nr;
		cin >> nr;
		for( int i = 1 ; i <= nr ; i ++ )
			add( i );
		for( int i = 0 ; i < 10 ; i++ ){
			printf( "%d%c" , countN[ i ]  , i == 9 ? '\n': ' ');
		}
	}
	return 0;
}
