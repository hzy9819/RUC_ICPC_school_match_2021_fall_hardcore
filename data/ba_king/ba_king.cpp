#include <bits/stdc++.h>
#define db double

using namespace std;

const db eps = 1e-4;

bool cmp(db x, db y) {
    return fabs(x - y) < eps;
}

int main(int argc, char * argv[]) {
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    db lambda[n + 5][m + 5], sum[m + 5], num[n + 5], Max = 0.;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            scanf("%lf", &lambda[i][j]);
    for(int j = 1; j <= m; ++j) {
        sum[j] = 0;
        for(int i = 1; i <= n; ++i)
            sum[j] += lambda[i][j];
    }
    for(int i = 1; i <= n; ++i) {
        num[i] = 0.;
        for(int j = 1; j <= m; ++j)
        num[i] += lambda[i][j] / sum[j];
        Max = max(Max, num[i]);
    }
    printf("%s\n", cmp(Max, num[1]) ? "Ogi is BABA AND WIN!" : "NOT Ogi is BABA AND WIN!");
    for(int i = 1; i <= n; ++i)
        printf("%.3lf\n", num[i]);
    return 0;
    
}