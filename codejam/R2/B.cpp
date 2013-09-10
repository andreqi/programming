#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <queue>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <ctime>

using namespace std;

int N, W, H;

struct rectangle
{
    int w, h, idx;
    int x1, y1, x2, y2, d;
    int mult_by, div_by;
};

bool operator <(const rectangle &a, const rectangle &b)
{
	long long A1 = a.w;
	A1 *= a.h;
	
	long long A2 = b.w;
	A2 *= b.h;
	
    return A1 > A2;
}

vector <rectangle> R;

int shared(int a, int b, int c, int d)
{
    int maxS = max(a, c), minE = min(b, d);
    if(maxS < minE) return minE - maxS;
    else return 0;
}

vector <rectangle> input;

int getScore(int x, int y, int ind, int dir)
{
    int xf = x + (dir == 0 ? R[ind].w : R[ind].h);
    int yf = y + (dir == 0 ? R[ind].h : R[ind].w);
    
    if(x < 0 || y < 0 || xf > W || yf > H) return 0;
    
    int c_score = 0;
    for(int i=0; i<N; i++)
    {
        if(R[i].x1 >= 0 && i != ind)
        {
            int maxX = max(R[i].x1, x), minX = min(R[i].x2, xf);
            int maxY = max(R[i].y1, y), minY = min(R[i].y2, yf);
            
            if(maxX < minX && maxY < minY)
            {
                c_score = -1;
                break;
            }
            else
            {
                int mult = (dir != R[i].d ? 1 : -1);
                
                c_score += mult * (R[i].x1 == x  ? shared(R[i].y1, R[i].y2, y, yf) : 0);
                c_score += mult * (R[i].x1 == xf ? shared(R[i].y1, R[i].y2, y, yf) : 0);
                c_score += mult * (R[i].x2 == x  ? shared(R[i].y1, R[i].y2, y, yf) : 0);
                c_score += mult * (R[i].x2 == xf ? shared(R[i].y1, R[i].y2, y, yf) : 0);
                
                c_score += mult * (R[i].y1 == y  ? shared(R[i].x1, R[i].x2, x, xf) : 0);
                c_score += mult * (R[i].y1 == yf ? shared(R[i].x1, R[i].x2, x, xf) : 0);
                c_score += mult * (R[i].y2 == y  ? shared(R[i].x1, R[i].x2, x, xf) : 0);
                c_score += mult * (R[i].y2 == yf ? shared(R[i].x1, R[i].x2, x, xf) : 0);
                
            }
        }
    }
    return c_score;
}

void check(int x, int y, int ind, int dir, int &bestDelta, int &xx, int &yy, int &dd)
{
	//cout<<x<<" "<<y<<" "<<ind<<endl;
	
    int xf = x + (dir == 0 ? R[ind].w : R[ind].h);
    int yf = y + (dir == 0 ? R[ind].h : R[ind].w);
    
    int xc = x + R[ind].w / 2, yc = y + R[ind].h / 2;
    if(xc < 0 || xc > W || yc < 0 || yc > H) return;
    
    int c_score = 0;
    for(int i=0; i<ind; i++)
    {
        if(R[i].x1 != -1<<30)
        {
            int maxX = max(R[i].x1, x), minX = min(R[i].x2, xf);
            int maxY = max(R[i].y1, y), minY = min(R[i].y2, yf);
            
            if(maxX < minX && maxY < minY)
            {
                c_score = -1;
                break;
            }
            else
            {
                int mult = 1;//(dir != R[i].d ? 1 : -1);
                
                c_score += mult * (R[i].x1 == x  ? shared(R[i].y1, R[i].y2, y, yf) : 0);
                c_score += mult * (R[i].x1 == xf ? shared(R[i].y1, R[i].y2, y, yf) : 0);
                c_score += mult * (R[i].x2 == x  ? shared(R[i].y1, R[i].y2, y, yf) : 0);
                c_score += mult * (R[i].x2 == xf ? shared(R[i].y1, R[i].y2, y, yf) : 0);
                
                c_score += mult * (R[i].y1 == y  ? shared(R[i].x1, R[i].x2, x, xf) : 0);
                c_score += mult * (R[i].y1 == yf ? shared(R[i].x1, R[i].x2, x, xf) : 0);
                c_score += mult * (R[i].y2 == y  ? shared(R[i].x1, R[i].x2, x, xf) : 0);
                c_score += mult * (R[i].y2 == yf ? shared(R[i].x1, R[i].x2, x, xf) : 0);
                
            }
        }
    }
    //cout<<score<<endl;
    if(c_score > bestDelta)
    {
        bestDelta = c_score;
        xx = x;
        yy = y;
        dd = dir;
    }
}


int main()
{
	int nCasos;
	scanf("%d", &nCasos);
	
	for(int caso=1; caso<=nCasos; caso++)
	{
		scanf("%d %d %d", &N, &W, &H);
		
		R.resize(N);
		
		for(int i=0; i<N; i++)
		{
			int r;
			scanf("%d", &r);
			
			R[i].w = R[i].h = 2*r;
		    R[i].mult_by = R[i].div_by = 1;
		    R[i].idx = i;
		}
		
		input = R;
		
		
		sort(R.begin(), R.end());
		
		R[0].x1 = -R[0].w / 2;
		R[0].y1 = -R[0].h / 2;
		R[0].x2 = R[0].w / 2;
		R[0].y2 = R[0].h / 2;
		R[0].d = 0;
		
		for(int i=1; i<N; i++)
		{
		    int bestDelta = -1, xx, yy, dd;
		    
		    for(int j=0; j<i; j++)
		    {
		        if(R[j].x1 != -1<<30)
		        {
		            check(R[j].x1, R[j].y2, i, 0, bestDelta, xx, yy, dd);
		            check(R[j].x2, R[j].y1, i, 0, bestDelta, xx, yy, dd);

		            check(R[j].x1, - R[i].h / 2, i, 0, bestDelta, xx, yy, dd);
		            check(R[j].x1, H - R[i].h / 2, i, 0, bestDelta, xx, yy, dd);

		            check(R[j].x2, - R[i].h / 2, i, 0, bestDelta, xx, yy, dd);
		            check(R[j].x2, H - R[i].h / 2, i, 0, bestDelta, xx, yy, dd);
		            		        
		            check( - R[i].w / 2, R[j].y2, i, 0, bestDelta, xx, yy, dd);
		            check(W - R[i].w / 2, R[j].y2, i, 0, bestDelta, xx, yy, dd);		            
		        }
		    }
		            
		    if(bestDelta >= 0)
		    {
		        R[i].x1 = xx;
		        R[i].y1 = yy;
		        R[i].x2 = R[i].x1 + (dd == 0 ? R[i].w : R[i].h);
		        R[i].y2 = R[i].y1 + (dd == 0 ? R[i].h : R[i].w);
		        R[i].d = dd;
		    }
		    else R[i].x1 = R[i].y1 = R[i].x2 = R[i].y2 = -1<<30;
		}
		
		double xx1[1005], yy1[1005], xx2[1005], yy2[1005];
		for(int i=0; i<N; i++)
		{
		    xx1[R[i].idx] = (R[i].x1 + R[i].x2)/2.0;
		    yy1[R[i].idx] = (R[i].y1 + R[i].y2)/2.0;
		    //xx2[R[i].idx] = R[i].x2;
		    //yy2[R[i].idx] = R[i].y2;
		}
		   
		cout<<"Case #"<<caso<<":";
		
		for(int i=0; i<N; i++)
		    printf(" %.2lf %.2lf", xx1[i], yy1[i]);
		cout<<endl;
    }
    return 0;
}
