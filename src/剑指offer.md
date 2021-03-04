[TOC]

# 剑指offer

## 剑指 Offer 03. 数组中重复的数字（简单）

找出数组中重复的数字。


在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

示例 1：

输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2 或 3 


限制：

2 <= n <= 100000

```cpp
class Solution {
public:
    int a[100005];
    int findRepeatNumber(vector<int>& nums) {
        int n=nums.size();
        for(int i=0;i<=n;++i)a[i]=0;
        for(int i=0;i<nums.size();++i){
            if(a[nums[i]]){
                return nums[i];
            }
            a[nums[i]]=1;
        }
        return -1;
    }
};
```

## 剑指 Offer 04. 二维数组中的查找（中等）

在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

 

示例:

现有矩阵 matrix 如下：

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
给定 target = 5，返回 true。

给定 target = 20，返回 false。

 

限制：

0 <= n <= 1000

0 <= m <= 1000

### 二分解法

先二分出最大行，再对可能的行二分

```c++
class Solution {
public:
    bool ju(vector<vector<int>>& matrix,int target){
        if(matrix.size()==0||matrix[0].size()==0)return false;
        int h=matrix.size()-1,w=matrix[0].size()-1;
        int l=0,r=h,mid;
        while(l<=r){
            mid=(l+r)>>1;
            if(matrix[mid][0]==target)return true;
            if(matrix[mid][0]<target)l=mid+1;
            else r=mid-1;
        }
        int p=r;
        for(int i=0;i<=p;++i){
            l=0,r=w;
            while(l<=r){
                mid=(l+r)>>1;
                if(matrix[i][mid]==target)return true;
                if(matrix[i][mid]<target)l=mid+1;
                else r=mid-1;
            }   
        }
        return false;
    }
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        return ju(matrix,target);
    }
};
```

### 考虑性质

二叉搜索

```c++
class Solution {
public:
    bool ju(vector<vector<int>>& matrix,int target){
        if(matrix.size()==0||matrix[0].size()==0)return false;
        int h=matrix.size()-1,w=matrix[0].size()-1;
        int x=0,y=w;
        while(true){
            if(target==matrix[x][y])return true;
            if(target<matrix[x][y]){
                if(y>0)--y;
                else return false;
            }else{
                if(x<h)++x;
                else return false;
            }
        }
        return false;
    }
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        return ju(matrix,target);
    }
};
```

## 剑指 Offer 05. 替换空格（简单）

请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

 

示例 1：

输入：s = "We are happy."
输出："We%20are%20happy."


限制：

0 <= s 的长度 <= 10000

```c++
class Solution {
public:
    string replaceSpace(string s) {
        int ls=s.length();
        string ans="";
        for(int i=0;i<ls;++i){
            if(s[i]==' ')ans+="%20";
            else ans+=s[i];
        }
        return ans;
    }
};
```

## 剑指 Offer 06. 从尾到头打印链表（简单）

输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。

 

示例 1：

输入：head = [1,3,2]
输出：[2,3,1]


限制：

0 <= 链表长度 <= 10000

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void solve(vector<int> &ans,ListNode* head){
        if(head==NULL)return;
        solve(ans,head->next);
        ans.push_back(head->val);
    }
    vector<int> reversePrint(ListNode* head) {
        vector<int> ans;
        solve(ans,head);
        return ans;
    }
};
```

## 剑指 Offer 07. 重建二叉树（中等）

输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

 

例如，给出

前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
返回如下的二叉树：

    3

   / \
  9  20
    /  \
   15   7


限制：

0 <= 节点个数 <= 5000

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* build(vector<int>& preorder,int pl,int pr,vector<int>& inorder,int il,int ir){
        TreeNode* now=new TreeNode(preorder[pl]);
        for(int i=il;i<=ir;++i){
            if(inorder[i]==preorder[pl]){
                int a=i-il,b=ir-i;
                if(a)now->left=build(preorder,pl+1,pl+a,inorder,il,il+a-1);
                if(b)now->right=build(preorder,pl+a+1,pr,inorder,il+a+1,ir);
                return now;
            }
        }
        return now;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size()==0)return NULL;
        return build(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1);
    }
};
```

## 剑指 Offer 09. 用两个栈实现队列

用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )

 

示例 1：

输入：
["CQueue","appendTail","deleteHead","deleteHead"]
[[],[3],[],[]]
输出：[null,null,3,-1]
示例 2：

