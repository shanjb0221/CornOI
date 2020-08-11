#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
inline ll read() {
	register ll res=0;
	register char c=getchar(),f=1;
	while(c<48||c>57) {
		if(c=='-')f=0;
		c=getchar();
	}
	while(c>=48&&c<=57)res=(res<<3)+(res<<1)+(c&15),c=getchar();
	return f?res:-res;
}
inline void write(ll x) {
	register char c[21],len=0;
	if(!x)return putchar('0'),void();
	if(x<0)x=-x,putchar('-');
	while(x)c[++len]=x%10,x/=10;
	while(len)putchar(c[len--]+48);
}
inline void space(ll x) {
	write(x),putchar(' ');
}
inline void enter(ll x) {
	write(x),putchar('\n');
}

const int N=1e5+10,mod=20020421;
const int P[5]= {2,3,5,7,11};
const int iP5=792475;
inline ll qpow(ll x,int y) {
	ll res=1;
	for(; y; y>>=1)res=y&1?res*x%mod:res,x=x*x%mod;
	return res;
}

struct node {
	int c[5];
	inline node() {
		memset(c,0,sizeof(c));
	}
	inline node operator*(const node& p)const {
		node res;
		for(int i=0; i<5; ++i)res.c[i]=c[i]+p.c[i];
		return res;
	}
	inline node operator/(const node& p)const {
		node res;
		for(int i=0; i<5; ++i)res.c[i]=c[i]-p.c[i];
		return res;
	}
	inline ll sigma1() {
		ll res=1;
		for(int i=0; i<5; ++i)res=res*(qpow(P[i],c[i]+1)-1)%mod;
		return res*iP5%mod;
	}
} dis[N];
inline node div(int x) {
	node res;
	for(int i=0; i<5; ++i)
		while(!(x%P[i]))x/=P[i],++res.c[i];
	return res;
}

int n,m,a[N],dep[N],fa[N][18];
vector<int> e[N];
inline void adde(int x,int y) {
	e[x].push_back(y);
}
void dfs(int u) {
	for(int i=0; fa[u][i]; ++i)
		fa[u][i+1]=fa[fa[u][i]][i];
	for(int i=0,sz=e[u].size(); i<sz; ++i) {
		int v=e[u][i];
		if(v==fa[u][0])continue;
		fa[v][0]=u;
		dep[v]=dep[u]+1;
		dis[v]=dis[u]*div(a[v]);
		dfs(v);
	}
}
inline int lca(int x,int y) {
	if(dep[x]<dep[y])swap(x,y);
	int t=dep[x]-dep[y];
	for(int i=0; t; ++i,t>>=1)
		x=t&1?fa[x][i]:x;
	if(x==y)return x;
	for(int i=17; ~i; --i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
inline int dist(int x,int y) {
	int f=lca(x,y);
	return (dis[x]*dis[y]/dis[f]/dis[fa[f][0]]).sigma1();
}

int main() {
	freopen("onlinejudge.in","r",stdin);
	freopen("onlinejudge.out","w",stdout);

	n=read(),m=read();
	for(int i=1; i<=n; ++i)a[i]=read();
	for(int i=1,x,y; i<n; ++i)x=read(),y=read(),adde(x,y),adde(y,x);
	dep[1]=1,dis[1]=div(a[1]),dfs(1);
	while(m--)enter(dist(read(),read()));
	for(int i=1; i<=n; ++i)e[i].clear();
}
