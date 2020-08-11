@import "Corn.less"

# "CornOI"CUP #1 题解

## T1 排课表 简易题解

### $30 \%$

大力搜索即可

注意：先搜索第一节和最后一节会大大提升程序运行效率

### $100 \%$

根据容斥原理容易得知：
答案=（不考虑任何限制的方案数）-（违反限制a不考虑限制b的方案数）-（违反限制b不考虑限制a的方案数）+（同时违反限制a和限制b的方案数）

即：$ Ans = A_n^m - aA_{n-1}^{m-1} - bA_{n-1}^{m-1} + abA_{n-2}^{m-2} $
整理化简得：$ Ans= \left(\left(n-1\right)\left(n-a-b\right)+ab\right)\cdot \frac{\left(n-2\right)!}{\left(n-m\right)!}$

预处理阶乘，QuickPow求逆元即可

注意：  

+ > **`int`一时爽，溢出火葬场。**

总复杂度：$\text{O}\left(N+TlogN\right)$

## T2 玉米田

题目大意:用 $k$ 种颜色染一个 $n$ 元环，要求相邻位置颜色不同，环不能旋转

部分分:
$k=2$ 时，$ans=
\begin{cases}
0& \text{n为偶数}\\
2& \text{n为奇数}
\end{cases}$ 这是一个很平凡的结论

$n$，$k$ 很小时，可以考虑暴力搜索，时间复杂度 $O(方案数)$
$n$，$k$ 为 $10^5$ 级别时，暴力显然行不通了，那么我们考虑一个更简单的情况:
>一条长为 $n$ 的链用 $k$ 种颜色染，要求相邻位置颜色不同

在这种情况下，答案显然是 $k*(k-1)^{n-1}$

为什么环上不行呢?因为第 $n$ 号位置的可染颜色不一定是 $k-1$，而是取决于第 $1$ 和第 $n-1$ 号位置的颜色是否相同

那么我们来分类讨论:(记 $i$ 个位置染 $k$ 种颜色的方案数为 $f[i]$ )

`Case1`: 第 $1$ 和第 $n-1$ 号位置的颜色相同

那么我们可以将第 $n-1$，$n$，$1$ 号位置当成一个位置，且这个合并起来的位置的颜色 $col=col[n-1]=col[1]$，那么被夹在中间的 $col[n]$ 有 $k-1$ 中染法

我们发现这样合并相当于将位置减小了两个，所以 $f[n]+=(k-1)*f[n-2]$

`Case2`: 第 $1$ 和第 $n-1$ 号位置的颜色不同

那么我们可以将第 $n$ 号位置删除，现在 $1$ 号位置和第 $n-1$ 号位置相邻，统计出的答案一定满足`Case2`，那么将第 $n$ 号位置再加回来后有 $k-2$ 种染法

我们发现这样相当于将位置删除了一个，所以 $f[n]+=(k-2)*f[n-1]$

所以
$$f[i]=(k-1)*f[n-2]+(k-2)*f[n-1]$$

复杂度 $O(n)$ 

由于 $n$ 为 $1e9$ 级别，所以运用矩阵快速幂解决问题，复杂度 $O(logn)$

* 找规律也可AC

## T3 评测机

这里规定 $n$ 与 $m$ 同阶，$A=max(a_i)$

### `Case 1 ~ 2`：

暴力乘完分解即可

复杂度：$O($乱搞$)$

这么做的瓶颈是乘积会炸`long long`……

什么？你说乘积取模再分解？~~你可以回家了~~

### `Case 3 ~ 8`：

先分解所有 $a_i$。由于每个 $a_i$ 都只有`5`个质因数，所以分解的复杂度只有 $O(logA)$。把每个 $a_i$ 的质因数及其幂次都存入一个数组`c[N][5]`中（其中`c[i][0...4]`分别表示 $a_i$ 的分解中 $2$、$3$、$5$、$7$、$11$ 的幂次）。这步预处理的复杂度为 $O(5nlogA)$

从 $x$ 和 $y$ 暴力向上跳，同时把经过的点的每个质因数的幂次都加到数组`res[5]`中。这样就算出了乘积的质因数分解

最后用约数和公式即可得出答案（不需要等比数列求和，甚至不需要快速幂。暴力即可）

复杂度总为 $O(n^2+nlogA)$

### `Case 9 ~ 14`：

因为 $a_i$ 的质因数只有 $2$，所以乘积中 $a_i$ 的质因数也只有 $2$，即乘积一定是 $2$ 的幂次

那么我们直接把 $a_i$ 换成 $log_2a_i$，问题就变成了《[模板] [LCA] 牧场行走》了。直接按照那道题的做法去倍增就好了。最后得到乘积的幂次 $k$ 后答案就是 $2^{k+1}-1$

注意，这是点权和不是边权和。算 $dist(x，y)$ 的公式是
$dist(x，y)=dis[x]+dis[y]-dis[lca]-dis[fa[lca]]$

### `Case 15 ~ 20`：

沿用`9 ~ 14`组的做法。将每个数的分解存入结构体中（存入数组也可以，不过结构体可以直接重载乘除很方便）

算约数和用公式+等比数列求和即可

```cpp
struct node{
	int c[5];
	inline node(){memset(c，0，sizeof(c));}
	inline node operator*(const node& p)const{
		node res;
		for(int i=0;i<5;++i)res.c[i]=c[i]+p.c[i];
		return res;
	}
	inline node operator/(const node& p)const{
		node res;
		for(int i=0;i<5;++i)res.c[i]=c[i]-p.c[i];
		return res;
	}
	inline ll sigma1(){
		ll res=1;
		for(int i=0;i<5;++i)res=res*(qpow(P[i]，c[i]+1)-1)%mod;
		return res*iP5%mod; //这里iP5=792475是(2-1)*(3-1)*(5-1)*(7-1)*(11-1)模20020421意义下的逆元。提前预处理出来即可。
	}
}dis[N];
inline node div(int x){
	node res;
	for(int i=0;i<5;++i)
		while(!(x%P[i]))x/=P[i]，++res.c[i];
	return res;
}
```

和倍增的想法类似。预处理 $dis[x]=$ 根到 $x$ 经过的所有节点的积的分解

```cpp
void dfs(int u){
	for(int i=0;fa[u][i];++i)
		fa[u][i+1]=fa[fa[u][i]][i];
	for(int i=0，sz=e[u].size();i<sz;++i){
		int v=e[u][i];
		if(v==fa[u][0])continue;
		fa[v][0]=u;
		dep[v]=dep[u]+1;
		dis[v]=dis[u]*div(a[v]);
		dfs(v);
	}
}
```

倍增的作用仍然仅有求$\text{LCA}$……

```cpp
inline int lca(int x，int y){
	if(dep[x]<dep[y])swap(x，y);
	int t=dep[x]-dep[y];
	for(int i=0;t;++i，t>>=1)
		x=t&1?fa[x][i]:x;
	if(x==y)return x;
	for(int i=17;~i;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i]，y=fa[y][i];
	return fa[x][0];
}
```

乘除和加减的性质类似，所以

```cpp
inline int dist(int x，int y){
	int f=lca(x，y);
	return (dis[x]*dis[y]/dis[f]/dis[fa[f][0]]).sigma1();
}
```

总复杂度为 $O(nlogn+nlogA)$