输入：
["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]
[[],[],[5],[2],[],[]]
输出：[null,-1,null,null,5,2]
提示：

1 <= values <= 10000
最多会对 appendTail、deleteHead 进行 10000 次调用

```cpp
class CQueue {
public:
    stack<int> st1,st2;
    CQueue() {
        
    }
    
    void appendTail(int value) {
        st2.push(value);
    }
    
    int deleteHead() {
        if(st1.empty()){
            if(st2.empty()){
                return -1;
            }
            while(!st2.empty()){
                st1.push(st2.top());
                st2.pop();
            }
        }
        int x=st1.top();
        st1.pop();
        return x;
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */
```

## 剑指 Offer 10- I. 斐波那契数列（简单）

写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项（即 F(N)）。斐波那契数列的定义如下：

F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

 

示例 1：

输入：n = 2
输出：1
示例 2：

输入：n = 5
输出：5


提示：

0 <= n <= 100

```cpp
class Solution {
public:
    int fib(int n) {
        int f[n+5];
        f[0]=0,f[1]=1;
        for(int i=2;i<=n;++i){
            f[i]=f[i-1]+f[i-2];
            f[i]%=1000000007;
        }
        return f[n];
    }
};
```

## 剑指 Offer 10- II. 青蛙跳台阶问题（简单）

一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

示例 1：

输入：n = 2
输出：2
示例 2：

输入：n = 7
输出：21
示例 3：

输入：n = 0
输出：1
提示：

0 <= n <= 100

```cpp
class Solution {
public:
    int numWays(int n) {
        int f[n+5];
        f[0]=1;
        f[1]=1;
        for(int i=2;i<=n;++i){
            f[i]=f[i-1]+f[i-2];
            f[i]%=1000000007;
        }
        return f[n];
    }
};
```

## 剑指 Offer 11. 旋转数组的最小数字（简单）

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。  

示例 1：

输入：[3,4,5,1,2]
输出：1
示例 2：

输入：[2,2,2,0,1]
输出：0

```cpp
class Solution {
public:
    int minArray(vector<int>& numbers) {
        int len=numbers.size();
        if(numbers[len-1]>numbers[0]||len==1)return numbers[0];
        for(int i=1;i<len;++i){
            if(numbers[i]<numbers[i-1])return numbers[i];
        }
        return numbers[0];
    }
};
```

## 剑指 Offer 12. 矩阵中的路径（中等）

请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一格开始，每一步可以在矩阵中向左、右、上、下移动一格。如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该格子。例如，在下面的3×4的矩阵中包含一条字符串“bfce”的路径（路径中的字母用加粗标出）。

[["a","b","c","e"],
["s","f","c","s"],
["a","d","e","e"]]

但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入这个格子。

 

示例 1：

输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true
示例 2：

输入：board = [["a","b"],["c","d"]], word = "abcd"
输出：false


提示：

1 <= board.length <= 200
1 <= board[i].length <= 200

```cpp
class Solution {
public:
    int vis[205][205];
    int dir[4][2]={1,0,-1,0,0,1,0,-1};
    int ju(int x,int y,int h,int w){
        if(x<0||y<0||x>=h||y>=w||vis[x][y]==1)return false;
        return true;
    }
    int dfs(int x,int y,int now,int h,int w,vector<vector<char>>& board,string &word){
        if(now==word.size()-1)return true;
        for(int i=0;i<4;++i){
            int xx=x+dir[i][0];
            int yy=y+dir[i][1];
            if(ju(xx,yy,h,w)&&board[xx][yy]==word[now+1]){
                vis[xx][yy]=1;
                if(dfs(xx,yy,now+1,h,w,board,word)){
                    return true;
                }
                vis[xx][yy]=0;
            }
        }
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int h=board.size(),w=board[0].size();
        for(int i=0;i<h;++i){
            for(int j=0;j<w;++j){
                if(board[i][j]==word[0]){
                    memset(vis,0,sizeof(vis));
                    vis[i][j]=1;
                    if(dfs(i,j,0,h,w,board,word)){
                        return true;
                    }
                }
            }
        }
        return false;
    }
};
```

## 剑指 Offer 13. 机器人的运动范围（中等）

地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？

 

示例 1：

输入：m = 2, n = 3, k = 1
输出：3
示例 2：

输入：m = 3, n = 1, k = 0
输出：1
提示：

1 <= n,m <= 100
0 <= k <= 20

```cpp
class Solution {
public:
    int dir[4][2]={1,0,-1,0,0,1,0,-1};
    int get(int x){
        int ans=0;
        while(x){
            ans+=x%10;
            x/=10;
        }
        return ans;
    }
    int movingCount(int m, int n, int k) {
        int vis[105][105];
        for(int i=0;i<=n;++i){
            for(int j=0;j<=m;++j){
                vis[i][j]=-1;
            }
        }
        memset(vis,-1,sizeof(vis));
        queue<pair<int,int>>pq;
        pq.push(make_pair(0,0));
        vis[0][0]=0;
        int ans=1;
        while(!pq.empty()){
            pair<int,int> now=pq.front();
            pq.pop();
            for(int i=0;i<4;++i){
                int xx=now.first+dir[i][0];
                int yy=now.second+dir[i][1];
                if(xx>=0&&xx<n&&yy>=0&&yy<m&&vis[xx][yy]==-1&&get(xx)+get(yy)<=k){

                    vis[xx][yy]=vis[now.first][now.second]+1;
                    pq.push(make_pair(xx,yy));
                    ++ans;
                }
            }
        }
        return ans;
    }
};
```

## 剑指 Offer 14- I. 剪绳子（中等）

给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m-1] 。请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

示例 1：

输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1
示例 2:

输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36
提示：

2 <= n <= 58

```cpp
class Solution {
public:
    int cuttingRope(int n) {
        if(n==2)return 1;
        if(n==3)return 2;
        int a=n/3,b=n-a*3;
        int ans=1;
        while(a--){
            ans*=3;
        }
        if(b==1){
            ans/=3;
            ans*=4;
        }else(b==2){
            ans*=2;
        }
        return ans;
    }
};
```

## 剑指 Offer 14- II. 剪绳子 II（中等）

给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m - 1] 。请问 k[0]*k[1]*...*k[m - 1] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

 

示例 1：

输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1
示例 2:

输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36


提示：

2 <= n <= 1000

```cpp
class Solution {
public:
    long long pow_(long long a,long long b){
        long long ans=1;
        while(b){
            if(b&1)ans=(ans*a)%1000000007;
            b>>=1;
            a=(a*a)%1000000007;
        }
        return ans;
    }
    int cuttingRope(int n) {
        if(n==2)return 1;
        if(n==3)return 2;
        int a=n/3,b=n-a*3;
        long long ans;
        if(b==1){
            ans=pow_(3,a-1);
            ans*=4;
        }else if(b==2){
            ans=pow_(3,a);
            ans*=2;
        }else{
            ans=pow_(3,a);
        }
        return (int)(ans%1000000007);
    }
};
```

