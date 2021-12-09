#include <bits/stdc++.h>
#define db double
using namespace std;

const int TESTCASE = 5;
const int _eps = 1e4; // 1 / eps

db frand(int l, int r) {
    int delt = (r - l) * _eps;
    return l + (db) (rand() % delt) / _eps;
}

int main() {
    srand(time(0));

    string name = "ba_king", in_name, out_name, cmd_line;
    int n = 1000, m = 1000;
    for(int i = 0; i < TESTCASE; ++i) {
        in_name = name + to_string(i) + ".in";
        out_name = name + to_string(i) + ".out";
        FILE * fin = fopen(in_name.c_str(), "w");
        fprintf(fin, "%d %d\n", n, m);
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j)
                fprintf(fin, "%.4lf ", frand(1, 20));
            fprintf(fin, "\n");
        }
    }
    return 0;
}