#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> num(m);
    unordered_multimap<int, int> umm;

    for (int i = 0; i < m; i++) {
        cin >> num[i];
        umm.insert({num[i], i});
    }

    for (int i = 1; i <= n; i++) {
        auto range = umm.equal_range(i);
        for (auto it = range.first; it != range.second; ++it) {
            cout << i << " ";
        }
    }

    return 0;
}