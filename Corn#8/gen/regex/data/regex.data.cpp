#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <set>
using namespace std;
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

typedef pair<int, int> pii;
const int L = 100, N =5e4+10;
int typ, len, str, dic;
int n, m;
char d[N][L];
inline void putStr(int i,int l,int r) {
	for(int j=l; j<=r; ++j)putchar(d[i][j]);
}
inline void rndStr(int l,int r) {
	for(int j=l; j<=r; ++j)putchar(random('a',typ&2?'z':'d'));
}
inline void genS() {
	static int i,l,r;
	i=random(1,dic);
	l=random(1,len-len/2);
	r=random(1,len-len/2);
	if(l>r)l^=r^=l^=r;
	r+=len/2; 
	putStr(i,1,l-1),rndStr(l,r),putStr(i,r+1,len),putchar('\n');
}
inline void genT() {
	static int i,l,r;
	i=random(1,dic);
	if(typ&1) {
		if(random(0,1)) {
			l=random(1,len/2);
			putStr(i,1,l-1),putchar('*');
		} else {
			r=random(len/2+1,len);
			putchar('*'),putStr(i,r+1,len);
		}
	} else {
		l=random(1,len/2);
		r=random(1,len/2);
		if(l>r)l^=r^=l^=r;
		r+=len/2;
		putStr(i,1,l-1),putchar('*'),putStr(i,r+1,len);
	}
	putchar('\n');
}
int main() {
	init();
	scanf("%d%d%d%d", &typ, &len, &str, &dic);
	n=str/len,m=n<<1;
	printf("%d %d\n",n,m);
	for(int i=1; i<=dic; ++i)
		for(int j=1; j<=len; ++j)
			d[i][j]=random('a',typ&2?'z':'d');
	for(int i=1; i<=n; ++i)genS();
	for(int i=1; i<=m; ++i)genT();
	return 0;
}