## 剑指 Offer 15. 二进制中1的个数（简单）

请实现一个函数，输入一个整数（以二进制串形式），输出该数二进制表示中 1 的个数。例如，把 9 表示成二进制是 1001，有 2 位是 1。因此，如果输入 9，则该函数输出 2。

 

示例 1：

输入：00000000000000000000000000001011
输出：3
解释：输入的二进制串 00000000000000000000000000001011 中，共有三位为 '1'。
示例 2：

输入：00000000000000000000000010000000
输出：1
解释：输入的二进制串 00000000000000000000000010000000 中，共有一位为 '1'。
示例 3：

输入：11111111111111111111111111111101
输出：31
解释：输入的二进制串 11111111111111111111111111111101 中，共有 31 位为 '1'。


提示：

输入必须是长度为 32 的 二进制串 。

### 循环判断

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans=0;
        while(n){
            if(n&1)++ans;
            n>>=1;
        }
        return ans;
    }
};
```

## Bit性质

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans=0;
        while(n){
            ++ans;
            n-=n&(-n);
        }
        return ans;
    }
};
```

## 剑指 Offer 16. 数值的整数次方（中等）

实现函数double Power(double base, int exponent)，求base的exponent次方。不得使用库函数，同时不需要考虑大数问题。

 

示例 1:

输入: 2.00000, 10
输出: 1024.00000
示例 2:

输入: 2.10000, 3
输出: 9.26100
示例 3:

输入: 2.00000, -2
输出: 0.25000
解释: 2-2 = 1/22 = 1/4 = 0.25


说明:

-100.0 < x < 100.0
n 是 32 位有符号整数，其数值范围是 [−231, 231 − 1] 。

```cpp
class Solution {
public:
    double myPow(double x, int n) {
        double ans=1;
        uint32_t nn=n;
        if(n<0)nn=-nn;
        while(nn){
            if(nn&1)ans*=x;
            x*=x;
            nn>>=1;
        }
        if(n<0)ans=1/ans;
        return ans;
    }
};
```

## 剑指 Offer 17. 打印从1到最大的n位数

输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。

示例 1:

输入: n = 1
输出: [1,2,3,4,5,6,7,8,9]


说明：

用返回一个整数列表来代替打印
n 为正整数

```cpp
class Solution {
public:
    int pow_(int a,int b){
        int ans=1;
        while(b){
            if(b&1)ans*=a;
            a*=a;
            b>>=1;
        }
        return ans;
    }
    vector<int> printNumbers(int n) {
        int m=pow_(10,n)-1;
        vector<int> ans;
        for(int i=1;i<=m;++i){
            ans.push_back(i);
        }
        return ans;
    }
};
```

## 剑指 Offer 18. 删除链表的节点（简单）

给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。

返回删除后的链表的头节点。

注意：此题对比原题有改动

示例 1:

输入: head = [4,5,1,9], val = 5
输出: [4,1,9]
解释: 给定你链表中值为 5 的第二个节点，那么在调用了你的函数之后，该链表应变为 4 -> 1 -> 9.
示例 2:

输入: head = [4,5,1,9], val = 1
输出: [4,5,9]
解释: 给定你链表中值为 1 的第三个节点，那么在调用了你的函数之后，该链表应变为 4 -> 5 -> 9.


说明：

题目保证链表中节点的值互不相同
若使用 C 或 C++ 语言，你不需要 free 或 delete 被删除的节点

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if(head->val==val)return head->next;
        ListNode* ans=head;
        ListNode* pre=head;
        head=head->next;
        while(head!=NULL){
            if(head->val==val){
                pre->next=head->next;
            }
            pre=head;
            head=head->next;
        }
        return ans;
    }
};
```

## 剑指 Offer 19. 正则表达式匹配（困难）

请实现一个函数用来匹配包含'. '和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但与"aa.a"和"ab*a"均不匹配。

示例 1:

输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。
示例 2:

输入:
s = "aa"
p = "a*"
输出: true
解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
示例 3:

输入:
s = "ab"
p = ".*"
输出: true
解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
示例 4:

输入:
s = "aab"
p = "c*a*b"
输出: true
解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
示例 5:

输入:
s = "mississippi"
p = "mis*is*p*."
输出: false
s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母以及字符 . 和 *，无连续的 '*'。

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        int ls=s.size(),lp=p.size();
        int dp[ls+5][lp+5];
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for(int i=0;i<=ls;++i){
            for(int j=1;j<=lp;++j){
                if(p[j-1]!='*'){
                    if(i>0&&(s[i-1]==p[j-1]||p[j-1]=='.'))dp[i][j]=dp[i-1][j-1];
                }else{
                    if(j>=2)dp[i][j]|=dp[i][j-2];//不用
                    if(i>0&&j>1&&(s[i-1]==p[j-2]||p[j-2]=='.'))dp[i][j]|=dp[i-1][j];
                }
            }
        }
        return dp[ls][lp];
    }
};
```



## 剑指 Offer 21. 调整数组顺序使奇数位于偶数前面（简单）

输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。

 

示例：

输入：nums = [1,2,3,4]
输出：[1,3,2,4] 
注：[3,1,2,4] 也是正确的答案之一。


提示：

1 <= nums.length <= 50000
1 <= nums[i] <= 10000

### 额外空间

```cpp
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        vector<int> a,b;
        for(int i=0,len=nums.size();i<len;++i){
            if(nums[i]&1)a.push_back(nums[i]);
            else b.push_back(nums[i]);
        }
        for(int i=0,len=b.size();i<len;++i){
            a.push_back(b[i]);
        }
        return a;
    }
};
```

### 首尾双指针

