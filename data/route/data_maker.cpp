#include <bits/stdc++.h>

using namespace std;

const int TESTCASE = 3;
const int N = 1e6;
const int K = 1e7;

void random_tree(FILE * fout, int n, int k) {
    fprintf(fout, "%d\n", n);
    for(int i = 1; i < n; ++i)
        fprintf(fout, "%d %d\n", rand() % i, i);
}

void random_query(FILE * fout, int n, int k) {
    fprintf(fout, "%d\n", k);
    int sz = K / k;
    int vis[n];
    memset(vis, -1, sizeof(vis));
    for(int i = 0; i < k; ++i) {
        fprintf(fout, "%d ", sz);
        for(int j = 0; j < sz; ++j) {
            int tmp = rand() % n;
            if(vis[tmp] != i) {
                fprintf(fout, "%d ", tmp);
                vis[tmp] = i;
            }
        }
        fprintf(fout, "\n");
    }
}

void half_star_graph(FILE * fout, int n, int k) {
    fprintf(fout, "%d\n", n);
    int lim = n / 2;
    for(int i = 1; i < lim; ++i)
        fprintf(fout, "%d %d\n", 0, i);
    for(int i = lim; i < n; ++i)
        fprintf(fout, "%d %d\n", rand() % i, i);
}

void half_star_query(FILE * fout, int n, int k) {
    fprintf(fout, "%d\n", k);
    int lim = n / 2;
    int sz = K / k;
    int vis[n];
    memset(vis, -1, sizeof(vis));
    for(int i = 0; i < k; ++i) {
        fprintf(fout, "%d 0 ", sz);
        vis[0] = i;
        for(int j = 1; j < sz; ++j) {
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
    
    
    

int main() {
    srand(time(0));
    int num1 = TESTCASE / 3;
    int num2 = TESTCASE / 3 + num1;
    string name = "route", in_name, out_name, cmd_line;
    for(int i = 0; i < num1; ++i) {
        in_name = name + to_string(i) + ".in";
        out_name = name + to_string(i) + ".out";
        FILE * fin = fopen(in_name.c_str(), "w");
        random_tree(fin, 1e6, 2e6);
        random_query(fin, 1e6, 2e6);
        cmd_line = "./route " + in_name + " " + out_name;
        system(cmd_line.c_str());
    }
    for(int i = num1; i < num2; ++i) {
        in_name = name + to_string(i) + ".in";
        out_name = name + to_string(i) + ".out";
        FILE * fin = fopen(in_name.c_str(), "w");
        half_star_graph(fin, 1e6, 2e6);
        random_query(fin, 1e6, 2e6);
        cmd_line = "./route " + in_name + " " + out_name;
        system(cmd_line.c_str());
    }
    for(int i = num2; i < TESTCASE; ++i) {
        in_name = name + to_string(i) + ".in";
        out_name = name + to_string(i) + ".out";
        FILE * fin = fopen(in_name.c_str(), "w");
        half_star_graph(fin, 1e6, 2e6);
        half_star_query(fin, 1e6, 2e6);
        cmd_line = "./route " + in_name + " " + out_name;
        system(cmd_line.c_str());
    }

}