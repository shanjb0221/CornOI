#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,x,cnt,t[60],ans,s,tot;
struct node {
	int f,t,s;
	inline void init(int _f,int _t) {
		f=_f,t=_t,s=(59-f)/t+1;
	}
	inline bool operator<(const node& a)const {
		return a.s==s?f<a.f:a.s<s;
	}
} a[1800];
inline void change(int fir,int itr,int val=1) {
	for(int i=fir; i<60; i+=itr)t[i]+=val,s+=val;
}
inline bool check(int fir,int itr) {
	for(int i=fir; i<60; i+=itr)if(!t[i])return false;
	return true;
}
inline bool dfs(int dep=0,int id=0) {
	//++tot;
	if(s==0)return true;
	for(; id<cnt&&dep+s/a[id].s<=ans; ++id)
		if(a[id].s<=s&&check(a[id].f,a[id].t)) {
			change(a[id].f,a[id].t,-1);
			if(dfs(dep+1,id))return true;
			change(a[id].f,a[id].t);
		}
	return false;
}
int main() {
	while(cin>>n) {
		s=n,cnt=0,tot=0;
		memset(t,0,sizeof t);
		while(n--)cin>>x,t[x]++;
		for(int i=0; i<60; ++i)
			for(int j=i+1; i+j<60; ++j)
				if(check(i,j))a[cnt++].init(i,j);
		sort(a,a+cnt);
		for(ans=0;!dfs();++ans);
		cout<<ans<<endl;
		//cout<<"@ "<<tot<<endl;
	}
}
