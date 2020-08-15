# Corn#8 题解

出题人对得分的**预期**：

|水平|T1得分|T2得分|T3得分|总分|
|:-:|:-:|:-:|:-:|:-:|
|AK NOIP|100|100|100|300|
|冲击省队|100|90(前90%)|40(1-3,6,11-14)|230|
|省一等奖|90(前90%)|60(前60%)|20(1-3,6)|170|
|省二等奖|60(前60%)|40(前40%)|15(前15%)|115|
|刚刚入门|20(前20%)|10(前10%)|5(前5%)|35|

## T1 校园游览 

`visit` | 1 sec | 256 MB | 10 Case

### 题意

给出一棵以 $1$ 为根的树，求在从 $1$ 到 $t$ 的链上走 $\frac{d}{2}$ 能到达的最远点。

### 标准解法

很容易想到：从 $1$ 出发向 $t$ 走的路径不容易得到，而从 $t$ 向 $1$ 的路径只需要每次走到当前点的父节点。

因此问题转化为：  
> 求从 $t$ 向根节点走 $dis_t - \frac{d}{2}$ 能到达的最远位置。  
> 若最后走到点 $x$ 上，则 $x$ 即为答案，若最后走到一条边 $e: x \rightarrow pnt_x$ 上，则 $pnt_x$ 即为答案。  
> 其中： $dis_t$ 表示从 $t$ 到 $1$ 的距离，$pnt_x$ 表示 $x$ 的父节点。

预处理出 $f_{p,i}$ 表示节点 $p$ 的 $2^i$ 辈祖先和 $d_{p,i}$ 表示 $p$ 到 $f_{p,i}$ 的距离，倍增求解即可。

#### 时空复杂度

时间复杂度：$\mathcal{O}\left(\left(n+m\right)\log n\right)$  
空间复杂度：$\mathcal{O}\left(n\log n\right)$，常数约为 $2$  

#### 标准程序

