#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define IO(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
using std::reverse;
const int N=1e6+5;
int n,m;
char s[N];
int ans[N];
int trieTotal,linkTotal,dfsCount;
struct BIT {
	int d[N];
	inline void update(int p) {
		for(; p<=dfsCount; p+=p&-p)++d[p];
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
	int to,nt;
	inline void set(int t,int n) {
		to=t,nt=n;
	}
} q[N];
struct linkNode {
	char ch;
	int to,nt;
	inline void set(int t,int n,char c) {
		to=t,nt=n,ch=c;
	}
} l[N<<1];
struct trieNode {
	int h,v1,v2;
#define siz v1
#define dfn v2
#define lnk v1
#define fir v2
	inline void addQuery(int i,int t) {
		q[i].set(t,fir),fir=i;
	}
} a[N<<1];
inline void update(int pos,int flg=1) {
	static int tmp;
	for(int i=a[pos].fir; i; i=q[i].nt) {
		tmp=q[i].to;
		ans[i]+=flg*b.querySum(a[tmp].dfn,a[tmp].dfn+a[tmp].siz-1);
	}
}
inline int newTrieNode() {
	return ++trieTotal;
}
inline int newLinkNode() {
	return ++linkTotal;
}
inline int findLink(int pos,char v) {
	for(int i=a[pos].h; i; i=l[i].nt)
		if(l[i].ch==v)return l[i].to;
	return 0;
}
inline int addLink(int src,int dst,char val) {
	int tmp=newLinkNode();
	l[tmp].set(dst,a[src].h,val),a[src].h=tmp;
	return dst;
}
struct trie {
	int root;
	inline trie():root(newTrieNode()) {};
	inline int insert(char* s) {
		int pos=root,tmp;
		for(; *s; ++s) {
			tmp=findLink(pos,*s);
			if(tmp)pos=tmp;
			else pos=addLink(pos,newTrieNode(),*s);
		}
		return pos;
	}
	inline int travel(char* s) {
		int pos=root;
		for(; *s!='*'; ++s) {
			pos=findLink(pos,*s);
			if(!pos)return 0;
		}
		return pos;
	}
} t[2];
inline int dfs1(int pos) {
	a[pos].siz=1,a[pos].dfn=++dfsCount;
	for(int i=a[pos].h; i; i=l[i].nt)a[pos].siz+=dfs1(l[i].to);
	return a[pos].siz;
}
inline void dfs2(int pos) {
	update(pos,-1);
	if(a[pos].lnk)b.update(a[a[pos].lnk].dfn);
	for(int i=a[pos].h; i; i=l[i].nt)dfs2(l[i].to);
	update(pos,1);
}
int len,t0,t1;
inline void funcS() {
	scanf("%s",s);
	len=strlen(s),t0=t[0].insert(s);
	reverse(s,s+len),t1=t[1].insert(s);
	a[t0].lnk=t1;
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
	dfs1(t[1].root);
	for(int i=1; i<=m; ++i)funcT(i);
	dfs2(t[0].root);
	for(int i=1; i<=m; ++i)printf("%d\n",ans[i]);
}
