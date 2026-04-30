#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n,m;
    cin >> n >> m;
    vector<vector<char>> map(n,vector<char>(m));

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m ; j++)
        {
            cin >> map[i][j];
        }
    }

    vector<int> dx = {-1,-1,-1,0,0,0,1,1,1};
    vector<int> dy = {-1,0,1,-1,0,1,-1,0,1};

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m ; j++)
        {
            if(map[i][j] == '*')
            {
                cout << map[i][j];
            }
            else
            {
                int count = 0;
                for(int r = 0; r < dx.size(); r++)
                {
                    int di = i + dx[r];
                    int dj = j + dy[r];
                    if(di >= 0 && di < n && dj >= 0 && dj < m)
                    {
                        if(map[di][dj] == '*')
                        {
                            count++;
                        }
                    }
                }
                cout << count;
            }
        }
        cout << endl;
    }
    return 0;
}