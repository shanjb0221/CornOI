#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define IO(x) freopen(x".rule","r",stdin),freopen(x".tmp","w",stdout)
using namespace std;
typedef unsigned long long ull;
int spe,n,tot;
char type[10];
char op[]=" IDRKE";
inline ull random() {
	return (ull(rand()))<<48|(ull(rand()))<<32|(ull(rand()))<<16|rand();
}
inline int random(int l,int r) {
	return random()%(r-l+1)+l;
}
inline bool checkOp(int x) {
	if(!x)return false;
	if(type[0]=='A'&&x==5)return false;
	if(tot==0&&x!=1)return false;
	return true;
}
inline int getOp2() {
	static int r;
	do {
		r=random(-1,6);
		if(r<=0)r=1;
		if(r>=6)r=spe?spe:1;
	} while(!checkOp(r));
	if(r==2)--tot;
	if(r==1)++tot;
	return r;
}
inline int getOp11() {
	static int r;
	do {
		r=random(-1,3);
		if(r<=0)r=1;
		if(r>=3)r=5;
	} while(!checkOp(r));
	if(r==2)--tot;
	if(r==1)++tot;
	return r;
}
inline int getOp12() {
	static int r;
	do {
		r=random(3,6);
		if(r>=6)r=spe;
	} while(!checkOp(r));
	return r;
}
inline int getNum(){
	if(type[0]=='B')return random(1,n-1);
	return random(1,1e9);
}
inline void init() {
	tot=0,srand(time(NULL)^*(new char()));
}
int main() {
	IO("score");
	init();
	scanf("%d%s%d",&spe,type,&n);
	printf("%d %s\n",n,type);
	int i=0,x,y;
	if(type[1]=='2') {
		for(; i<n; ++i) {
			x=getOp2();
			printf("%c",op[x]);
			if(x==1)printf(" %d",getNum());
			putchar('\n');
		}
	}else if(type[1]=='1') {
		for(y=n>>1; i<y; ++i) {
			x=getOp11();
			printf("%c",op[x]);
			if(x==1)printf(" %d",getNum());
			putchar('\n');
		}
		for(;i<n;++i){
			x=getOp12();
			printf("%c",op[x]);
			putchar('\n');
		}
	}else {
		for(y=n/3; i<y; ++i) {
			x=1,++tot;
			printf("%c",op[x]);
			if(x==1)printf(" %d",getNum());
			putchar('\n');
		}
		for(;i<n;++i){
			x=getOp12();
			printf("%c",op[x]);
			putchar('\n');
		}
	}
}
