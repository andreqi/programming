#include <cstring>
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;


char firsts[] = "adgjmptw";
int pressed( ){
	string buff;
	getline( cin , buff ) ;
	int ans = 0;
	for( int i = 0 , j ; i < buff.size() ; i++ ){
		if( buff[ i ] == ' ' ) ans ++;
		else{
			for( j = 7 ; j >= 0 ; j -- ) if( firsts[ j ] <= buff[ i ] )
				break;
			int val = buff[ i ] - firsts[ j ] ;
			ans += val + 1;
		}
	}
	return ans;
}
int main(){
	int test;
	cin >> test;
	string str;
	getline( cin , str );
	for( int cases = 1 ; cases <= test ; cases++ ){
		printf("Case #%d: %d\n" , cases , pressed() );
	}
	return 0;
}
