#include <cstdio>
#include <cstring>
#include <algorithm>
#include <time.h>
using namespace std;

int Rand()
{
	return rand()<<15|rand();
}

int main()
{
	srand((int)time(0));
	freopen("solve.in","w",stdout);

	int T=100;
	printf("%d\n",T);
	for(int i=1;i<=T;++i)
	{
		printf("%d\n", Rand()%(int)((1e6)-1)+2);
	}
	
	return 0;
}
