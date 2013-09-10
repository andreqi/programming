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

int a[1005], b[1005];
bool ok1[1005], ok2[1005];

int main()
{
	int nCasos;
	scanf("%d", &nCasos);
	
	for(int caso=1; caso<=nCasos; caso++)
	{
		int n;
		cin>>n;
		
		for(int i=0; i<n; i++)
			cin>>a[i]>>b[i];
		
		memset(ok1, 0, sizeof(ok1));
		memset(ok2, 0, sizeof(ok2));
		
		int score = 0, games = 0;
		while(score < 2*n)
		{
			bool sigue = 0;
			for(int i=0; i<n; i++)
			{
				if(!ok2[i] && score >= b[i])
				{
					sigue = 1;
					
					games++;
					if(ok1[i]) score++;
					else score += 2;
					
					ok1[i] = 1;
					ok2[i] = 1;
				}
			}
			
			if(!sigue && score < 2*n)
			{
				int maxB = -1, ind = -1;
				for(int i=0; i<n; i++)
				{
					if(!ok1[i] && score >= a[i])
					{
						if(b[i] > maxB)
						{
							maxB = b[i];
							ind = i;
						}
					}
				}
				if(ind != -1)
				{
					sigue = 1;
					
					ok1[ind] = 1;
					score++;
					games++;
				}
			}
			
			if(!sigue) break;
		}
		
		if(score < 2 * n) printf("Case #%d: Too Bad\n", caso);
		else printf("Case #%d: %d\n", caso, games);
	}	
	
	return 0;
}
