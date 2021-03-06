#include <bits/stdc++.h>
#include "Hypergraph.h"
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)



void DataLoader(const char * file_name, Graph & G, std::vector< std::vector<size_t> > &V) {
    FILE * fin = fopen(file_name, "r");
    size_t n, k, x, y;
    fscanf(fin, "%lu", &n);
    G.Init(n, (n - 1) * 2);
    for(size_t i = 0; i < n - 1; ++i) {
        fscanf(fin, "%lu %lu", &x, &y);
        G.add(x, y), G.add(y, x);
    }

    G.build_fa();

    fscanf(fin, "%lu", &k);

    for(size_t i = 0; i < k; ++i) {
        std::vector<size_t> tmp;
        tmp.clear();
        size_t sz, temp;
        fscanf(fin, "%lu", &sz);
        while(sz--) {
            fscanf(fin, "%lu", &temp);
            tmp.push_back(temp);
        }
        // if(i % 10000 == 0)
        //     printf("%lu\n", i);
        V.push_back(tmp);        
    }
}

int main(int argc, char * argv[]) {    
    Graph G;
    std::vector< std::vector<size_t> > V;
    V.clear();
    printf("%d\n", argc);
    printf("%s\n", argv[1]);
    DataLoader(argv[1], G, V);
    std::vector< bool > res;
    G.check_connectivity_T(V, res);
    printf("%s\n", argv[2]);
    FILE * fout = fopen(argv[2], "w");
    for(auto it = res.begin(); it != res.end(); ++it)
        // *it ? puts("YES") : puts("NO");
        fprintf(fout, "%s\n", *it ? "YES" : "NO");
    return 0;
}
