#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<iostream>
using namespace std;
const int N=310;
int vis[N][N];
int n,m,x,y,z,v;
inline int random(int l,int r) {
	return rand()%(r-l+1)+l;
}
int main() {
	srand(time(0)^getpid());
	freopen("Hack.range","r",stdin);
	freopen("WA.in","w",stdout);
	cin>>n>>m>>v;
	cout<<n<<" "<<m<<endl;
	for(int i=1; i<n; ++i) {
		x=i+1,y=random(1,i);
		z=random(1,v);
		vis[x][y]=vis[y][x]=1;
		cout<<x<<" "<<y<<" "<<z<<endl;
	}
	for(int i=n; i<=m; ++i) {
		do x=random(1,n),y=random(1,n);
		while(x==y||vis[x][y]);
		vis[x][y]=vis[y][x]=1;
		z=random(1,v);
		cout<<x<<" "<<y<<" "<<z<<endl;
	}
	fclose(stdout),fclose(stdin);
}
