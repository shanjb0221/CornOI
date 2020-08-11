#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

const char name[]="arrange";

int TotCase;

const int N=1e5+10;
const int M=998244353;
typedef long long ll;
int fac[N];
int T,n,m,a,b;
ll ans;
ll Pow(ll x,int t){
	ll r=1;
	while(t){
		if(t&1)r=r*x%M;
		x=x*x%M,t>>=1;
	}
	return r;
}
ll A(int n,int m){
	return fac[n]*Pow(fac[n-m],M-2)%M;
}

inline void IO(int id) {
	char s[100];
	sprintf(s,"%s%d.in",name,id);
	freopen(s,"r",stdin);
	sprintf(s,"%s%d.ans",name,id);
	freopen(s,"w",stdout);
}

int main() {
	freopen("list.ini","r",stdin);

	cin>>TotCase;
	
	fclose(stdin);

	for(int Case=1; Case<=TotCase; ++Case) {

		IO(Case);


		fac[0]=1;
		for(int i=1; i<N; ++i)fac[i]=(ll)fac[i-1]*i%M;
		cin>>T;
		while(T--) {
			cin>>n>>m>>a>>b;
			ans=((ll)(n-1)*(n-a-b)+(ll)a*b)%M;
			ans=(ans*A(n-2,m-2))%M;
			cout<<ans<<endl;
		}

		fclose(stdout),fclose(stdin);

		cerr<<"Case "<<Case<<" Done!"<<endl;

	}

}