```cpp
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int len=nums.size();
        int left=0,right=len-1;
        while(left<right){
            while(left<right&&(nums[left]&1))++left;
            while(left<right&&!(nums[right]&1))--right;
            swap(nums[left],nums[right]);
        }
        return nums;
    }
};
```

### 快慢双指针

```cpp
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int len=nums.size();
        int left=0,right=0;
        while(right<len){
            while(right<len&&!(nums[right]&1))++right;
            if(right<len)
            swap(nums[left++],nums[right++]);
        }
        return nums;
    }
};
```

## 剑指 Offer 22. 链表中倒数第k个节点（简单）

输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。

例如，一个链表有 6 个节点，从头节点开始，它们的值依次是 1、2、3、4、5、6。这个链表的倒数第 2 个节点是值为 4 的节点。

 

示例：

给定一个链表: 1->2->3->4->5, 和 k = 2.

返回链表 4->5.

### 处理出链表长度然后计算是顺数第几个节点

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* p=head;
        int num=0;
        while(p!=NULL){
            p=p->next;
            ++num;
        }
        num-=k;
        p=head;
        while(num--){
            p=p->next;
        }
        return p;
    }
};
```

### 双指针处理指出k距离，同时右移

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* left,*right;
        left=right=head;
        int m=k;
        while(m--)right=right->next;
        while(right!=NULL){
            left=left->next;
            right=right->next;
        }
        return left;
    }
};
```

## 剑指 Offer 24. 反转链表（简单）

定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

 

示例:

输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL


限制：

0 <= 节点个数 <= 5000

### 遍历过程中变换指针方向

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head==NULL)return NULL;
        ListNode* p,* q,* t;
        p=head;
        q=head->next;
        p->next=NULL;
        while(q!=NULL){
            t=q->next;
            q->next=p;
            p=q;
            q=t;
        }
        return p;
    }
};
```

## 剑指 Offer 25. 合并两个排序的链表（简单）

输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。

示例1：

输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4
限制：

0 <= 链表长度 <= 1000

### 归并排序思想

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* ans=new ListNode;
        ListNode* p=ans;
        while(l1!=NULL&&l2!=NULL){
            if(l1->val<l2->val){
                p->next=l1;
                p=p->next;
                l1=l1->next;
            }else{
                p->next=l2;
                p=p->next;
                l2=l2->next;
            }
        }
        while(l1!=NULL){
            p->next=l1;
            p=p->next;
            l1=l1->next;
        }
        while(l2!=NULL){
            p->next=l2;
            p=p->next;
            l2=l2->next;
        }
        return ans->next;
    }
};
```

## 剑指 Offer 26. 树的子结构(中等)

输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)

B是A的子结构， 即 A中有出现和B相同的结构和节点值。

例如:
给定的树 A:

给定的树 B：

```
     3
    / \
   4   5
  / \
 1   2
```

给定的树 B：

```
   4 
  /
 1
```


返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。

示例 1：

输入：A = [1,2,3], B = [3,1]
输出：false
示例 2：

输入：A = [3,4,5,1,2], B = [4,1]
输出：true
限制：

0 <= 节点个数 <= 10000

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool ju(TreeNode* a,TreeNode* b){
        if(a==NULL&&b==NULL)return true;
        if(a==NULL&&b!=NULL)return false;
        if(a!=NULL&&b==NULL)return true;
        if(a->val!=b->val)return false;
        if(ju(a->left,b->left)==false)return false;
        if(ju(a->right,b->right)==false)return false;
        return true;
    }
    bool dfs(TreeNode* now,TreeNode* B){
        if(now==NULL)return false;
        if((now->val)==(B->val)){
            if(ju(now,B))return true;
        }
        if(dfs(now->left,B)||dfs(now->right,B))return true;
        return false;
    }
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if(B==NULL)return false;
        return dfs(A,B);
    }
};
```

## 剑指 Offer 27. 二叉树的镜像（简单）

请完成一个函数，输入一个二叉树，该函数输出它的镜像。

例如输入：

         4
       /   \
      2     7
     / \   / \
    1   3 6   9



镜像输出：

         4
       /   \
      7     2
     / \   / \
    9   6 3   1

 



示例 1：

输入：root = [4,2,7,1,3,6,9]
输出：[4,7,2,9,6,3,1]


限制：

0 <= 节点个数 <= 1000

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void solve(TreeNode* now){
        if(now==NULL)return;
        TreeNode* t=now->left;
        now->left=now->right;
        now->right=t;

        solve(now->left);
        solve(now->right);
    }
    TreeNode* mirrorTree(TreeNode* root) {
        solve(root);
        return root;
    }
};
```

## 剑指 Offer 28. 对称的二叉树（简单）

请实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。

例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

```
    1
   / \
  2   2
 / \ / \
3  4 4  3
```

但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:

```
    1
   / \
  2   2
   \   \
   3    3
```

 

示例 1：

输入：root = [1,2,2,3,4,4,3]
输出：true
示例 2：

输入：root = [1,2,2,null,3,null,3]
输出：false


限制：

