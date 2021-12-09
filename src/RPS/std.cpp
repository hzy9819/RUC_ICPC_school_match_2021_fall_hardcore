#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <time.h>
using namespace std;

int a[22],b[22],real[22];

int i, seed, n;
int top = 0;

int judge()
{
	(i += seed) %= n;
	real[++top] = i;
	return i % 3;
}

void init_rps()
{
	seed = rand() % n;
	i = 0;
}

int main()
{
	srand((int)time(0));
	int temp;
	bool anc = 0;
	n = 1000;
	for(int T = 1; T <= 1; ++T)
	{
		anc = 0;
		init_rps();
		for(int t = 1; t <= 20; ++t)
		{
			/*
			cout << "?" << endl;
			fflush(stdout);
			cin >> temp;
			*/
			temp = judge();
			a[t] = temp;
			b[t] = (a[t] - a[t-1] + 3) % 3;
		    if(t >= 3 && b[t] != b[t-1])
			{
				int x = (a[t] + b[t-1]) % 3;
				cout << "! " << (x + 1) % 3 << endl;
				fflush(stdout);
				anc = 1;
				break;
			}
		}
		if(!anc)
		{
			cout << "! " << (a[20] + b[20]) % 3 << endl;
			fflush(stdout);
		}
	}
	
	cout << judge() << endl;
	for(int t = 1; t <= 20; ++t) cout << real[t] << " ";
	cout << endl;
	for(int t = 1; t <= 20; ++t) cout << a[t] << " ";
	cout << endl;
	for(int t = 1; t <= 20; ++t) cout << b[t] << " ";
	system("pause");
	
	return 0;
}
