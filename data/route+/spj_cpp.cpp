#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int n, k, vis[N], temp[N];

struct Edge {
    int to, nxt;
}e[N * 2];
int lst[N], d = 0;

void add(int x, int y) {
    e[d].to = y, e[d].nxt = lst[x], lst[x] = d++;
}

int fa[N];

void Dfs(int t) {
    for(int i = lst[t]; i >= 0; i = e[i].nxt)
        if(fa[e[i].to] == -1) {
            fa[e[i].to] = t;
            Dfs(e[i].to);
        }
}

int work(FILE* f, int i) //1: YES, 0: NO
{
    int sz;
	fscanf(f, "%d", &sz);
    for(int j = 1; j <= sz; ++j)
	{
		fscanf(f, "%d", &temp[j]);
		vis[temp[j]] = i;
	}
    int flag = 0;
    for(int j = 1; j <= sz; ++j)
        if(fa[temp[j]] == -1 || vis[fa[temp[j]]] != i) {
            flag++;
            if(flag > 1)
                break;
        }
	
	return flag <= 1;
}

int main() {
	FILE* f1 = fopen("input", "r");
	FILE* f2 = fopen("user_out", "r");
	FILE* f3 = fopen("answer", "r");

	char ans[6], stdans[6];
	fscanf(f1, "%d%d\n", &n, &k);
	fscanf(f2, "%s\n", ans);
	fscanf(f3, "%s", stdans);
	if(ans[0] == 'Y')
	{
		if(stdans[0] != 'Y')
		{
			printf("0");
			fclose(f1); fclose(f2); fclose(f3);
			return 0;
		}
		else
		{
			int x, y;
			memset(lst, -1, sizeof lst);
			for(int i = 1; i < n; ++i)
			{
				fscanf(f2, "%d %d\n", &x, &y);
				add(x, y), add(y, x);
				fa[i] = -1;
			}
			fa[0] = 0;
			Dfs(0);
			fa[0] = -1;
			for(int i = 1; i <= k; ++i)
			{
				int res = work(f1, i);
				if(!res)
				{
					printf("0");
					fclose(f1); fclose(f2); fclose(f3);
					return 0;
				}
			}
			printf("100");
			fclose(f1); fclose(f2); fclose(f3);
			return 0;
		}
	}
	else
	{
		if(stdans[0] != 'N')
		{
			printf("0");
			fclose(f1); fclose(f2); fclose(f3);
			return 0;
		}
		else
		{
			printf("100");
			fclose(f1); fclose(f2); fclose(f3);
			return 0;
		}
	}	

	fclose(f1); fclose(f2); fclose(f3);
    return 0;
}
