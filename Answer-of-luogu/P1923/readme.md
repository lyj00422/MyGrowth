# 这是洛谷P1923 【深基9.例4】求第 k 小的数
不会做的，求助的AI  
这道题是这样，在一个数组中选一个作为基准，分为lt，i，gt三路，lt~i是比pivot小的，i~gt是未排序的，gt~r是比pivot大的，while循环l < r,里面嵌套i < gt。k 如果小于lt，就令r = lt - 1，继续找，其他同理，直到k既不小于lt，也不大于gt  
这个算法在洛谷上超时，需要用到ios::sync_with_stdio(false),cin.tie(false),加快读入速度  
在设置pivot的时候，AI给出了有意思的随机数设置mt19937 rng(chrono::steady_clock::now().time_since_epoch().count)