# 这是洛谷[NOIP 2016 提高组] 玩具谜题
我学到了什么：  
1.提高cin,cout速度的两句代码  
ios::sync_with_stdio(false)  
cin.tie(nullptr)  
在using namespace std的情况下  
这个原理是，接触cin,cout 和 scanf，printf的同步，写下这个就不可以混用了。解除cin传入的时候和cout.flush()的绑定，写下这个在必要的时候要自己写cout.flush()  
2.优化时间复杂度  
我在第一次写的时候，用的是循环链表，使得时间复杂度非常大，因为每一次移动都要移动指针，在问了chatgpt之后，知道可以用数组(vector<person> people(n),可以创建长度为n的数组),同时，可以用下标的移动，用取余保证其移动后在0~n-1之间(相当于循环了),这样时间复杂度大大缩短为O(1)