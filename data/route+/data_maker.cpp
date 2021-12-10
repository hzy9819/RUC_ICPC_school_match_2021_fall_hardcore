#include <bits/stdc++.h>

using namespace std;

const int TESTCASE = 3;
const int N = 1e5;
const int K = 1e7;
    
void random_hypergraph(FILE * fout, int n, int k) {
    fprintf(fout, "%d %d\n", n, k);
    int sz = K / k, vis[n];
    for(int i = 0; i < n; ++i)
        vis[i] = -1;    
    for(int i = 0; i < k; ++i) {
        fprintf(fout, "%d ", sz);
        for(int j = 0; j < sz; ++j) {
            int tmp = rand() % n;
            if(vis[tmp] != i) {
                fprintf(fout, "%d ", tmp);
                vis[tmp] = i;
            }
            else
                j--;
        }
        fprintf(fout, "\n");
    }
}

void acyclic_hypergraph(FILE * fout, int n, int k) {
    fprintf(fout, "%d %d\n", n, k);
    int sz = K / n, p[sz], delt = k / n;
    for(int i = 0; i < sz; ++i)
        p[i] = i;
    vector< vector <int> > V, res(k);
    for(int i = 0; i < n; ++i)
        res[i].clear();
    V.clear();
    vector <int> tp(0);
    V.push_back(tp);
    for(int i = 0; i < sz; ++i)
        V[0].push_back(i);
    for(int i = 1; i < n; ++i) {
        vector <int> tmp(0);
        int l = delt * (i + 1), r = l + delt, pre = rand() % i;
        l = min(l, k), r = min(r, k);
        random_shuffle(p, p + sz);
        for(int j = 0; j < sz - (r - l); ++j)
            tmp.push_back(V[pre][p[j]]);
        for(int j = l; j < r; ++j)
            tmp.push_back(j);
        V.push_back(tmp);
    }
    for(int i = 0; i < n; ++i)
        for(auto it = V[i].begin(); it != V[i].end(); ++it)
            res[*it].push_back(i);
    for(int i = 0; i < k; ++i) {
        fprintf(fout, "%d ", res[i].size());
        for(auto it = res[i].begin(); it != res[i].end(); ++it)
            fprintf(fout, "%d ", *it);
        fprintf(fout, "\n");
    }
}
    

int main() {
    srand(time(0));
    int num1 = TESTCASE / 2;
    string name = "route+", in_name, out_name, cmd_line;
    for(int i = 0; i < num1; ++i) {
        in_name = name + to_string(i) + ".in";
        out_name = name + to_string(i) + ".out";
        FILE * fin = fopen(in_name.c_str(), "w");
        random_hypergraph(fin, 1e5, 2e5);
    }
    for(int i = num1; i < TESTCASE; ++i) {
        in_name = name + to_string(i) + ".in";
        out_name = name + to_string(i) + ".out";
        FILE * fin = fopen(in_name.c_str(), "w");
        acyclic_hypergraph(fin, 1e5, 2e5);
    }
    return 0; 

}