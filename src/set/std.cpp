#include <cstdio>
#include <cstring>
#include <algorithm>
#include <time.h>
#define nn 1000002
#define LL long long
using namespace std;

int n;
int vis[nn],s[nn];

void init()
{
	for(int j=2;j<nn;++j)
	{
		for(int k=2*j;k<nn;k+=j)
		{
			vis[k]=1;
		}
	}
	s[1]=0;
	for(int j=2;j<nn;++j) s[j]=(1-vis[j])+s[j-1];
}

int main()
{
	freopen("solve.in","r",stdin);
	freopen("solve.out","w",stdout);

	int T;
	init();
	scanf("%d\n",&T);
	for(int i=1;i<=T;++i)
	{
		scanf("%d\n",&n);
		printf("%d\n",s[n]);
	}
	
	return 0;
}