0 <= 节点个数 <= 1000

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool solve(TreeNode* a,TreeNode* b){
        if(a==NULL&&b==NULL)return true;
        if(a==NULL||b==NULL)return false;
        if(a->val!=b->val)return false;
        if(solve(a->left,b->right)==false)return false;
        if(solve(a->right,b->left)==false)return false;
        return true;
    }
    bool isSymmetric(TreeNode* root) {
        if(root==NULL)return true;
        return solve(root->left,root->right);
    }
};
```

## 剑指 Offer 29. 顺时针打印矩阵（简单）

输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

示例 1：

输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]
示例 2：

输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]


限制：

0 <= matrix.length <= 100
0 <= matrix[i].length <= 100

### 用一个数组进行标记

```cpp
class Solution {
public:
    int vis[105][105];
    bool ju(int x,int y,int n,int m){
        if(x>=0&&x<n&&y>=0&&y<m&&vis[x][y])return true;
        return false;
    }
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int dir[4][2]={0,1,1,0,0,-1,-1,0};
        int n=matrix.size();
        vector<int> ans;
        if(n==0)return ans;
        int m=matrix[0].size();
        memset(vis,0,sizeof(vis));
        for(int i=0;i<n;++i)for(int j=0;j<m;++j)vis[i][j]=1;
        int i=0,j=0,ni,nj,di=0;
        ans.push_back(matrix[0][0]);
        int num=(n*m)-1;
        vis[0][0]=0;
        while(num){
            ni=i+dir[di][0];
            nj=j+dir[di][1];
            if(ju(ni,nj,n,m)){
                ans.push_back(matrix[ni][nj]);
                i=ni,j=nj;
                --num;
                vis[i][j]=0;
            }else{
                di=(di+1)%4;
            }
        }
        return ans;
    }
};
```

## 剑指 Offer 30. 包含min函数的栈（简单）

定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，调用 min、push 及 pop 的时间复杂度都是 O(1)。

 

示例:

MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.min();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.min();   --> 返回 -2.


提示：

各函数的调用总次数不超过 20000 次

### 双栈解法

```cpp
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> a,b;
    MinStack() {
        while(!a.empty())a.pop();
        while(!b.empty())b.pop();
    }
    
    void push(int x) {
        a.push(x);
        if(b.empty()||x<=b.top())b.push(x);
    }
    
    void pop() {
        if(a.top()==b.top())b.pop();
        a.pop();
    }
    
    int top() {
        return a.top();
    }
    
    int min() {
        return b.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */
```

## 剑指 Offer 31. 栈的压入、弹出序列（中等）

输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如，序列 {1,2,3,4,5} 是某栈的压栈序列，序列 {4,5,3,2,1} 是该压栈序列对应的一个弹出序列，但 {4,3,5,1,2} 就不可能是该压栈序列的弹出序列。

 

示例 1：

输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
输出：true
解释：我们可以按以下顺序执行：
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
示例 2：

输入：pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
输出：false
解释：1 不能在 2 之前弹出。


提示：

0 <= pushed.length == popped.length <= 1000
0 <= pushed[i], popped[i] < 1000
pushed 是 popped 的排列。

```cpp
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int lpush=pushed.size(),lpop=popped.size();
        stack<int> st;
        int i=0,j=0;
        while(j<lpop){
            if(st.empty()){
                if(i<lpush)
                    st.push(pushed[i++]);
                else
                    return false;
            }else{
                if(st.top()==popped[j]){
                    st.pop();
                    ++j;
                }else if(i<lpush){
                    st.push(pushed[i++]);
                }else{
                    return false;
                }
            }
        }
        return true;
    }
};
```

## 剑指 Offer 32 - I. 从上到下打印二叉树（中等）

从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。

 

例如:
给定二叉树: [3,9,20,null,null,15,7],

```
    3
   / \
  9  20
    /  \
   15   7
```

返回：

[3,9,20,15,7]


提示：

节点总数 <= 1000

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> levelOrder(TreeNode* root) {
        queue<TreeNode*> pq;
        vector<int> ans;
        TreeNode* now;
        pq.push(root);
        while(!pq.empty()){
            now=pq.front();
            pq.pop();
            if(now==NULL)continue;
            ans.push_back(now->val);
            if(now->left!=NULL)pq.push(now->left);
            if(now->right!=NULL)pq.push(now->right);
        }
        return ans;
    }
};
```

## 剑指 Offer 32 - II. 从上到下打印二叉树 II（简单）

从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。

 

例如:
给定二叉树: [3,9,20,null,null,15,7],

```
    3
   / \
  9  20
    /  \
   15   7
```

返回其层次遍历结果：

```
[
  [3],
  [9,20],
  [15,7]
]
```


提示：

节点总数 <= 1000

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        vector<int> res;
        TreeNode* now;
        if(root==NULL)return ans;
        queue<TreeNode*>pq;
        pq.push(root);
        while(!pq.empty()){
            int num=pq.size();
            res.clear();
            while(num--){
                now=pq.front();
                pq.pop();
                if(now==NULL)continue;
                res.push_back(now->val);
                if(now->left!=NULL)pq.push(now->left);
                if(now->right!=NULL)pq.push(now->right);
            }
            ans.push_back(res);
        }
        return ans;
    }
};
```

## 剑指 Offer 32 - III. 从上到下打印二叉树 III（中等）

请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。

 

例如:
给定二叉树: [3,9,20,null,null,15,7],

```
    3
   / \
  9  20
    /  \
   15   7
```

返回其层次遍历结果：

[
  [3],
  [20,9],
  [15,7]
]


提示：

节点总数 <= 1000

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        vector<int> res;
        TreeNode* now;
        if(root==NULL)return ans;
        queue<TreeNode*>pq;
        pq.push(root);
        int vis=0;
        while(!pq.empty()){
            int num=pq.size();
            res.clear();
            while(num--){
                now=pq.front();
                pq.pop();
                if(now==NULL)continue;
                res.push_back(now->val);
                if(now->left!=NULL)pq.push(now->left);
                if(now->right!=NULL)pq.push(now->right);
            }
            if(vis){
                int lres=res.size();
                for(int i=0;i<lres/2;++i){
                    swap(res[i],res[lres-i-1]);
                }
            }
            ans.push_back(res);
            vis^=1;
        }
        return ans;
    }
};
```

