#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<algorithm>
using namespace std;
template<class T>inline void read(T& x) {
	register char c=getchar(),d=0;
	while(c<'0'||c>'9')d=c,c=getchar();
	x=0;
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+c-'0',c=getchar();
	if(d=='-')x=-x;
}
const int N=310,M=90010,inf=0x3f3f3f3f;
int n,m;
int x[M],y[M],z[M];
int d[N][N];
int ans;
std::pair<int,int> b[N];
inline bool check(int dis,int lim) {
	for(int i=1,R=0; i<=n; ++i) {
		if(b[i].first+lim>=R)return 1;
		R=max(R,b[i].second-lim);
		if(R>dis)return 0;
	}
	return 1;
}
inline void judge(int x,int y,int dis) {
	for(int i=1; i<=n; ++i) {
		if(min(d[i][x],d[i][y])>=ans)return;
		b[i]=std::make_pair(-d[i][x],dis+d[i][y]);
	}
	std::sort(b+1,b+n+1);
	if(!check(dis,ans))return;
	int L=0,R=ans-1,mid;
	while(L<=R) {
		mid=(L+R)>>1;
		if(check(dis,mid))ans=mid,R=mid-1;
		else L=mid+1;
	}
}
int main() {
	freopen("WA.in","r",stdin);
	freopen("WA.out","w",stdout);
	read(n),read(m);
	memset(d,inf,sizeof d);
	for(int i=1; i<=m; ++i) {
		read(x[i]),read(y[i]),read(z[i]);
		d[x[i]][y[i]]=d[y[i]][x[i]]=(z[i]<<=1);
	}
	for(int i=1; i<=n; ++i)d[i][i]=0;
	for(int k=1; k<=n; ++k)
		for(int i=1; i<=n; ++i)
			for(int j=i+1; j<=n; ++j)
				d[j][i]=d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
	ans=inf;
	for(int i=1; i<=m; ++i)
		judge(x[i],y[i],z[i]);
	cout<<fixed<<setprecision(2)<<ans/2.0<<endl;
	fclose(stdin),fclose(stdout);
}