代码长度：1196

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define IO(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
using std::reverse;
const int N=1e5+10,L=18;
int n,m,x,y,z,t,s;
int f[N][L],d[N][L],dis[N];
struct edge {
	int to,nt,vl;
	inline void init(int t,int n,int v) {
		to=t,nt=n,vl=v;
	}
} e[N<<1];
int h[N],c;
inline void adde(int x,int y,int z) {
	e[++c].init(y,h[x],z),h[x]=c;
	e[++c].init(x,h[y],z),h[y]=c;
}
inline void dfs(int pos,int pnt=0) {
	for(int i=0; i+1<L&&f[pos][i]; ++i) {
		f[pos][i+1]=f[f[pos][i]][i];
		d[pos][i+1]=d[f[pos][i]][i]+d[pos][i];
	}
	for(int i=h[pos]; i; i=e[i].nt) {
		int son=e[i].to;
		if(son==pnt)continue;
		d[son][0]=e[i].vl;
		f[son][0]=pos;
		dis[son]=dis[pos]+e[i].vl;
		dfs(son,pos);
	}
}
inline int getAns(int pos,int dis) {
	for(int i=L-1; i>=0; --i)
		if(f[pos][i]&&d[pos][i]<=dis)dis-=d[pos][i],pos=f[pos][i];
	if(dis>0)pos=f[pos][0];
	return pos;
}
int main() {
	IO("visit");
	scanf("%d%d",&n,&m);
	for(int i=1; i<n; ++i)scanf("%d%d%d",&x,&y,&z),adde(x,y,z);
	dfs(1);
	for(int i=1; i<=m; ++i) {
		scanf("%d%d",&t,&s),s>>=1;
		printf("%d\n",getAns(t,dis[t]-s));
	}
}
```

### 特殊性质与部分分

#### 前 60%

时间复杂度小于等于 $\mathcal{O}\left(nm\right)$ 的暴力能够通过。

#### 特殊性质 1

「图是 $1$ 为一个端点的链」，将树上问题弱化为序列问题。

#### 特殊性质 0,2

「图随机生成」或「图是 $1$ 为根的满二叉树」，树的深度为 $\log n$ 级别，时间复杂度小于等于 $\mathcal{O}\left(m\cdot\max\left(depth\right)\right)$ 的暴力能够通过。

## T2 文件查找

`regex` | 1 sec | 512 MB | 20 Case

### 题意

有 $n$ 个字符串 $S_i$，全部由小写字母组成。  
另有 $m$ 个字符串 $T_j$，除小写字母外，每个字符串中有且仅有一个 $*$ 字符。  
其中 $*$ 字符能够匹配任意字符串（含空串）。  
对每个字符串 $T_j$，求有多少个字符串 $S_i$ 能被匹配。

### 标准解法

**<u>警告：本题标准解法较为复杂，而前 90% 部分的解法更加简单易懂。</u>**

#### 步骤 1

将所有 $S$ 串正、反建出两棵「**字典树**」 $\text{Trie}$、$\text{Trie}'$，将同一 $S$ 的结束位置 $end_S$、$end_S'$ **关联**。

用 $T$ 串 $*$ 前的子串在 $\text{Trie}$ 上匹配；$*$ 后的子串的反串在 $\text{Trie}'$ 上匹配。  
若任何一匹配失败，则 $T$ 不能与任何 $S$ 匹配。  
若均成功匹配，将在 $\text{Trie}$、$\text{Trie}'$ 上得到的匹配结束位置分别记为 $pos$、$pos'$。

原问题转化为：求 $\text{Trie}$ 中 $pos$ 的子树中所有点的**关联点**在 $\text{Trie}'$ 中 $pos'$ 的子树中有多少个。  
此问题能使用「**DFS 序**」解决。

#### 步骤 2

$\text{Trie}'$ 中 $pos'$ 的子树在 $\text{Trie}'$ 的 DFS 序中对应的区间为 $\left[{dfn}_{pos'},{dfn}_{pos'}+{siz}_{pos'}\right)$。  
其中 $dfn_{x}$ 表示 $x$ 被 DFS 到的次序，$siz_{x}$ 表示 $x$ 子树的大小（节点数），这个序列使用「**树状数组**」维护。

当在 $\text{Trie}$ 中 DFS 到 $end_S$ 时，在 $end_S'$ 对应的位置，即树状数组的 ${dfn}_{end_S'}$ 处 $+1$。  

在 DFS 到 $pos$ 时，首先（在包括上一段操作的所有操作之前）统计区间 $\left[{dfn}_{pos'},{dfn}_{pos'}+{siz}_{pos'}\right)$ 的和，这部分是由不在 $pos$ 子树中的 $end_S$ 产生的，应在答案中减去。  
之后递归 DFS $pos$ 的子树，当 $pos$ 的子树全部 DFS 完毕后，再次统计区间 $\left[{dfn}_{pos'},{dfn}_{pos'}+{siz}_{pos'}\right)$ 的和，此次统计与第一次统计的**差值**就是 $T$ 能够匹配的 $S$ 串数量。

具体实现时，可以将询问用「**链表**」链接在对应的 $pos$ 上。

#### 时空复杂度

记 $|S|=\sum length(s_i)$，$|T|=\sum length(T_j)$  
时间复杂度：$\mathcal{O}\left(|S|+|T|+m\log{|S|}\right)$  
空间复杂度：$\mathcal{O}\left(|S|\right)$，常数约为 $60$  

#### 标准程序

代码长度：2460

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define IO(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
using std::reverse;
const int N=2e6+10,S=26;
int n,m;
char s[N];
int ans[N];
int total,count;
struct BIT {
	int d[N];
	inline void update(int p) {
		for(; p<=count; p+=p&-p)++d[p];
	}
	inline int query(int p) {
		static int r;
		for(r=0; p; p-=p&-p)r+=d[p];
		return r;
	}
	inline int querySum(int l,int r) {
		return query(r)-query(l-1);
	}
} b;
struct queryNode {
	int toPos,next;
	inline void init(int t,int n) {
		toPos=t,next=n;
	}
} q[N];
struct trieNode {
	int c[S],v1,v2;
#define siz v1
#define dfn v2
#define link v1
#define first v2
	inline void clear() {
		v1=v2=0,memset(c,0,sizeof(c));
	}
	inline void addQuery(int i,int t) {
		q[i].init(t,first),first=i;
	}
} a[N];
inline void update(int pos,int flg=1) {
	static int tmp;
	for(int i=a[pos].first; i; i=q[i].next) {
		tmp=q[i].toPos;
		ans[i]+=flg*b.querySum(a[tmp].dfn,a[tmp].dfn+a[tmp].siz-1);
	}
}
inline int newNode() {
	a[++total].clear();
	return total;
}
struct trie {
	int root;
	inline trie():root(newNode()) {};
	inline int insert(char* s) {
		int pos=root,val;
		for(; *s; ++s) {
			val=(*s)-'a';
			if(!a[pos].c[val])a[pos].c[val]=newNode();
			pos=a[pos].c[val];
		}
		return pos;
	}
	inline int travel(char* s) {
		int pos=root,val;
		for(; *s!='*'; ++s) {
			val=(*s)-'a';
			if(!a[pos].c[val])return 0;
			pos=a[pos].c[val];
		}
		return pos;
	}
	inline int dfs1(int pos) {
		a[pos].siz=1,a[pos].dfn=++count;
		for(int i=0; i<26; ++i)
			if(a[pos].c[i])
				a[pos].siz+=dfs1(a[pos].c[i]);
		return a[pos].siz;
	}
	inline void dfs2(int pos) {
		update(pos,-1);
		if(a[pos].link)b.update(a[a[pos].link].dfn);
		for(int i=0; i<26; ++i)
			if(a[pos].c[i])
				dfs2(a[pos].c[i]);
		update(pos,1);
	}
} t[2];
int len,t0,t1;
inline void funcS() {
	scanf("%s",s);
	len=strlen(s),t0=t[0].insert(s);
	reverse(s,s+len),t1=t[1].insert(s);
	a[t0].link=t1;
}
inline void funcT(int i) {
	scanf("%s",s);
	len=strlen(s),t0=t[0].travel(s);
	reverse(s,s+len),t1=t[1].travel(s);
	if(t0&&t1)a[t0].addQuery(i,t1);
}
int main() {
	IO("regex");
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)funcS();
	t[1].dfs1(t[1].root);
	for(int i=1; i<=m; ++i)funcT(i);
	t[0].dfs2(t[0].root);
	for(int i=1; i<=m; ++i)printf("%d\n",ans[i]);
}
```

### 特殊性质与部分分

#### 前 90%

「$*$ 只出现在首或尾」，建出两棵字典树后求子树和即可。

#### 其他部分分

出题人为各种其他奇奇怪怪的暴力提供了充足的数据梯度。

## T3 成绩统计

`score` | 1 sec | 256 MB | 20 Case

### 题意

维护一个有序数列，支持：

- 插入 $x$
- 删除 $x$
- 查询 $x$ 的排名
- 查询 第 $k$ 名
- **将所有数十进制翻转** 

保证操作合法

### 标准解法

前 4 种操作显然是「**普通**~~平衡树~~**树状数组二分**」模板。

本题的关键在于对第 5 种操作的处理上。

首先探究十进制翻转的性质：
> 考虑一个十进制非负整数 $x$，记 $x$ 十进制翻转后得到的数为 $x^{-1}$，翻转 $t$ 次后得到的数为 $x^{-t}$。  
> 通常情况下 $x^{-2}=\left(x^{-1}\right)^{-1}=x$，如 ${19260817}^{-2}={71806291}^{-1}=19260817$；  
> 但也有一些例外，如 ${19190810}^{-2}={1809191}^{-1}=1919081$，容易发现数字结尾的 $0$ 在翻转两（或其他正偶数）次后被清除了。  
> 容易发现：任意非负整数在翻转两次之后无论再翻转几次，能得到的结果都只有两种：$x^{-1}$、$x^{-2}$。

综上，任意非负整数 $x$ 在翻转零或若干次后能得到的结果只可能有 $x$、$x^{-1}$、$x^{-2}$ 三种，可以提前离散化。

若执行第 5 种操作时将所有数都真正翻转一次，显然时间效率不能接受。

若只考虑 $x^{-1}$、$x^{-2}$ 两种值之间的转化，显然地，每种值只会在插入后又翻转了奇数（或偶数）次后出现。  
那么，所有这样的两个值都可以被分进两个组：共翻转了**奇数**次后能出现的值，共翻转了**偶数**次后能出现的值。

这样，就可以用**两个数据结构**分别维护每组中的数，查询时按当前翻转总次数向对应的数据结构查询即可。

对于 $x$ 的结尾存在 $0$ 的情况，可以为每个数据结构额外记录「**翻转两次后值发生变化的数**」的**表**。  
当向一个数据结构中插入一个结尾存在 $0$ 的正整数时，将其原值与翻转两次后的值加入此数据结构的**表**中。  
当翻转操作使一个数据结构成为当前的查询对象时，修改这些变化的数，同时清空表。  

#### 时空复杂度

时间复杂度：$\mathcal{O}\left(n\log n\right)$  
空间复杂度：$\mathcal{O}\left(n\right)$，常数约为 $20$  

#### 标准程序

代码长度：2866

```cpp
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<functional>
#define IO(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
using namespace std;
const int N=3e5+10,M=N*3;
int n,m,L,c=0;
int op[N],v1[N],v2[N],v3[N],vl[M];
inline bool isNum(const char&c) {return c>='0'&&c<='9';}
inline int getInt() {
	int r=0;
	char c=getchar(),d=0;
	while(!isNum(c))d=c,c=getchar();
	while(isNum(c))r=(r<<1)+(r<<3)+c-'0',c=getchar();
	return d=='-'?-r:r;
}
inline void putInt(const int&x) {if(x/10)putInt(x/10);putchar('0'+x%10);}
inline void putIntSp(int x) {if(x<0)x=-x,putchar('-');putInt(x),putchar(' ');}
inline void putIntNl(int x) {if(x<0)x=-x,putchar('-');putInt(x),putchar('\n');}
inline int isOp(const char&c) {
	switch(c) {
		case 'I':return 1;
		case 'D':return 2;
		case 'R':return 3;
		case 'K':return 4;
		case 'E':return 5;
	}
	return 0;
}
inline int getOp() {
	char c=getchar();
	while(!isOp(c))c=getchar();
	return isOp(c);
}
inline int getRev(int x) {
	static int s[10],n,r,f;
	n=r=f=0;
	if(x<0)x=-x,f=1;
	while(x)s[n++]=x%10,x/=10;
	for(int i=0; i<n; ++i)r=r*10+s[i];
	return f?-r:r;
}
inline void push(int x) {vl[m++]=x;}
inline void sort() {
	sort(vl,vl+m,greater<int>()),m=unique(vl,vl+m)-vl;
	while((1<<L)<m)++L;
}
inline int query(int x) {return lower_bound(vl,vl+m,x,greater<int>())-vl+1;}
inline int value(int k) {return vl[k-1];}
struct BIT {
	int d[M],t,l[N],r[N];
	inline BIT(): t(0) {};
	inline void update(int p,int v) {for(; p<=m; p+=p&-p)d[p]+=v;}
	inline int query(int p) {
		static int r;
		for(r=0; p; p-=p&-p)r+=d[p];
		return r;
	}
	inline int at(int p) {return query(p)-query(p-1);}
	inline void push(int x,int y) {l[t]=x,r[t++]=y;}
	inline void flush() {
		static int v;
		while(t)v=at(l[--t]),update(l[t],-v),update(r[t],v);
	}
	inline int find(int k) {
		static int r,i,t;
		for(r=0,i=L,--k; i>=0; --i) {
			t=r|(1<<i);
			if(t<=m&&d[t]<=k)k-=d[r=t];
		}
		return r+1;
	}
} t[2];
inline void ins(int x,int y,int z) {
	x=query(x),y=query(y),z=query(z);
	t[c].update(x,1),t[c^1].update(y,1);
	if(x^z)t[c].push(x,z);
}
inline void del(int x) {
	static int y;
	y=query(getRev(x)),x=query(x);
	t[c].update(x,-1),t[c^1].update(y,-1);
}
inline int rnk(int x) {return t[c].query(query(x)-1)+1;}
inline int kth(int k) {return value(t[c].find(k));}
inline void rev() {c^=1,t[c].flush();}
int main() {
	IO("score");
	n=getInt(),getInt();
	for(int i=0; i<n; ++i) {
		op[i]=getOp();
		if(op[i]==5)continue;
		v1[i]=getInt();
		if(op[i]!=1)continue;
		push(v1[i]);
		push(v2[i]=getRev(v1[i]));
		push(v3[i]=getRev(v2[i]));
	}
	sort();
	for(int i=0; i<n; ++i) {
		if(op[i]==1)ins(v1[i],v2[i],v3[i]);
		if(op[i]==2)del(v1[i]);
		if(op[i]==3)putIntNl(rnk(v1[i]));
		if(op[i]==4)putIntNl(kth(v1[i]));
		if(op[i]==5)rev();
	}
}
```

### 特殊性质及部分分

#### 前 40%

暴力模拟，时间复杂度：$\mathcal{O}\left(n^2\log n\right)$ 或 $\mathcal{O}\left(n^2\right)$

#### 特殊性质 A

「没有翻转操作」，模板题，随便过。

#### 特殊性质 B

「$x < n$」，不用离散化

#### 特殊性质 0

「没有删除操作，所有插入操作都在最开始进行」，对给定序列进行查询，注意**仍有翻转操作**，仍需要一些处理技巧。

#### 特殊性质 1

「所有查询操作都在插入删除操作之后」，先维护序列，再对给定的序列进行查询，注意**仍有翻转操作**，仍需要一些处理技巧。