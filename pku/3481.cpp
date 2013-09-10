#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <numeric>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

struct back_queue{
	set< pii > queue;
	back_queue(){}
	void insert( int nr , int pry ){
		queue.insert( pii( pry , nr ) );
	}
	int serve( int n ){
		if( queue.empty() ) return 0; 
		pii ans = n ? *queue.rbegin() : *queue.begin();
		queue.erase( ans );
		return ans.snd;
	}
} b_queue;

int main(){
	int op = 0;
	int nr , py , ans;
	while( scanf("%d" , &op ) and op ){
		char ch_op = '0' + op;
		switch( ch_op ){
			case '1' :
				scanf("%d %d" , &nr , &py);
				b_queue.insert( nr , py );
				break;
			case '2' :
			case '3' :
				ans = b_queue.serve( ch_op - '2' );
				printf("%d\n" , ans);
				break;
		}
	}
	return 0;
}

