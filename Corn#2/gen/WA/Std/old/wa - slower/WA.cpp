#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<algorithm>
using namespace std;
namespace IOS {
	template<class T>inline void read(T& x) {
		register char c=getchar(),d=0;
		while(c<'0'||c>'9')d=c,c=getchar();
		x=0;
		while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+c-'0',c=getchar();
		if(d=='-')x=-x;
	}
	template<class T>inline void wt(T x) {
		if(x/10)wt(x/10);
		putchar(x%10+'0');
	}
	template<class T>inline void wtsp(T x) {
		if(x<0)putchar('-'),x=-x;
		wt(x),putchar(' ');
	}
	template<class T>inline void wtln(T x) {
		if(x<0)putchar('-'),x=-x;
		wt(x),putchar('\n');
	}
	template<class T>inline void wtar(T* buf,int n) {
		for(int i=0; i<n-1; ++i)wtsp(buf[i]);
		wtln(buf[n-1]);
	}
}
using namespace IOS;
const int N=310,inf=0x3f3f3f3f;
int n,m;
int x,y,z;
int d[N][N];
int ans;
inline int calc(int x,int dx,int y,int dy) {
	int res=0;
	for(int i=1; i<=n; ++i)
		res=max(res,min(dx+d[i][x],dy+d[i][y]));
	return res;
}
inline int judge(int i,int j,int dis) {
	int L=0,R=dis,l,r,lans,rans,ans=inf;
	while(R-L>2) {
		l=(L*2+R)/3;
		r=(R*2+L)/3;
		lans=calc(i,l,j,dis-l);
		rans=calc(i,r,j,dis-r);
		if(lans<rans)
			ans=min(ans,lans),R=r;
		else
			ans=min(ans,rans),L=l;
	}
	for(int d=L; d<=R; ++d)
		ans=min(ans,calc(i,d,j,dis-d));
	return ans;
}
int main() {
	freopen("WA.in","r",stdin);
	freopen("WA.out","w",stdout);
	read(n),read(m);
	memset(d,inf,sizeof d);
	for(int i=1; i<=m; ++i) {
		read(x),read(y),read(z);
		d[x][y]=d[y][x]=z*2;
	}
	for(int k=1; k<=n; ++k)
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j)
				d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
	for(int i=1; i<=n; ++i)d[i][i]=0;
	ans=inf;
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j) {
			if(d[i][j]==inf)continue;
			ans=min(ans,judge(i,j,d[i][j]));
		}
	cout<<fixed<<setprecision(2)<<ans/2.0<<endl;
	fclose(stdin),fclose(stdout);
}