## 剑指 Offer 33. 二叉搜索树的后序遍历序列（中等）

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。

 

参考以下这颗二叉搜索树：

```
     5
    / \
   2   6
  / \
 1   3
```

示例 1：

输入: [1,6,3,2,5]
输出: false
示例 2：

输入: [1,3,2,6,5]
输出: true


提示：

数组长度 <= 1000

```cpp
class Solution {
public:
    bool ju(vector<int>& postorder,int l,int r){

        if(l>=r)return true;
        int i=l,j=r-1;
        while(i<r&&postorder[i]<postorder[r])++i;
        for(int k=i;k<r;++k){
            if(postorder[k]<postorder[r])return false;
        }
        if(ju(postorder,l,i-1)&&ju(postorder,i,r-1))return true;
        return false;
    }
    bool verifyPostorder(vector<int>& postorder) {
        return ju(postorder,0,postorder.size()-1);
    }
};
```

### 单调栈+逆序遍历

```cpp
class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        int len=postorder.size();
        stack<int> st;
        int pre=0x3f3f3f3f,now;
        for(int i=len-1;i>=0;--i){
            now=postorder[i];
            while(!st.empty()&&st.top()>now){
                pre=st.top();
                st.pop();
            }
            if(now>pre)return false;
            st.push(now);
        }
        return true;
    }
};
```

## 剑指 Offer 34. 二叉树中和为某一值的路径（中等）

输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。从树的根节点开始往下一直到叶节点所经过的节点形成一条路径。

 

示例:
给定如下二叉树，以及目标和 sum = 22，

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
返回:

[
   [5,4,11,2],
   [5,8,4,5]
]


提示：

节点总数 <= 10000

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> res;
    void dfs(TreeNode* now,int sum){
        if(now==NULL)return;
        sum-=now->val;
        res.push_back(now->val);
        if(sum==0&&now->left==NULL&&now->right==NULL){
            ans.push_back(res);
        }

        dfs(now->left,sum);
        dfs(now->right,sum);
        res.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        dfs(root,sum);
        return ans;
    }
};
```

## 剑指 Offer 35. 复杂链表的复制（中等）

请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。

 

示例 1：

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/09/e1.png)

输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
示例 2：

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/09/e2.png)

输入：head = [[1,1],[2,1]]
输出：[[1,1],[2,1]]
示例 3：

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/09/e3.png)

输入：head = [[3,null],[3,0],[3,null]]
输出：[[3,null],[3,0],[3,null]]
示例 4：

输入：head = []
输出：[]
解释：给定的链表为空（空指针），因此返回 null。


提示：

-10000 <= Node.val <= 10000
Node.random 为空（null）或指向链表中的节点。
节点数目不超过 1000 。

### map映射

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head==NULL)return NULL;
        Node* ans=new Node(head->val);
        Node* p=ans;
        Node* q=head->next;
        map<Node*,Node*>mp;
        mp[head]=ans;
        while(q!=NULL){
            p->next=new Node(q->val);
            p=p->next;
            mp[q]=p;
            q=q->next;
        }
        p=ans,q=head;
        while(p!=NULL){
            p->random=mp[q->random];
            p=p->next;
            q=q->next;
        }
        return ans;
    }
};
```

### 拼接+拆分链表

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head==NULL)return NULL;
        Node* ans;
        Node* q;
        Node* p=head;
        while(p!=NULL){
            q=new Node(p->val);
            q->next=p->next;
            p->next=q;
            p=p->next->next;
        }
        // return head;
        p=head;
        while(p!=NULL){
            q=p->next;
            if(p->random!=NULL)
                q->random=p->random->next;
            p=q->next;
        }
        p=head;
        ans=new Node(0);
        q=ans;
        while(p!=NULL){
            q->next=p->next;
            q=q->next;
            p->next=p->next->next;
            p=p->next;
        }
        return ans->next;
    }
};
```

## 剑指 Offer 36. 二叉搜索树与双向链表（中等）

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。

 

为了让您更好地理解问题，以下面的二叉搜索树为例：

 <img src="https://assets.leetcode.com/uploads/2018/10/12/bstdlloriginalbst.png" alt="img" style="zoom:67%;" />

我们希望将这个二叉搜索树转化为双向循环链表。链表中的每个节点都有一个前驱和后继指针。对于双向循环链表，第一个节点的前驱是最后一个节点，最后一个节点的后继是第一个节点。

下图展示了上面的二叉搜索树转化成的链表。“head” 表示指向链表中有最小元素的节点。

 <img src="https://assets.leetcode.com/uploads/2018/10/12/bstdllreturndll.png" alt="img" style="zoom:67%;" />

特别地，我们希望可以就地完成转换操作。当转化完成以后，树中节点的左指针需要指向前驱，树中节点的右指针需要指向后继。还需要返回链表中的第一个节点的指针。

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    //返回当前子树最大的节点（pre为当前子树的前驱节点，now为当前节点）
    Node* solve(Node* pre,Node* now){
        if(now==NULL)return NULL;
        if(now->left!=NULL){//如果左边有
            Node* p=solve(pre,now->left);//获取左子树最大节点。接在当前节点前
            p->right=now;
            now->left=p;
        }else{//如果没有说明当前节点为当前子树最小节点，连接前驱
            now->left=pre;
            pre->right=now;
        }
        if(now->right!=NULL){//如果右子树有
            return solve(now,now->right);//返回右子树最大节点
        }else{//否则当前节点为当前子树最大节点
            return now;
        }
    }
    Node* treeToDoublyList(Node* root) {
        if(root==NULL)return NULL;
        Node* st,*en;
        st=en=root;
        while(st->left!=NULL)st=st->left;//找到起始节点
        while(en->right!=NULL)en=en->right;//找到末尾节点
        solve(new Node(0),root);
        //连接起始和末尾节点
        st->left=en;
        en->right=st;
        return st;
    }
};
```

