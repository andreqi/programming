
#include<iostream>
#include<vector>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<set>
#define MAXN 100011
using namespace std;

typedef long long int64;
int64 b[ MAXN ];
int64 a[ MAXN ];
vector< int64 > divr;
int main(){
    int n;
    while ( scanf("%d", &n ) == 1 and n!= 0 ) {
        int64 cont = 0;
        for ( int i = 0 ; i <= n-1 ; i++ ) {
            int x;
			scanf("%d", &x );
            a[i] = x;
        }
        int64 div = a[0];
        for ( int i = 1 ; i <= n-1 ; i++ ) {
            div = __gcd ( div , a[i] );
        }
		divr.clear();
		for( int i = 1 ; i*i <= div ; i++ ) if( div % i == 0 ){ 
			int64 a = i , b = div / i ; 
			divr.push_back( a );
			if( a != b )
				divr.push_back( b );
		}
        for ( int i = 0 ; i < divr.size() ; i++){
			int r = divr[ i ];
            if ( div % r == 0 ) {
                for ( int i = 0 ; i <= n-1 ; i++){
                    b[i] = a[i] / r;
                }
                int m = b[0] % n;
                bool T = true;
                for ( int i = 1 ; i <= n-1 ; i++){
                    if ( b[i] % n != m){
                        T = false;
						break;
                    }
                }
                if ( T ) {
                    int64 min = b[0];
                    for ( int i = 1 ; i <= n-1 ; i++){
                        if( b[i] < min ) {
                            min = b[i];
                        }
                    }
                    if ( m == 0 ) {
                        cont = (int64)cont + (int64)( min/n ) - 1;
                    }
                    else{
                        cont = (int64)cont + (int64)( ( min - m ) / n );
                    }
                }
            }
        }
		printf("%lld\n" , cont );
    }
    return 0;
}
