# 数据结构/算法——interview

## 平衡二叉树

非叶子节点只能允许最多两个子节点存在

每一个非叶子节点数据分布规则为左边的子节点小当前节点的值，右边的子节点大于当前节点的值

保证数据的左右两边的节点层级相差不会大于1



## B树

平衡多路查找树（查找路径不只两个）

所有节点关键字是按递增次序排列，并遵循左小右大原则

所有叶子节点均在同一层、叶子节点除了包含了关键字和关键字记录的指针外也有指向其子节点的指针只不过其指针地址都为null对应下图最后一层节点的空格子

非叶节点的子节点数>1，且<=M ，且M>=2

子节点的关键字数量大于等于ceil(m/2)-1个且小于等于M-1个

## B+树

B+树更充分的利用了节点的空间，让查询速度更加稳定，其速度完全接近于二分法查找

B+跟B树不同B+树的**非叶子**节点不保存关键字记录的指针，只进行数据索引，这样使得B+树每个**非叶子**节点所能保存的关键字大大增加

B+树**叶子**节点保存了父节点的所有关键字记录的指针，所有数据地址必须要到叶子节点才能获取到。所以每次数据查询的次数都一样

B+树叶子节点的关键字从小到大有序排列，左边结尾数据都会保存右边节点开始数据的指针。



## 红黑树

**每个节点或者是黑色，或者是红色**

**根节点是黑色**

**每个叶子节点（NIL）是黑色**

**如果一个节点是红色的，则它的子节点必须是黑色的**

**从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点**

## 排序

### 快速排序

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e5+5;
const int inf=0x3f3f3f3f;
int w[maxn],n;
void sort_(int l,int r){
    if(l>=r)return;
    int p=w[l],i=l,j=r;
    while(i<j){
        while(w[j]>=p&&i<j)--j;
        while(w[i]<=p&&i<j)++i;
        swap(w[i],w[j]);
    }
    w[l]=w[i];
    w[i]=p;
    sort_(l,i-1);
    sort_(i+1,r);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;++i)cin>>w[i];
    sort_(1,n);
    for(int i=1;i<=n;++i){
        cout<<w[i]<<(i==n?'\n':' ');
    }
}
```

### 堆排序

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e5+5;
const int inf=0x3f3f3f3f;
int w[maxn];
void adjustheap(int now,int len){
    int l,r;
    while(now<=len){
        l=now<<1,r=now<<1|1;
        int ma=now;
        if(l<=len&&w[l]>w[ma])ma=l;
        if(r<=len&&w[r]>w[ma])ma=r;
        if(ma!=now){
            swap(w[now],w[ma]);
            now=ma;
        }else{
            return;
        }
    }
}
void sort_(int n){
    for(int i=n/2+1;i>=1;--i){
        adjustheap(i,n);
    }
    while(n>1){
        swap(w[1],w[n]);
        adjustheap(1,--n);
    }
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;++i)cin>>w[i];
    sort_(n);
    for(int i=1;i<=n;++i){
        cout<<w[i]<<(i==n?'\n':' ');
    }
}
```

## 跳表

## 压缩列表