## 剑指 Offer 37. 序列化二叉树（困难）

请实现两个函数，分别用来序列化和反序列化二叉树。

示例: 

你可以将以下二叉树：

```
    1
   / \
  2   3
     / \
    4   5
```

序列化为 "[1,2,3,null,null,4,5]"

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        queue<TreeNode*> pq;
        pq.push(root);
        while(!pq.empty()){
            TreeNode* now=pq.front();
            pq.pop();
            if(now){
                out<<now->val<<" ";
                pq.push(now->left);
                pq.push(now->right);
            }else{
                out<<"null ";
            }
        }
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream input(data);
        string val;
        vector<TreeNode*> v;
        while(input>>val){
            if(val=="null"){
                v.push_back(NULL);
            }else{
                v.push_back(new TreeNode(stoi(val)));
            }
        }
        int j=1,len=v.size();
        for(int i=0;j<len;++i){
            if(v[i]==NULL)continue;
            if(j<len)v[i]->left=v[j++];
            if(j<len)v[i]->right=v[j++];
        }
        return v[0];
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
```

## 剑指 Offer 38. 字符串的排列（中等）

输入一个字符串，打印出该字符串中字符的所有排列。

 

你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。

 

示例:

输入：s = "abc"
输出：["abc","acb","bac","bca","cab","cba"]


限制：

1 <= s 的长度 <= 8

```cpp
class Solution {
private:
    vector<string> ans;
public:
    void dfs(int now,int len,string s){
        if(now==len)
        ans.push_back(s);
        map<char,int> mp;
        for(int i=now;i<len;++i){
            if(mp[s[i]])continue;
            mp[s[i]]=1;
            swap(s[now],s[i]);
            dfs(now+1,len,s);
            swap(s[now],s[i]);
        }
    }
    vector<string> permutation(string s) {
        dfs(0,s.size(),s);
        return ans;
    }
};
```

## 剑指 Offer 39. 数组中出现次数超过一半的数字（简单）

数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。

 

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

 

示例 1:

输入: [1, 2, 3, 2, 2, 2, 5, 4, 2]
输出: 2


限制：

1 <= 数组长度 <= 50000

### 排序

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        return nums[nums.size()/2];
    }
};
```

### 哈希

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        map<int,int>mp;
        int len=nums.size();
        for(int i=0;i<len;++i){
            mp[nums[i]]++;
            if(mp[nums[i]]>len/2)return nums[i];
        }
        return 0;
    }
};
```

### 投票

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int len=nums.size();
        int ans=0,num=0;
        for(int i=0;i<len;++i){
            if(num==0)ans=nums[i];
            if(nums[i]==ans)++num;
            else --num;
        }
        return ans;
    }
};
```

### 位运算

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int len=nums.size();
        int ans=0;
        for(int k=0;k<32;++k){
            int num=0;
            for(int i=0;i<len;++i){
                if(nums[i]&(1<<k))++num;
            }
            if(num>len/2)ans+=(1<<k);
        }
        return ans;
    }
};
```

## 剑指 Offer 40. 最小的k个数

输入整数数组 arr ，找出其中最小的 k 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。

 

示例 1：

输入：arr = [3,2,1], k = 2
输出：[1,2] 或者 [2,1]
示例 2：

输入：arr = [0,1,2,1], k = 1
输出：[0]


限制：

0 <= k <= arr.length <= 10000
0 <= arr[i] <= 10000

### 排序

```cpp
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        sort(arr.begin(),arr.end());
        vector<int>ans;
        for(int i=0;i<k;++i)ans.push_back(arr[i]);
        return ans;
    }
};
```

### 优先队列（堆）

```cpp
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        priority_queue<int>pq;
        vector<int>ans;
        if(k==0)return ans;
        int len=arr.size();
        for(int i=0;i<len;++i){
            if(i<k||arr[i]<pq.top()){
                pq.push(arr[i]);
                if(pq.size()>k){
                    pq.pop();
                }
            }
        }
        while(!pq.empty()){
            ans.push_back(pq.top());
            pq.pop();
        }
        return ans;
    }
};
```

### 快排思想

```cpp
class Solution {
public:
    void sort_(vector<int>&arr,int l,int r,int k){
        if(l>=r)return;
        int p=arr[l];
        int i=l,j=r;
        while(i<j){
            while(i<j&&arr[j]>=p)--j;
            while(i<j&&arr[i]<=p)++i;
            swap(arr[i],arr[j]);
        }
        swap(arr[l],arr[i]);
        if(i-l+1==k)return;
        if(i-l+1>k)sort_(arr,l,i-1,k);
        else sort_(arr,i+1,r,k-(i-l+1));
    }
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> ans;
        if(arr.size()==0)return ans;
        sort_(arr,0,arr.size()-1,k);
        for(int i=0;i<k;++i)ans.push_back(arr[i]);
        return ans;
    }
};
```

### 手写堆

```cpp
class Solution {
public:
    int heap[10005],lh;
    void adjustheap_down(int now){
        int ma=now;
        if((now<<1)<lh&&heap[now<<1]<heap[ma])ma=now<<1;
        if((now<<1|1)<lh&&heap[now<<1|1]<heap[ma])ma=now<<1|1;
        if(now!=ma){
            swap(heap[now],heap[ma]);
            adjustheap_down(ma);
        }
    }
    void adjustheap_up(int now){
        int fa=now>>1;
        if(fa==0)return;
        if(heap[now]<heap[fa]){
            swap(heap[now],heap[fa]);
            adjustheap_up(fa);
        }
    }
    void pop(){
        if(lh==0)return;
        swap(heap[1],heap[lh--]);
        adjustheap_down(1);
    }
    void push(int x){
        heap[++lh]=x;
        adjustheap_up(lh);
    }
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> ans;
        int len=arr.size();
        for(int i=0;i<len;++i)push(arr[i]);
        for(int i=0;i<k;++i){
            ans.push_back(heap[1]);
            pop();
        }
        return ans;
    }
};
```

### 计数

```cpp
class Solution {
public:
    int num[10005];
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> ans;
        int len=arr.size();
        for(int i=0;i<len;++i)++num[arr[i]];
        for(int i=0;i<=10000&&k>0;++i){
            if(num[i]){
                while(k>0&&num[i]--){
                    ans.push_back(i);
                    --k;
                }
            }
        }
        return ans;
    }
};
```

## 剑指 Offer 41. 数据流中的中位数（困难）

如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

例如，

[2,3,4] 的中位数是 3

[2,3] 的中位数是 (2 + 3) / 2 = 2.5

设计一个支持以下两种操作的数据结构：

void addNum(int num) - 从数据流中添加一个整数到数据结构中。
double findMedian() - 返回目前所有元素的中位数。
示例 1：

输入：
["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
[[],[1],[2],[],[3],[]]
输出：[null,null,null,1.50000,null,2.00000]
示例 2：

输入：
["MedianFinder","addNum","findMedian","addNum","findMedian"]
[[],[2],[],[3],[]]
输出：[null,null,2.00000,null,2.50000]


限制：

最多会对 addNum、findMedian 进行 50000 次调用。

### 最大最小堆

```cpp
class MedianFinder {
public:
    priority_queue<int>pq1;
    priority_queue<int,vector<int>,greater<int>>pq2;
    /** initialize your data structure here. */
    MedianFinder() {
        //while(!pq1.empty())pq1.pop();
        //while(!pq2.empty())pq2.pop();
    }
    void adjust(){
        while(pq1.top()>pq2.top()){
            int a=pq1.top(),b=pq2.top();
            pq1.pop(),pq2.pop();
            pq1.push(b),pq2.push(a);
        }
    }
    void addNum(int num) {
        if(pq1.empty())pq1.push(num);
        else if(pq2.empty()){
            pq2.push(num);
            adjust();
        }else{
            if((pq1.size()+pq2.size())&1)pq2.push(num);
            else pq1.push(num);
            adjust();
        }
    }
    
