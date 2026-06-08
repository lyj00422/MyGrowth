#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> cnt(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < cnt[i]; j++) {
            cout << i << " ";
        }
    }

    return 0;
}