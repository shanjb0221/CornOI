#include<cmath>
#include<ctime> 
#include<cstdio>
#include<bits/stdc++.h> 
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define IO(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
using std::reverse;
using std::max;
typedef unsigned long long ull;
inline ull random() {
	return (ull(rand())) << 48 | (ull(rand())) << 32 | (ull(rand())) << 16 |
	       rand();
}
inline int random(int l, int r) {
	return random() % (r - l + 1) + l;
}
inline void init() {
	srand(time(NULL) ^ (long long)(int*)(new char()));
}

const int N=1e5+10;
int t,n,m,x,y,z,v,s;
int dis[N];
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
	for(int i=h[pos]; i; i=e[i].nt) {
		int son=e[i].to;
		if(son==pnt)continue;
		dis[son]=dis[pos]+e[i].vl;
		dfs(son,pos);
	}
}
int main() {
	init();
	scanf("%d%d%d%d",&t,&n,&m,&v),s=sqrt(n);
	printf("%d %d\n",n,m);
	for(int i=1; i<n; ++i){
		y=i+1,z=random(1,v);
		if(t==0)x=random(1,i);
		if(t==1)x=i;
		if(t==2)x=y>>1;
		if(t==3)x=random(max(1,i-s),i);
		printf("%d %d %d\n",x,y,z);
		adde(x,y,z);
	}
	dfs(1);
	for(int i=1; i<=m; ++i) {
		x=random(2,n);
		y=random(0,(dis[x]+v)<<1);
		if(y>=1000000000)fprintf(stderr,"[ERROR] TOO LARGE VALUE -------------------");
		printf("%d %d\n",x,y);
	}
}
