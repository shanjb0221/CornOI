# Corn#2 题解

## T1 奆炮的重生

$by \ \text{fr200110217102}$

### 一句话题意

有一个环，每次可以

- 合并相邻两数$A$，$B$，得到的新数$A+B$

- 合并相邻三数$A$，$B$，$C$，得到的新数$A \times C - B$

求最终剩下的数的最大值。

- $T \leq 50$

- $n \leq 35$

- $Ans \leq 2^{63}-1$

### 算法一（前三个点）：手玩

$n=1$

……

$n=2$

A+B问题！

$n=3$

$Ans = \max(A+B+C,A \times B-C,A \times C-B,B \times C-A)$

$n=4$ / $n=5$

把所有情况都枚举出来就好了！反正一共才几十种。

### 算法二（前五个点）：暴力

DFS。

枚举合并的位置进行操作。

环长为$n$的时候有$\text{O} (n)$种合并的可能，所以复杂度是$\text{O}(n!)$级别。

### 算法三（所有点）：标算

区间DP。

~~这么明显的“相邻”“合并”还想不到区间DP吗~~

先破坏成链，把环复制一份，然后直接在$2n$的序列上做区间DP。

我们看到了减法，还看到了有正有负……所以要维护最大和最小值了。

设$f[l][r]=$将$[l,r]$合并为一个数的最大值，$g[l][r]=$将$[l,r]$合并为一个数的最小值

$f$的转移有3种：

$f[l][k]+f[k+1][r]$（合并两个）

$f[l][i] \times f[j][r]-g[i+1][j-1]$

$g[l][i] \times g[j][r]-g[i+1][j-1]$（合并三个，最大$\times$最大/最小$\times$最小。注意减最小值才是最大值）

$g$的转移有5种：最大$\times$最大，最小$\times$最小，最大$\times$最小，最小$\times$最大都有可能成为最小值。减的时候要减最大值。

本题数据比较水，$g$只用最大$\times$最小和最小$\times$最大转移也可以做。

最终答案就是$\max(f[1][n],f[2][n+1],...,f[n][2*n-1])$。

时间复杂度：$\text{O}\left(n^4\right)$

### std部分代码

```cpp
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%lld",&a[i]),a[i+n]=a[i];
    m=n<<1;
    for(int i=1;i<=m;++i)s[i]=s[i-1]+a[i];
    for(int i=1;i<=m;++i)for(int j=i;j<=m;++j)
        f[i][j]=g[i][j]=s[j]-s[i-1];
    for(int len=2;len<=n;++len)for(int l=1;l<=m-len+1;++l){
        int r=l+len-1;
        for(int i=l;i<r;++i){
            cmax(f[l][r],f[l][i]+f[i+1][r]);
            cmin(g[l][r],g[l][i]+g[i+1][r]);
        }
        for(int i=l;i<r-1;++i)for(int j=i+2;j<=r;++j){
            cmax(f[l][r],f[l][i]*f[j][r]-g[i+1][j-1]);
            cmax(f[l][r],g[l][i]*g[j][r]-g[i+1][j-1]);
            cmin(g[l][r],f[l][i]*f[j][r]-f[i+1][j-1]);
            cmin(g[l][r],g[l][i]*g[j][r]-f[i+1][j-1]);
            cmin(g[l][r],f[l][i]*g[j][r]-f[i+1][j-1]);
            cmin(g[l][r],g[l][i]*f[j][r]-f[i+1][j-1]);
        }
    }
    ll ans=-1e18;
    for(int i=1;i<=n;++i)cmax(ans,f[i][i+n-1]);
    printf("%lld\n",ans);
}
```

### 一个假的标算

如果你写了区间DP，但是你每次都重新做了一遍区间DP，

那么恭喜你可以获得80~90分的高分！

### 总结

定位：送分题

~~这100分是出题人对选手慷慨的馈赠。~~

~~出题人希望这道题能为你未来的NOIP之路提供一个有力的援助。~~

---

## T2 幽香的宴会

 $by \ \text{Wy12121212}$

### 一句话题意

给出一个图，每个点有权值，每条边有海拔 $p_i$。

给出一常数 $k$ ，$T$  次询问在只保留海拔大于等于 $P_i$ 的边时 $c_i$ 所在连通块中前 $k$ 大点权之和为多少。

- $n,m,T\leq 2 \times 10^5$

- $k \leq 10^4$

- 询问**不强制在线**

