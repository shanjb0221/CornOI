#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read(){
	register int res=0;
	register char c=getchar(),f=1;
	while(c<48||c>57){if(c=='-')f=0;c=getchar();}
	while(c>=48&&c<=57)res=(res<<3)+(res<<1)+(c&15),c=getchar();
	return f?res:-res;
}
inline char reac(){
	register char c=getchar();
	while(c<65||c>90)c=getchar();
	return c;
}
inline void write(int x){
	register char c[21],len=0;
	if(!x)return putchar('0'),void();
	if(x<0)x=-x,putchar('-');
	while(x)c[++len]=x%10,x/=10;
	while(len)putchar(c[len--]+48);
}
#define space(x) write(x),putchar(' ')
#define enter(x) write(x),putchar('\n')

const int N=3e5+10;
int tot=0,buc[N*3];
inline int id(int x){
	return lower_bound(buc+1,buc+tot+1,-x)-buc;
}
inline int val(int x){
	return -buc[x];
}
struct BIT{
	int n,lg,c[N];
	inline void upd(int x,int y){
		for(;x<=n;x+=x&-x)c[x]+=y;
	}
	inline void init(int m){
		n=m;
		while((1<<lg)<n)++lg;
	}
	inline int sum(int x){
		int res=0;
		for(;x;x-=x&-x)res+=c[x];
		return res;
	}
	
	inline void ins(int x){upd(id(x),1);}
	inline void del(int x){upd(id(x),-1);}
	inline int rnk(int x){return sum(id(x));}
	inline int kth(int k){
		int res=0;
		for(int i=lg;~i;--i)
			if((res|(1<<i))<=n&&c[res|(1<<i)]<k)
				res|=1<<i,k-=c[res];
		return val(res+1);
	}
}T[2];

char tmp[20];
inline int rev(int x){
	sprintf(tmp,"%d",x);
	int l=strlen(tmp),res=0;
	for(int i=l-1;~i;--i)res=res*10+tmp[i]-48;
	return res;
}
int n,x,r,opx[N],opr[N],oprr[N];
char opt[N];
int sta[N],top=0;
int main(){
	//freopen("score.in","r",stdin);
	//freopen("score.out","w",stdout);
	
	n=read(),scanf("%s",tmp);
	for(int i=1;i<=n;++i){
		opt[i]=reac();
		if(opt[i]!='E'){
			x=opx[i]=read();
			if(opt[i]=='I'||opt[i]=='D')r=opr[i]=rev(x);
			if(opt[i]=='I'){
				buc[++tot]=-x,buc[++tot]=-r;
				if(!(x%10))oprr[i]=rev(r),buc[++tot]=-oprr[i];
			}
		}
	}
	sort(buc+1,buc+tot+1);
	tot=unique(buc+1,buc+tot+1)-buc-1;
	T[0].init(tot),T[1].init(tot);
	
	bool o=0;
	for(int i=1;i<=n;++i){
		int x=opx[i],r=opr[i];
		if(opt[i]=='I'){
			T[o].ins(x),T[o^1].ins(r);
			if(!(opx[i]%10))sta[++top]=i;
		}
		else if(opt[i]=='D')
			T[o].del(x),T[o^1].del(r);
		else if(opt[i]=='R')
			enter(T[o].rnk(opx[i]));
		else if(opt[i]=='K')
			enter(T[o].kth(opx[i]));
		else if(opt[i]=='E'){
			while(top)T[o].del(opx[sta[top]]),T[o].ins(oprr[sta[top]]),--top;
			o^=1;
		}
	}
}
