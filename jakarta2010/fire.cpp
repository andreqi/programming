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
#define clr(x, y) memset(x, (y), sizeof x)
#define two(x) (1<<(x))
#define twol(x) (1LL<<(x))
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
typedef pair<int, pii> node;

int L, H, W;
int dis[101][101][101];
char grid[110][110][110];
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
int dp[10010];
int main(){
    int test;
    scanf("%d", &test);
    while (test--) {
        int N, S;
        scanf("%d%d%d%d%d", &L, &H, &W, &N, &S);
        rep (i, L) rep (j, H) scanf("%s", grid[i][j]);
        int x, y, z;
        rep (i, L) rep (j, H) rep (k, W) {
            if (grid[i][j][k] == 'S') {
                x = i , y = j, z = k;
                goto hell;
            }
        }
        hell:;

        queue<node> q;
        q.push(mp(x,mp(y,z)));
        memset(dis, -1 , sizeof dis);
        dis[x][y][z] = 0;
        while (not q.empty()) {
            node cur = q.front(); q.pop();
            x = cur.fst, y = cur.snd.fst, z = cur.snd.snd;
            rep (i, 4) {
                int ny = y + dx[i];
                int nz = z + dy[i];
                if (ny < 0 or nz < 0 or ny >= H or nz >=W ) continue; 
                if (dis[x][ny][nz] != -1 or 
                    grid[x][ny][nz] == 'X') continue; 
                dis[x][ny][nz] = dis[x][y][z] + 1;
                q.push(mp(x,mp(ny,nz)));
            }
            char c = grid[x][y][z];
            int mx = c == 'U' ? 1:( c == 'D' ? -1: 0 );
            if (mx == 0 ) continue;
            int nx = x + mx;
            if (nx < 0 or nx >= L) continue;
            if (dis[nx][y][z] != -1) continue;
            dis[nx][y][z] = dis[x][y][z] + 1;
            q.push(mp(nx,mp(y,z)));
        }
        int f, r, c, p;
        clr(dp, -1);
        int ans = 0;
        dp[0] = 0;
        rep (i, N) {
            scanf("%d%d%d%d", &f, &r, &c, &p);
            int cost = dis[f-1][r-1][c-1];
            if (cost < 0) continue;
            cost *= 3;
            for (int j = S; j >= cost; j--) {
                if (dp[j-cost] != -1) {
                    dp[j] = max(dp[j], dp[j- cost] + p);
                }
                ans = max(ans, dp[j]);
            }
        }
        printf("%d\n", ans);
    }
	return 0;
}
