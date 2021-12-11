#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

int a[12], b[12];

int main() {
    int temp;
    bool anc = 0;
    for (int T = 1; T <= 1000; ++T) {
        anc = 0;
        for (int t = 1; t <= 10; ++t) {
            cout << "?" << endl;
            fflush(stdout);
            cin >> temp;
            a[t] = temp;
            b[t] = (a[t] - a[t - 1] + 3) % 3;
            if (t >= 3 && b[t] != b[t - 1]) {
                int x = (a[t] + b[t - 1]) % 3;
                cout << "! " << (x + 1) % 3 << endl;
                fflush(stdout);
                anc = 1;
                break;
            }
        }
        if (!anc) {
            cout << "! " << (a[10] + b[10] + 1) % 3 << endl;
            fflush(stdout);
        }
    }

    return 0;
}