### `Case 1  ~  16`

- $n,m,T \leq 10^3$

- $k\leq 10^2$

考虑暴力。

我们直接从  $c_i$  遍历（只走可行边），将访问到的点权塞入小根堆中，当小根堆大小大于 $k$ 的时候弹出堆顶即可

或者直接拿个数组存一下，遍历完后排个序取出前 $k$ 大累加即可

时间复杂度 $\text{O}\left( Tn \log k \right) \text{ or } \text{O}\left( Tn \log n \right)$

### `Case 17`

- $n,m,T \leq 2 \times 10^5$

- $k=1$

- $P_i \geq P_{i-1}$
  
  $P_i$ 单调不减意味着边会被一条一条去掉，这个我们不方便维护。

因此将询问倒过来做，那么 $P_i \leq P_{i-1}$ ，所以我们是在一条一条向图中加边。

我们使用并查集经行维护，因为 $k = 1$ 所以我们只需要维护每个集合的最大值，在并查集合并 $fa$ 的时候顺便合并最大值即可。

时间复杂度 $\text{O}\left(n \alpha \left(n\right)\right)$

### `Case 18  ~  19`

- $n,m,T \leq 2 \times 10^5$

- $k=1$

$P_i$ 没有单调性，那么我们将询问按照 $P_i$ 从大到小排序，将每条边按照 $p_i$ 从大到小排序。

这样我们维护两个指针 $i,j$， 分别指向正在处理的询问和第一个还没有加入图中的边，每次 $i$ 右移一位，然后 $j$ 右移直至 $p_j < P_i$ 即可， $j$ 在右移的过程中要将访问到的边全部加入图。

同样使用并查集维护连通性即最大值。

时间复杂度 $\text{O}\left(n \log n\right)$

### `Case 20`

- $n,m,T \leq 2 \times 10^5$

- $k=2$

- $P_i \geq P_{i-1}$

类似于 `Case 17` 的做法，但是 $k = 2$ 意味着我们要维护每个集合的最大值和次大值。

那么在合并两个集合的时候讨论一下即可得到新的最大值和次大值了。

或者更通用的方法是将两个集合的最大次大值塞到大根堆（优先队列）中再取出最大的两个即可。

复杂度同 `Case 17` 

### `Case 21  ~  22`

- $n,m,T \leq 2 \times 10^5$

- $k=2$

将前两种做法结合起来就可以了。

### `Case 23`

- $n,m,T \leq 2 \times 10^5$

- $k \leq 10^4$

- $P_i = 0$

比较靠后的送分点

由于 $P_i = 0$ ，所以没有边不能走，我们直接先建出整个图，加边用并查集维护。

之后将每个点的权值加入到它所在连通块所对应的小根堆（优先队列）中并将该连通块的当前答案加上点权，同样的在小根堆大小超过 $k$ 的时候将连通块的答案减去堆顶权值并弹出堆顶即可。

查询的时候直接输出 $c_i$ 所在所在连通块的答案即可。

时间复杂度 $\text{O}\left(n \log k\right)$

### Case 24  ~  25:

- $n,m,T \leq 2 \times 10^5$

- $k \leq 10^4$

（我们可以通过离线排序保证 $P_i$ 的单调性，所以两个 `Case` 本质相同，故不分开讨论）

~~这是防AK的部分分，不感兴趣的同学可以跳过~~

首先，我们大概要延续 `Case 21 ~ 22` 的做法，所以我们需要对每个集合维护前 $k$ 大的值，接下来考虑一下如何暴力合并两个集合前 $k$ 大的值。

- 对每个集合维护一个小根堆（优先队列）

- 两个集合合并时，不断弹出较小的小根堆堆顶直至两个小根堆的大小之和小于等于  $k$ ，那么现在两个堆内的元素就是合并后前 $k$ 大的值

- 将一个堆中的所有元素**暴力**弹出并加到另一个堆中

正解就是在这种做法的基础上使用了并查集的按秩合并，即将小的集合的堆暴力合并到大的集合的堆中。

假设 $n,k$ 同级的最劣情况，那么没有点会被弹出，根据按秩合并的原理，每个点最多被合并 $\log n$ 次，而单次合并复杂度为 $\log k$ ，所以时间复杂度为 $\text{O}\left(n \log n \log k\right)$

### std部分代码