    double findMedian() {
        double ans;
        if(pq2.empty())ans=pq1.top();
        else if(pq1.size()==pq2.size()){
            ans=pq1.top()+pq2.top();
            ans/=2;
        }else ans=pq1.top();
        return ans;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
```

## 剑指 Offer 42. 连续子数组的最大和（简单）

输入一个整型数组，数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。

要求时间复杂度为O(n)。

 

示例1:

输入: nums = [-2,1,-3,4,-1,2,1,-5,4]
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。


提示：

1 <= arr.length <= 10^5
-100 <= arr[i] <= 100

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len=nums.size();
        int ans=nums[0],res=max(nums[0],0);
        for(int i=1;i<len;++i){
            res=max(nums[i],res+nums[i]);
            ans=max(ans,res);
        }
        return ans;
    }
};
```

## 剑指 Offer 43. 1～n 整数中 1 出现的次数（困难）

输入一个整数 n ，求1～n这n个整数的十进制表示中1出现的次数。

例如，输入12，1～12这些整数中包含1 的数字有1、10、11和12，1一共出现了5次。

 

示例 1：

输入：n = 12
输出：5
示例 2：

输入：n = 13
输出：6


限制：

1 <= n < 2^31

### 数位dp（搜索）

```cpp
class Solution {
public:
    int a[12],b[12],ans;
    int dfs(int now,int len,int vis){
        if(now>len)return 1;
        if(vis){
            ans+=(len-now+1)*b[len-now];
            return b[len-now+1];
        }
        int up=min(a[now],9),res=0;
        for(int i=0;i<=up;++i){
            int x=dfs(now+1,len,vis||(i!=up));
            res+=x;
            if(i==1)ans+=x;
        }
        return res;
    }
    int get(int x){
        int num=0;
        while(x){
            ++num;
            x/=10;
        }
        return num;
    }
    int countDigitOne(int n) {
        b[0]=1;
        for(int i=1;i<=9;++i)b[i]=b[i-1]*10;
        int len=get(n);
        int m=n;
        for(int i=len;i>=1;--i){
            a[i]=m%10;
            m/=10;
        }
        dfs(1,len,0);
        return ans;
    }
};
```

### 分情况讨论

```cpp
class Solution {
public:
    int get(int x){
        int num=0;
        while(x){
            ++num;
            x/=10;
        }
        return num;
    }
    int countDigitOne(int n) {
        int len=get(n),ans=0,x=n%10;
        long cur=1,heigh=n/10,low=0;
        for(int i=1;i<=len;++i){
            if(x==0){
                ans+=heigh*cur;
            }else if(x==1){
                ans+=heigh*cur+low+1;
            }else{
                ans+=(heigh+1)*cur;
            }
            low+=cur*x;
            x=heigh%10;
            heigh/=10;
            cur*=10;
        }
        return ans;
    }
};
```

## 剑指 Offer 44. 数字序列中某一位的数字（中等）

数字以0123456789101112131415…的格式序列化到一个字符序列中。在这个序列中，第5位（从下标0开始计数）是5，第13位是1，第19位是4，等等。

请写一个函数，求任意第n位对应的数字。

 

示例 1：

输入：n = 3
输出：3
示例 2：

输入：n = 11
输出：0


限制：

0 <= n < 2^31



