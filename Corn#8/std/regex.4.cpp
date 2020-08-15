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
struct trie1Node;
struct trie0Node;
struct queryNode {
	trie1Node* to;
	queryNode* nt;
	int id;
	queryNode(trie1Node* t,queryNode* n,int i):to(t),nt(n),id(i) {};
};
template<class T> struct linkNode {
	int lp,rp;
	T* to;
	linkNode* nt;
	linkNode(T* t,linkNode* n,int l,int r):to(t),nt(n),lp(l),rp(r) {};
};
struct trie1Node {
	linkNode<trie1Node>* h;
	int siz,dfn;
	trie1Node():h(NULL),siz(1),dfn(0) {};
};
struct trie0Node {
	linkNode<trie0Node>* h;
	queryNode* fir;
	trie1Node* lnk;
	trie0Node():h(NULL),fir(NULL),lnk(NULL) {};
	inline void addQuery(int i,trie1Node* t) {
		fir=new queryNode(t,fir,i);
	}
	inline void update(int flg) {
		static trie1Node* tmp;
		for(queryNode* i=fir; i; i=i->nt) {
			tmp=i->to;
			ans[i->id]+=flg*b.querySum(tmp->dfn,tmp->dfn+tmp->siz-1);
		}
	}
};
template<class T>struct trie {
	T* root;
	char buf[N];
	int cur;
	inline trie():root(new T()) {};
	inline T* addLink(T* pos,T* dst,char*&s) {
		int old=cur;
		while(*s)buf[cur++]=*(s++);
		pos->h=new linkNode<T>(dst,pos->h,old,cur);
		return dst;
	}
	inline T* findLink(T* pos,char*&s) {
		static int p;
		for(linkNode<T>* i=pos->h; i; i=i->nt) {
			for(p=i->lp; p<i->rp&&buf[p]==*s; ++p)++s;
			if(p==i->rp)return i->to;
			if(p==i->lp)continue;
			pos=new T();
			pos->h=new linkNode<T>(i->to,pos->h,p,i->rp);
			i->to=pos,i->rp=p;
			break;
		}
		return addLink(pos,new T(),s);
	}
	inline T* insert(char* s) {
		T* pos=root;
		while(*s)pos=findLink(pos,s);
		return pos;
	}
	inline T* getLink(T* pos,char*&s) {
		static int p;
		for(linkNode<T>* i=pos->h; i; i=i->nt) {
			for(p=i->lp; p<i->rp&&buf[p]==*s; ++p)++s;
			if(p==i->lp)continue;
			if(p==i->rp||*s=='*')return i->to;
			break;
		}
		return NULL;
	}
	inline T* travel(char* s) {
		T* pos=root;
		while(pos&&*s!='*')pos=getLink(pos,s);
		return pos;
	}
};
trie<trie0Node> T0;
trie<trie1Node> T1;
inline int dfs1(trie1Node* pos) {
	pos->siz=1,pos->dfn=++dfsCount;
	for(linkNode<trie1Node>* i=pos->h; i; i=i->nt)pos->siz+=dfs1(i->to);
	return pos->siz;
}
inline void dfs2(trie0Node* pos) {
	pos->update(-1);
	if(pos->lnk)b.update(pos->lnk->dfn);
	for(linkNode<trie0Node>* i=pos->h; i; i=i->nt)dfs2(i->to);
	pos->update(1);
}
int len;
trie0Node* p0;
trie1Node* p1;
inline void funcS() {
	scanf("%s",s);
	len=strlen(s),p0=T0.insert(s);
	reverse(s,s+len),p1=T1.insert(s);
	p0->lnk=p1;
}
inline void funcT(int i) {
	scanf("%s",s);
	len=strlen(s),p0=T0.travel(s);
	reverse(s,s+len),p1=T1.travel(s);
	if(p0&&p1)p0->addQuery(i,p1);
}
int main() {
	IO("regex");
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)funcS();
	dfs1(T1.root);
	for(int i=1; i<=m; ++i)funcT(i);
	dfs2(T0.root);
	for(int i=1; i<=m; ++i)printf("%d\n",ans[i]);
}
