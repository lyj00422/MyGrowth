#include <bits/stdc++.h>
using namespace std;

int main() {
    int p1, p2, p3;
    cin >> p1 >> p2 >> p3;

    string s;
    cin >> s;

    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] != '-') {
            cout << s[i];
            continue;
        }

        // '-' 在开头或结尾，不能展开
        if (i == 0 || i == (int)s.size() - 1) {
            cout << s[i];
            continue;
        }

        char l = s[i - 1];
        char r = s[i + 1];

        // 判断左右两边是否同为小写字母，或者同为数字
        bool sameLower = islower(l) && islower(r);
        bool sameDigit = isdigit(l) && isdigit(r);

        // 不合法就原样输出 '-'
        if ((!sameLower && !sameDigit) || l >= r) {
            cout << s[i];
            continue;
        }

        // 决定展开方向
        int start, end, step;

        if (p3 == 1) {
            start = l + 1;
            end = r - 1;
            step = 1;
        } else {
            start = r - 1;
            end = l + 1;
            step = -1;
        }

        for (int c = start; ; c += step) {
            if (step == 1 && c > end) break;
            if (step == -1 && c < end) break;

            char out = (char)c;

            if (p1 == 3) {
                out = '*';
            } else if (p1 == 2 && islower(out)) {
                out = toupper(out);
            }

            for (int k = 0; k < p2; k++) {
                cout << out;
            }
        }
    }

    return 0;
}