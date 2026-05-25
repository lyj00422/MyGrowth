#include <bits/stdc++.h>
using namespace std;

class Person
{
    public:
    string name;
    string job;
    int gong;
    int level;
    int id;
};

int JobRank(string job)
{
    if(job == "BangZhu") return 1;
    if(job == "FuBangZhu") return 2;
    if(job == "HuFa") return 3;
    if(job == "ZhangLao") return 4;
    if(job == "TangZhu") return 5;
    if(job == "JingYing") return 6;
    return 7;
}

bool CmpGong(Person a,Person b)
{
    if(a.gong != b.gong) return a.gong > b.gong;
    return a.id < b.id;
}

bool CmpFinal(Person a,Person b)
{
    if(JobRank(a.job) != JobRank(b.job)) return JobRank(a.job) < JobRank(b.job);
    if(a.level != b.level) return a.level > b.level;
    return a.id < b.id;
}

int main()
{
    int n;
    cin >> n;

    vector<Person> fix_people;
    vector<Person> normal_people;

    for(int i = 0 ; i < n; i++)
    {
        Person p;
        cin >> p.name >> p.job >> p.gong >> p.level;
        p.id = i;

        if(p.job != "BangZhu" && p.job != "FuBangZhu")
        {
            normal_people.push_back(p);
        }
        else
        {
            fix_people.push_back(p);
        }
    }

    sort(normal_people.begin(), normal_people.end(), CmpGong);

    for (int i = 0; i < normal_people.size(); i++) {
        if (i < 2) {
            normal_people[i].job = "HuFa";
        } else if (i < 2 + 4) {
            normal_people[i].job = "ZhangLao";
        } else if (i < 2 + 4 + 7) {
            normal_people[i].job = "TangZhu";
        } else if (i < 2 + 4 + 7 + 25) {
            normal_people[i].job = "JingYing";
        } else {
            normal_people[i].job = "BangZhong";
        }
    }

    // 合并所有人
    vector<Person> all;
    for (auto p : fix_people) all.push_back(p);
    for (auto p : normal_people) all.push_back(p);

    // 第二次排序：按职位、等级、输入顺序输出
    sort(all.begin(), all.end(), CmpFinal);

    for (auto p : all) {
        cout << p.name << " " << p.job << " " << p.level << '\n';
    }

    return 0;
}