```cpp
int main(){
    read(n),read(m);
    for(int i=1;i<=n;++i){
        f[i]=i,s[i]=1;
        read(x),sum[i]=x;
        q[i].push(x);
    }
    for(int i=1;i<=m;++i)e[i].init();
    read(T),read(k);
    for(int i=1;i<=T;++i)g[i].init(i);
    sort(e+1,e+m+1);
    sort(g+1,g+T+1);
    for(int i=1,j=1;i<=T;++i){
        while(j<=m&&e[j].p>=g[i].p)
            merge(e[j].x,e[j].y),++j;
        ans[g[i].i]=sum[fnd(g[i].x)];
    }
    for(int i=1;i<=T;++i)wtln(ans[i]);
}
```

```cpp
inline int fnd(int x){
    return x==f[x]?x:f[x]=fnd(f[x]);    
}
inline void merge(int x,int y){
    x=fnd(x),y=fnd(y);
    if(x==y)return;
    if(s[x]>s[y])x^=y^=x^=y;
    f[x]=y,s[y]+=s[x],sum[y]+=sum[x];
    while(!q[x].empty())q[y].push(q[x].top()),q[x].pop();
    while(s[y]>k)sum[y]-=q[y].top(),q[y].pop(),--s[y];    
}
```

---

## T3 玉米的丰收

$by \ \text{2017sjb.}$

### 一句话题意

在图中任选一点（点上，边上均可），使该点到图中其他点的距离的最大值最小。

求该最小值。

- $n \leq 300$
- $m \leq 20000$
- $w_i \leq 100000$

### `Case 1 ~ 8`

- $n \leq 5$
- $m \leq 6$

大力讨论即可。

### `Case 1 2 4 7 9 11 13 15 18`

- $m = n - 1$

容易发现在树的直径的中点处最优。

直接求出树的直径，再除2即可。

时间复杂度： $\text{O} \left( n \right)$

### `Case 9 ~ 12`

- $n \leq 50$
- $m \leq 400$
- $w_i \leq 1000$

受树的情形的启发，继续分析，发现最优位置具有几个性质：

- 最优位置到至少两个点的距离等于最远距离【若只有一个点，则将最优位置向靠近这个点的方向移动会使最远距离变小】。
- 到最优位置距离等于最远距离的点中至少存在一对点在最优位置的两侧（最优位置在以这对点为两端的一条链的中点处）【若所有点都在同侧，则将最优位置向这一侧移动将使最远距离变小】。

因此最远距离的最小值等于图中某条链的长度$/2$，一定是 $0.5$ 的正整数倍，那么把所有边权$\times 2$，就能使最远距离变为整数。

考虑枚举最优位置所属的边，到边端点的距离，用 `SPFA/Dijkstra` 求出最远距离即可。

时间复杂度：$\text{O} \left( km^2w \right)$

继续观察发现，可以用 `Floyd` 预处理求出图中任意两点间的最短距离，那么点 $i$ 到最优位置的距离可以快速求出：

> 设 点 $i$ 到点 $j$ 最短距离为 $d[i][j]$
> 
> 设 最优位置所在边为 $x \leftrightarrow y$ ，边权为 $len$
> 
> 设 最优位置到点 $x$ 距离为 $dis$，$dis \in \left[ 0,len \right]$
> 
> 则 最优位置到点 $y$ 距离为 $len - dis$
> 
> 则 点 $i$ 到最优位置的距离为 $\min \left( d[i][x] + dis , d[i][y] + len - dis \right)$

时间复杂度：$\text{O} \left( n^3 + nmw \right)$

可以通过 `Case 13`。

继续观察发现，可以快速排除一些最优位置不可能出现的边：

> 考虑一条边 $x \leftrightarrow y$ ，边权为 $len$
> 
> 若 $d[x][y]<len$ 即：图中存在一条更短的路径，那么最优位置不可能出现在这条边上【若最优路径在这条边上，则把最优位置换到从 $x$ 到 $y$ 的更短路径上到 $x$ 距离不变的位置，再向靠近 $x$ 的方向移动一段距离，最远距离单调不增】

由于**数据随机**，使用这个剪枝可以再通过 `Case 14`。

若每次再使用当前最优答案进行剪枝，那么可以**~~暴力踩标算~~** `AC` 本题。

**~~这是出题人推荐的解法。~~**

### 部分代码

