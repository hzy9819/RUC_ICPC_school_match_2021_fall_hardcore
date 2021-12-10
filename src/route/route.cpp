#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int read() {
    int w = 0, f = 0; char c = getchar();
    while((c < '0' || c > '9') && c != '-') c = getchar();
    if(c == '-') f = 1, c = getchar();
    while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
    return f ? -w : w;
}

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

int main() {
    n = read();
    memset(lst, -1, sizeof lst);
    int x, y;
    for(int i = 1; i < n; ++i) {
        x = read(), y = read();
        add(x, y), add(y, x);
    }
    fa[0] = 0;
    Dfs(0);
    fa[0] = -1;
    k = read();
    for(int i = 1; i <= k; ++i) {
        int sz = read();
        for(int j = 1; j <= sz; ++j)
            temp[j] = read(), vis[temp[j]] = i;
        int flag = 0;
        for(int j = 1; j <= sz; ++j)
            if(fa[temp[j]] == -1 || vis[fa[temp[j]]] != i) {
                flag++;
                if(flag > 1)
                    break;
            }
        flag == 1 ? puts("YES") : puts("NO");
    }
    return 0;
}