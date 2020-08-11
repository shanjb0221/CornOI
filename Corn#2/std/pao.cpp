#include<cstdio>
#include<cstring>
namespace Fun {
	template<class T>
	inline const T& min(const T& x,const T& y) {
		return x<y?x:y;
	}
	template<class T>
	inline const T& max(const T& x,const T& y) {
		return x<y?y:x;
	}
} // namespace Fun
using namespace Fun;
namespace IOS {
	template<class T>
	inline void read(T& x) {
		register char c=getchar(),d=0;
		while(c>'9'||c<'0')d=c,c=getchar();
		x=0;
		while(c<='9'&&c>='0')x=(x<<1)+(x<<3)+c-'0',c=getchar();
		if(d=='-')x=-x;
	}
	template<class T>
	inline void wt(T x) {
		if(x/10)wt(x/10);
		putchar(x%10+'0');
	}
	template<class T>
	inline void wtln(T x) {
		if(x<0)putchar('-'),x=-x;
		wt(x),putchar('\n');
	}
	template<class T>
	inline void wtsp(T x) {
		if(x<0)putchar('-'),x=-x;
		wt(x),putchar(' ');
	}
} // namespace IOS
using namespace IOS;
typedef long long ll;
const int N=100;
int vmax[N][N];
int vmin[N][N];
ll mmax[N][N];
ll mmin[N][N];
int a[N];
int T,n;
ll ans;
ll qmin(int,int);
ll qmax(int,int);
ll qmax(int l,int r) {
	if(l==r)return a[l];
	if(vmax[l][r])return mmax[l][r];
	ll tmp=qmax(l,l)+qmax(l+1,r);
	for(int i=l+1; i<r; ++i)tmp=max(tmp,qmax(l,i)+qmax(i+1,r));
	for(int i=l; i<r; ++i) {
		for(int j=i+1; j<r; ++j) {
			tmp=max(tmp,qmax(l,i)*qmax(j+1,r)-qmin(i+1,j));
			tmp=max(tmp,qmin(l,i)*qmin(j+1,r)-qmin(i+1,j));
		}
	}
	vmax[l][r]=1;
	return mmax[l][r]=tmp;
}
ll qmin(int l,int r) {
	if(l==r)return a[l];
	if(vmin[l][r])return mmin[l][r];
	ll tmp=qmin(l,l)+qmin(l+1,r);
	for(int i=l+1; i<r; ++i)tmp=min(tmp,qmin(l,i)+qmin(i+1,r));
	for(int i=l; i<r; ++i) {
		for(int j=i+1; j<r; ++j) {
			tmp=min(tmp,qmin(l,i)*qmax(j+1,r)-qmax(i+1,j));
			tmp=min(tmp,qmax(l,i)*qmin(j+1,r)-qmax(i+1,j));
		}
	}
	vmin[l][r]=1;
	return mmin[l][r]=tmp;
}
int main() {
	freopen("pao.in","r",stdin);
	freopen("pao.out","w",stdout);
	read(T);
	while(T--) {
		read(n);
		for(int i=1; i<=n; ++i)read(a[i]),a[i+n]=a[i];
		memset(vmax,0,sizeof vmax);
		memset(vmin,0,sizeof vmin);
		ans=qmax(1,n);
		for(int i=2; i<=n; ++i)ans=max(ans,qmax(i,i+n-1));
		wtln(ans);
	}
}
