#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<algorithm>
#define IO(x) freopen(x".tmp","r",stdin),freopen(x".in","w",stdout)
using namespace std;
typedef unsigned long long ull;
const int N=3e5+10,M=N*3;
int n,m,L,c=0,tot=0,val;
int op[N],v1[N],v2[N],v3[N],vl[M];
char dic[]=" IDRKE";
char type[10];
inline bool isNum(const char& c) {
	return c>='0'&&c<='9';
}
inline int getInt() {
	int r=0;
	char c=getchar(),d=0;
	while(!isNum(c))d=c,c=getchar();
	while(isNum(c))r=(r<<1)+(r<<3)+c-'0',c=getchar();
	return d=='-'?-r:r;
}
inline void putInt(const int& x) {
	if(x/10)putInt(x/10);
	putchar('0'+x%10);
}
inline void putIntSp(int x) {
	if(x<0)x=-x,putchar('-');
	putInt(x),putchar(' ');
}
inline void putIntNl(int x) {
	if(x<0)x=-x,putchar('-');
	putInt(x),putchar('\n');
}
inline int isOp(const char& c) {
	switch(c) {
		case 'I':
			return 1;
		case 'D':
			return 2;
		case 'R':
			return 3;
		case 'K':
			return 4;
		case 'E':
			return 5;
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
inline void push(int x) {
	vl[m++]=x;
}
inline void sort() {
	sort(vl,vl+m,greater<int>()),m=unique(vl,vl+m)-vl;
	while((1<<L)<m)++L;
}
inline int query(int x) {
	return lower_bound(vl,vl+m,x,greater<int>())-vl+1;
}
inline int value(int k) {
	return vl[k-1];
}
struct BIT {
	int d[M],t,l[N],r[N];
	inline BIT():t(0) {};
	inline void update(int p,int v) {
		for(; p<=m; p+=p&-p)d[p]+=v;
	}
	inline int query(int p) {
		static int r;
		for(r=0; p; p-=p&-p)r+=d[p];
		return r;
	}
	inline int at(int p) {
		return query(p)-query(p-1);
	}
	inline void push(int x,int y) {
		l[t]=x,r[t++]=y;
	}
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
	++tot;
}
inline void del(int x) {
	static int y;
	y=query(getRev(x)),x=query(x);
	t[c].update(x,-1),t[c^1].update(y,-1);
	--tot;
}
inline int rnk(int x) {
	return t[c].query(query(x)-1)+1;
}
inline int kth(int k) {
	return value(t[c].find(k));
}
inline void rev() {
	c^=1,t[c].flush();
}
inline ull random() {
	return (ull(rand()))<<48|(ull(rand()))<<32|(ull(rand()))<<16|rand();
}
inline int random(int l,int r) {
	return random()%(r-l+1)+l;
}
inline void init() {
	srand(time(NULL)^*(new char()));
}
int main() {
	IO("score");
	init();
	scanf("%d %s",&n,type);
	printf("%d %s\n",n,type);
	for(int i=0; i<n; ++i) {
		op[i]=getOp();
		if(op[i]!=1)continue;
		v1[i]=getInt();
		push(v1[i]);
		push(v2[i]=getRev(v1[i]));
		push(v3[i]=getRev(v2[i]));
	}
	sort();
	for(int i=0; i<n; ++i) {
		printf("%c",dic[op[i]]);
		if(op[i]==1) {
			ins(v1[i],v2[i],v3[i]);
			printf(" %d",v1[i]);
		}
		if(op[i]==2||op[i]==3) {
			val=kth(random(1,tot));
			printf(" %d",val);
			if(op[i]==2)del(val);
		}
		if(op[i]==4) {
			val=random(1,tot);
			printf(" %d",val);
		}
		if(op[i]==5)rev();
		putchar('\n');
	}
}
