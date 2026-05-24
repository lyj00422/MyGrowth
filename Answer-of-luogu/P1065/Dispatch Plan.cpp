#include <bits/stdc++.h>
using namespace std;

int main()
{
    int m, n;
    int order[405];
    int machineNeed[25][25];
    int costTime[25][25];
    int cnt[25] = { 0 };
    int finishTime[25] = { 0 };
    bool used[25][100005] = { false }; 
    int ans = 0;

    cin >> m >> n;

    int total = m * n; 
    for(int i = 1; i <= total; i++)
    {
        cin >> order[i];
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            cin >> machineNeed[i][j];
        }
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            cin >> costTime[i][j];
        }
    }

    for(int i = 1; i <= total; i++)
    {
        int job = order[i];

        cnt[job]++;
        int step = cnt[job];

        int mac = machineNeed[job][step];
        int len = costTime[job][step];

        int start = finishTime[job];

        while(true)
        {
            bool ok = true;

            for(int t = start; t < start + len; t++)
            {
                if(used[mac][t])
                {
                    ok = false;
                    break;
                }
            }

            if(ok)
            {
                break;
            }

            start++;
        }

        for(int t = start; t < start + len; t++)
        {
            used[mac][t] = true;
        }

        finishTime[job] = start + len;
        ans = max(ans, finishTime[job]);
    }

    cout << ans << endl;

    return 0;
}