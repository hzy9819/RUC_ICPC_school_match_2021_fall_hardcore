#include "Hypergraph.h"
#include <cstdio>
#include <stdlib.h>

void DataLoader(const char * file_name, Hypergraph & G) {
    FILE * fin = fopen(file_name, "r");
    size_t n, m, sz, tmp;
    fscanf(fin, "%lu %lu", &n, &m);
    G.set(m, n);

    std::vector< std::vector<size_t> > V(n);

    for(size_t i = 0; i < m; ++i) {
        fscanf(fin, "%lu", &sz);
        for(size_t j = 0; j < sz; ++j) {
            fscanf(fin, "%lu", &tmp);
            V[tmp].push_back(i);
        }
    }
    for(size_t i = 0; i < n; ++i)
        G.add(V[i]);
}

int main(int argc, char * argv[]) {
    Hypergraph H;
    Graph G;
    DataLoader(argv[1], H);

    FILE * fout = fopen(argv[2], "w");

    if(H.build_join_forest(G)) {
        fprintf(fout, "YES\n");
        for(size_t i = 0; i < G.m; ++i)
            for(size_t j = G.lst[i]; j != -1; j = G.e[j].nxt)
                if(i < G.e[j].to)
                    fprintf(fout, "%lu %lu\n", i, G.e[j].to);
    }
    else 
        fprintf(fout, "NO\n");
    return 0;
}