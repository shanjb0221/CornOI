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
#define size v1
#define define v2
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
		ans[i]+=flg*b.querySum(a[tmp].define,a[tmp].define+a[tmp].size-1);
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
		a[pos].size=1,a[pos].define=++count;
		for(int i=0; i<26; ++i)
			if(a[pos].c[i])
				a[pos].size+=dfs1(a[pos].c[i]);
		return a[pos].size;
	}
	inline void dfs2(int pos) {
		update(pos,-1);
		if(a[pos].link)b.update(a[a[pos].link].define);
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
	if(a[t0].link){
		fprintf(stderr,"[ERROR] EQUAL STRING!");
		exit(3); 
	} 
	a[t0].link=t1;
}
inline void funcT(int i) {
	scanf("%s",s);
	len=strlen(s),t0=t[0].travel(s);
	reverse(s,s+len),t1=t[1].travel(s);
	if(t0&&t1)a[t0].addQuery(i,t1);
}
int main() {
	//IO("regex");
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)funcS();
	t[1].dfs1(t[1].root);
	for(int i=1; i<=m; ++i)funcT(i);
	t[0].dfs2(t[0].root);
	for(int i=1; i<=m; ++i)printf("%d\n",ans[i]);
}
