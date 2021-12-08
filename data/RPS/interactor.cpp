#include <bits/stdc++.h>
using namespace std;

int i, seed, n;
int wins;

int judge()
{
	(i += seed) %= n;
	return i % 3;
}

void init_rps()
{
	seed = rand() % n;
	i = 0;
}

int main() {
	srand((int)time(0));
	FILE * f = fopen("input", "r");
	FILE * fo = fopen("score.txt", "w");
	char tp[10];
	fscanf(f, "%d", &n);
	fclose(f);
	for(int T = 1; T <= 1000; ++T) {
		bool anc = 0;
		init_rps();
		for(int i = 1; i <= 11; ++i) {
			scanf("%s", tp);
			if(tp[0] == '?') {
				if(i == 11) break;
				int x = judge();
				puts(x==0?"0":(x==1?"1":"2"));
				fflush(stdout);
			}
			else {
				int y;
				scanf("%d", &y);
				int x = judge();
				if(x==0&&y==1 || x==1&&y==2 || x==2&&y==0)
				{
					wins++;
				}
				anc=1;
				break;
			}
		}
		
		if(!anc)
		{
			fprintf(fo, "0");
			cerr << "Number of queries exceeded!" << endl;
			fclose(fo);
			return 0;
		}
	}
	
	if(wins >= 950) {
		fprintf(fo, "100");
		cerr << "Accepted: your winning rate: " << wins * 1.0 / 1000 << endl;
		fclose(fo);
		return 0;		
	}
	else {
		fprintf(fo, "0");
		cerr << "Wrong Answer: your winning rate: " << wins * 1.0 / 1000 << endl;
		fclose(fo);
		return 0;
	}
	return 0;
}
				
			
	
	
