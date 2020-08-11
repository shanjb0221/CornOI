#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

inline int random(int l,int r) {
	return rand()*rand()%(r-l+1)+l;
}
inline void write_random(int lg) {
	putchar(random('1','9'));
	for(int i=1; i<lg; ++i)putchar(random('0','9'));
}

const char name[]="arrange";

int TotCase,T,N,op,n,m,a,b;

inline void O(int id) {
	char s[100];
	sprintf(s,"%s%d.in",name,id);
	freopen(s,"w",stdout);
}

int main() {
	freopen("list.ini","r",stdin);
	srand(time(NULL)),srand(rand());

	cin>>TotCase;

	for(int Case=1; Case<=TotCase; ++Case) {

		cin>>op>>N>>T;

		O(Case);

		N=random(max(1,int(N*0.9)),N);
		T=random(max(1,int(T*0.9)),T);
		
		cout<<T<<endl;
		
		while(T--){
			n=random(max(1,int(0.5*N)),N);
			m=random(max(1,int(0.5*n)),n);
			a=random(0,n);
			b=random(0,n-a);
			if(op==1)m=n;
			if(op==2)a=b=0;
			if(op==3)a=0;
			cout<<n<<" "<<m<<" "<<a<<" "<<b<<endl;	
		}

		fclose(stdout);
		
		cerr<<"Case "<<Case<<" Done!"<<endl;

	}

}
