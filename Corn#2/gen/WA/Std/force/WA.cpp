#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=310,M=90010,inf=0x3f3f3f3f;
int n,m;
int d[N][N];
struct edge{
	int x,y,z;
	inline void init(){
		scanf("%d %d %d\n",&x,&y,&z),z<<=1;
		d[x][y]=d[y][x]=z;
	}
	inline bool operator<(const edge& e)const{
		return z<e.z;
	}
	inline bool poss(){
		return d[x][y]==z;	
	}
}e[M];
int ans;
inline int check(int x,int y,int dx,int dy) {
	int res=0;
	for(int i=1;i<=n;++i)
		res=max(res,min(d[x][i]+dx,d[y][i]+dy));
	return res;
}
inline void judge(int x,int y,int dis) {
	if(dis>=2*ans)return;
	for(int i=1;i<=n;++i)if(min(d[i][x],d[i][y])>=ans)return;
	int i=0;
	for(;i<=dis&&i<ans;++i)
		ans=min(ans,check(x,y,i,dis-i));
	i=max(i,dis-ans+1);
	for(;i<=dis;++i)
		ans=min(ans,check(x,y,i,dis-i));
}
int main() {
	freopen("WA.in","r",stdin);
	freopen("WA.out","w",stdout);
	scanf("%d %d",&n,&m);
	memset(d,inf,sizeof d);
	for(int i=1; i<=m; ++i)e[i].init();
	for(int i=1; i<=n; ++i)d[i][i]=0;
	for(int k=1; k<=n; ++k)
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j)
				d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
	ans=inf;
	std::sort(e+1,e+m+1);
	for(int i=1; i<=m; ++i)
		if(e[i].poss())judge(e[i].x,e[i].y,e[i].z);
	printf("%.2lf\n",ans/2.0);
	fclose(stdin),fclose(stdout);
}
