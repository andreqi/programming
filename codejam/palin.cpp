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

vector<int64> ans;
vector<int64> sqr;
int64 pot[20];
int query(int a , int b){
	int ans = 0;
	rep( i , sqr.size() ) if ( a <= sqr[i] and sqr[i] <= b ) ans++;
	return ans;
}
char buff[100];
int cumple(int64 x){
	int len = 0;
	while( x ){
		buff[len++] = x %10;
		x /= 10;
	}
	rep(i, len) if( buff[i] != buff[len - 1 - i] ) 
		return false;
	return true;
}

void generate(int len){
	if(len == 1){
		repn(i,1,10) ans.push_back(i);
		return;
	}
	int pt = len / 2;
	for( int64 fst = pot[pt-1]; fst < pot[pt]; fst++ ){
		if ( len % 2 ){
			rep(nr,10){
				int64 x = fst;
				int64 snd = fst * 10LL + nr;
				while ( x ){
					snd = snd * 10LL + x % 10;
					x /= 10LL;
				}
				ans.push_back(snd);
			}
		} else {
			int64 x = fst;
			int64 snd = fst;
			while ( x ){
				snd = snd * 10LL + x % 10;
				x /= 10LL;
			}
			ans.push_back(snd);
		}
	}
}

int main(){
	int test, id = 1;
	pot[0] = 1;
	repn(i,1,15) pot[i] = pot[i - 1]*10LL;
	repn(i,1,9) generate(i);
	cout << ans.back() << endl;
	rep (i, ans.size()) if( cumple(ans[i]*ans[i]) ) sqr.push_back(ans[i]* ans[i]);
	cout << sqr.size() << endl;
	cout << sqr.back() << endl;
	cin >> test;
	while (test--){
		int64 a , b;
		cin >> a >> b;
		cout << "Case #" << id++ << ": " << query(a, b) << "\n";
	}
	return 0;
}

