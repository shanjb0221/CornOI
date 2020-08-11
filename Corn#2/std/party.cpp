#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using std::sort;
typedef std::priority_queue<int,std::vector<int>,std::greater<int> > pq;
namespace Fun {
	template<class T>
	inline const T& min(const T& x,const T& y) {
		return x<y?x:y;
	}
	template<class T>
	inline const T& max(const T& x,const T& y) {
		return x<y?y:x;
	}
} // namespace Fun
using namespace Fun;
namespace IOS {
	template<class T>
	inline void read(T& x) {
		register char c=getchar(),d=0;
		while(c>'9'||c<'0')d=c,c=getchar();
		x=0;
		while(c<='9'&&c>='0')x=(x<<1)+(x<<3)+c-'0',c=getchar();
		if(d=='-')x=-x;
	}
	template<class T>
	inline void wt(T x) {
		if(x/10)wt(x/10);
		putchar(x%10+'0');
	}
	template<class T>
	inline void wtln(T x) {
		if(x<0)putchar('-'),x=-x;
		wt(x),putchar('\n');
	}
	template<class T>
	inline void wtsp(T x) {
		if(x<0)putchar('-'),x=-x;
		wt(x),putchar(' ');
	}
} // namespace IOS
using namespace IOS;
const int N=2e5+10;
int n,m,x,T,k;
struct edge {
	int x,y,p;
	inline void init() {
		read(x),read(y),read(p);
	}
	inline bool operator<(const edge& e)const {
		return p>e.p;
	}
} e[N];
int f[N],s[N];
int sum[N],ans[N];
pq q[N];
struct node {
	int p,x,i;
	inline void init(int id) {
		read(x),read(p),i=id;
	}
	inline bool operator<(const node& e)const {
		return p>e.p;
	}
} g[N];
inline int fnd(int x) {
	return x==f[x]?x:f[x]=fnd(f[x]);
}
inline void merge(int x,int y) {
	x=fnd(x),y=fnd(y);
	if(x==y)return;
	if(s[x]>s[y])x^=y^=x^=y;
	f[x]=y,s[y]+=s[x],sum[y]+=sum[x];
	while(!q[x].empty())q[y].push(q[x].top()),q[x].pop();
	while(s[y]>k)sum[y]-=q[y].top(),q[y].pop(),--s[y];
}
int main() {
	freopen("party.in","r",stdin);
	freopen("party.out","w",stdout);
	read(n),read(m);
	for(int i=1; i<=n; ++i) {
		f[i]=i,s[i]=1;
		read(x),sum[i]=x;
		q[i].push(x);
	}
	for(int i=1; i<=m; ++i)e[i].init();
	read(T),read(k);
	for(int i=1; i<=T; ++i)g[i].init(i);
	sort(e+1,e+m+1);
	sort(g+1,g+T+1);
	for(int i=1,j=1; i<=T; ++i) {
		while(j<=m&&e[j].p>=g[i].p)
			merge(e[j].x,e[j].y),++j;
		ans[g[i].i]=sum[fnd(g[i].x)];
	}
	for(int i=1; i<=T; ++i)wtln(ans[i]);
}
