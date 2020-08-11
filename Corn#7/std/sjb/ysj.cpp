#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10, L = 19;
int T, n, m;
int prm[N], tot, phi[N];
ll sum[N];
int buf[N][L], lg2[N];
char vis[N], tag[N][L];
inline void init() {
    sum[1] = vis[1] = phi[1] = 1;
    for (int i = 2, k, p; i < N; ++i) {
        lg2[i] = lg2[i >> 1] + 1;
        if (!vis[i])
            prm[++tot] = i, phi[i] = i - 1;
        for (int j = 1; j <= tot && (k = i * (p = prm[j])) < N; ++j) {
            vis[k] = 1;
            if (i % p)
                phi[k] = phi[i] * phi[p];
            else {
                phi[k] = phi[i] * p;
                break;
            }
        }
        sum[i] = sum[i - 1] + phi[i];
    }
}
inline int mult(ll x, int y) { return x * y % m; }
inline int getm(int p, int l) {
    if (l == 0)
        return p;
    if (tag[p][l])
        return buf[p][l];
    tag[p][l] = 1;
    return buf[p][l] = mult(getm(p, l - 1), getm(p + (1 << (l - 1)), l - 1));
}
inline int find(int l, int r) {
    int res = 1, log = lg2[r - l + 1];
    while (l <= r) {
        if (log == lg2[r - l + 1])
            res = mult(res, getm(l, log)), l += 1 << log;
        --log;
    }
    return res;
}
inline int qpow(int x, ll t) {
    int r = 1;
    while (t) {
        if (t & 1)
            r = mult(r, x);
        x = mult(x, x), t >>= 1;
    }
    return r;
}
inline int calc(int n) {
    int ans = 1;
    for (int i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        ans = mult(ans, qpow(find(i, j), 2 * sum[n / i] - 1));
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T >> m, init();
    while (T--) cin >> n, cout << calc(n) << endl;
}
