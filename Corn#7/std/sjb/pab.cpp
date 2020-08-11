#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
int T;
ll a, b, c, x, y, g;
ll a0, b0, c0;
ll x0, y0, x1, y1, x2, y2;
inline ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll r = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return r;
}
inline ll mod(ll x, ll m) { return (x % m + m) % m; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T;
    while (T--) {
        cin >> a >> b >> c;
        g = exgcd(a, b, x, y);
        if (c % g) {
            cout << -1 << '\n';
            continue;
        }
        a0 = a / g, b0 = b / g, c0 = c / g;
        x0 = x * c0, y0 = y * c0;
        x1 = mod(x0, b0), y1 = (c - a * x1) / b;
        y2 = mod(y0, a0), x2 = (c - b * y2) / a;
        if (y1 < 0 || x2 < 0) {
            cout << -1 << '\n';
            continue;
        }
        cout << x1 << ' ' << y1 << ' ' << y2 << ' ' << x2 << '\n';
    }
}
