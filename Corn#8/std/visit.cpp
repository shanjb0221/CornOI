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
