#include <stdio.h>
__int64 a[101];
int A[101];
__int64 b[101];
int B[101];
int n,m;
__int64 ans;
void factory(int box, int rob, int max)
{
	int aa;
	if(ans<max)
	{
		ans=max;
	}
	if(box<=n && rob<=m)
	{
		if(A[box]==B[rob])
		{
			if(a[box]>b[rob])
			{
				aa=b[rob];
				max+=aa;	
				a[box]-=aa;
				factory(box,rob+1,max);
				a[box]+=aa;
				max-=aa;
			}
			else
			{
				aa=a[box];
				max+=aa;	
				b[rob]-=aa;
				factory(box+1,rob,max);
				b[rob]+=aa;
				max-=aa;
			}
		}
		else
		{
			factory(box+1,rob,max);
			factory(box,rob+1,max);
		}
	}
}
int main()
{
	freopen("C-small-attempt0.in","r",stdin);
	freopen("output.out","w",stdout);
	int i,j,z,t;
	scanf("%d",&t);
	for(z=1;z<=t;z++)
	{
		ans=0;
		printf("Case #%d: ",z);
		scanf("%d",&n);
		scanf("%d",&m);
		for(i=1;i<=n;i++)
		{
			scanf("%I64d",&a[i]);
			scanf("%d",&A[i]);
		}
		for(i=1;i<=m;i++)
		{
			scanf("%I64d",&b[i]);
			scanf("%d",&B[i]);
		}
		factory(1,1,0);
		printf("%I64d\n",ans);
	}

	return 0;
}