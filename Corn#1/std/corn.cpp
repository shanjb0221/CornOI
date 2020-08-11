#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int mod=20011021;
int n,k;
struct Mat {
	int a[2][2];
	Mat operator *(const Mat &fr)const {
		Mat res;
		for(int i=0; i<2; ++i)
			for(int j=0; j<2; ++j) {
				res.a[i][j]=0;
				for(int k=0; k<2; ++k)res.a[i][j]=(res.a[i][j]+(ll)a[i][k]*fr.a[k][j]%mod)%mod;
			}
		return res;
	}
} st,zy;
Mat mul(Mat a,int k) {
	Mat res;
	for(int i=0; i<2; ++i)
		for(int j=0; j<2; ++j)
			res.a[i][j]=(i==j);
	while(k) {
		if(k&1)res=res*a;
		a=a*a;
		k>>=1;
	}
	return res;
}
int main() {
	freopen("corn.in","r",stdin);
	freopen("corn.out","w",stdout);
	scanf("%d%d",&n,&k);
	if(n==1)printf("%d\n",k),exit(0);
	zy.a[1][0]=1,zy.a[0][1]=k-1,zy.a[1][1]=k-2;
	st.a[0][0]=(ll)k*(k-1)%mod,st.a[0][1]=(ll)st.a[0][0]*(k-2)%mod;
	printf("%d\n",(st*mul(zy,n-2)).a[0][0]);
}
