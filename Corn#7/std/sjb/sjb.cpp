#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
const int N = 110, M = 1 << 14;
const int inf = 0x3f3f3f3f;
struct edge {
    int to, nt;
    inline void init(int t, int n) { to = t, nt = n; }
} e[N << 1];
int n, m, c, x, y, s, t;
int h[N], a[N], w[N], b[N];
int dp[N][M];
inline void adde(int x, int y) {
    e[++c].init(y, h[x]), h[x] = c;
    e[++c].init(x, h[y]), h[y] = c;
}
inline void tryMin(int& x, int y) {
    if (y < x)
        x = y;
}
#define forSet(x, st) for (int x = st, _s = st; x; x = (x - 1) & _s)
#define forBit(x, st) for (int x = st & -st, _s = st; _s; _s ^= x, x = _s & -_s)
inline void upd(int pos, int pnt) {
    b[pnt] |= b[pos];
    forSet(i, b[pnt]) forSet(j, i & b[pos]) tryMin(dp[pnt][i], dp[pnt][j ^ i] + dp[pos][j]);
    for (int i = s; i; --i) forBit(j, i) tryMin(dp[pnt][i ^ j], dp[pnt][i]);
}
inline void dfs(int pos, int pre = 0) {
    memset(dp[pos], 0x3f, t);
    b[pos] = a[pos] ? (1 << (a[pos] - 1)) : 0;
    dp[pos][b[pos]] = w[pos];
    for (int i = h[pos], son; i; i = e[i].nt) {
        son = e[i].to;
        if (son == pre)
            continue;
        dfs(son, pos);
        upd(son, pos);
    }
    dp[pos][0] = 0;
}
int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cin >> n >> m, s = (1 << m) - 1, t = sizeof(int) * (1 << m);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1; i < n; ++i) cin >> x >> y, adde(x, y);
    dfs(1);
    cout << dp[1][s] << endl;
}
