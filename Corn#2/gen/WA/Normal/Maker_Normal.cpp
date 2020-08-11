#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<iostream>
using namespace std;
const int N=310;
int vis[N][N];
int id,n,m,v,x,y,z;
inline int random(int l,int r) {
	return rand()%(r-l+1)+l;
}
char str[100];
const char name[]="WA";

int main() {
	srand(time(0)^getpid());

	sprintf(str,"%s.range",name);
	cout<<"Range File: \""<<str<<"\""<<endl;
	freopen(str,"r",stdin);

	while(cin>>id>>n>>m>>v) {
		sprintf(str,"%s%d.in",name,id);
		freopen(str,"w",stdout);

		memset(vis,0,sizeof vis);
		
		if(n>=100){
			n=random(n*0.95,n);
			if(m!=-1)m=random(m*0.95,m);
		}
		if(m==-1)m=n-1;
		
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
		
		fclose(stdout);
		
		cerr<<"Case "<<id<<" Done!"<<endl;
	}
}