```cpp
struct edge{
    int x,y,z;
    inline void init(){
        scanf("%d %d %d\n",&x,&y,&z),z<<=1;
        d[x][y]=d[y][x]=z;
    }
    inline bool operator<(const edge& e)const{
        return z<e.z;
    }
    inline bool poss(){
        return d[x][y]==z;    
    }
}e[M];
inline int check(int x,int y,int dx,int dy) {
    int res=0;
    for(int i=1;i<=n;++i)
        res=max(res,min(d[x][i]+dx,d[y][i]+dy));
    return res;
}
inline void judge(int x,int y,int dis) {
    if(dis>=2*ans)return;
    for(int i=1;i<=n;++i)if(min(d[i][x],d[i][y])>=ans)return;
    int i=0;
    for(;i<=dis&&i<ans;++i)
        ans=min(ans,check(x,y,i,dis-i));
    i=max(i,dis-ans+1);
    for(;i<=dis;++i)
        ans=min(ans,check(x,y,i,dis-i));
}
int main() {
    //   ...
    for(int i=1; i<=m; ++i)e[i].init();
    //   ...
    std::sort(e+1,e+m+1);
    for(int i=1; i<=m; ++i)
        if(e[i].poss())judge(e[i].x,e[i].y,e[i].z);
    //   ...
}
```

~~以下为防AK部分，请谨慎阅读。~~

### `Case 13 ~ 17`

- $n \leq 200$
- $m \leq 5000$
- $w_i \leq 10000$

考虑对上一解法做出优化：

- 枚举最优位置所属的边，用**二分**求出最优位置在当前边上时的最远距离的最小值。

二分方法：

> $len$，$dis$ 均沿用上一解法中的定义
> 
> 设 当前二分的最远距离为 $mid$
> 
> 则 存在最优位置等价于存在 $dis$ 使任意点 $i$ 均满足：$mid \leq \min \left( d[i][x] + dis , d[i][y] + len - dis \right)$
> 
> 整理得 $dis \geq mid - d[i][x]$ 或 $dis \leq len + d[i][y] -mid$
> 
> 即 $dis \in \left[ 0,mid - d[i][x] \right] \cup \left[len + d[i][y] -mid,len\right]$
> 
> $n$ 个集合的交集不为空集则存在最优位置，反之不存在
> 
> 但对 $n$ 个这样的集合求交集很困难，考虑这些集合的特殊性质：
> 设 $\left[0,len\right]$ 为全集，第 $i$ 个集合的补集为 $\left(mid - d[i][x],len + d[i][y] -mid\right)$
> 
> 原先的 $n$ 个集合的交集不为空集等价于 $n$ 个补集的并集不为全集，问题转化为了求 $n$ 个开区间的并集，可以使用快速排序在 $\text{O} \left( n \log n \right)$ 时间内解决

时间复杂度：$\text{O} \left( mn \log n \log w \right)$

### `Case 18 ~ 20`

- $n \leq 300$
- $m \leq 20000$
- $w_i \leq 100000$

上一解法还可以进一步优化：

> 设 当前在边 $x \leftrightarrow y$ 上二分
> 
> 要进行求并的 $n$ 个区间都形如：$\left(mid - d[i][x],len + d[i][y] -mid\right)$
> 
> 注意到两个区间左端点的相对大小关系，与 $mid$ 的取值无关，因此可以在二分之前把所有区间预先排序好，这样一次二分的复杂度就可以优化成 $\text{O} \left( n \right)$

时间复杂度：$\text{O} \left( mn \left( \log n +\log w \right) \right)$

### std部分代码

```cpp
std::pair<int,int> b[N];
inline bool check(int dis,int lim) {
    for(int i=1,R=0; i<=n; ++i) {
        if(b[i].first+lim>=R)return 1;
        R=max(R,b[i].second-lim);
        if(R>dis)return 0;
    }
    return 1;
}
inline void judge(int x,int y,int dis) {
    for(int i=1;i<=n;++i){
        if(min(d[i][x],d[i][y])>=ans)return;
        b[i]=std::make_pair(-d[i][x],dis+d[i][y]);
    }
    std::sort(b+1,b+n+1);
    if(!check(dis,ans))return;
    int L=0,R=ans-1,mid;
    while(L<=R) {
        mid=(L+R)>>1;
        if(check(dis,mid))ans=mid,R=mid-1;
        else L=mid+1;
    }
}
```

### `Case 6 10 14 19`

三分需要保证原函数为单峰/谷函数。

本题中的函数并非单谷函数，但在随机数据下大多呈单谷趋势。

这些测试点经过了一些构造，可能使一些三分的解法 `WA`。
