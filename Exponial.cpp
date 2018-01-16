#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <regex>

using namespace std;

#define fr          first
#define sc          second
#define mp          make_pair
#define pub         push_back
#define all(x)      (x).begin(),(x).end()
#define sz(x)       int((x).size())
#define F(i,a,b)    for (int i = a; i < b; i++)
#define R(i,a,b)    for (int i = a - 1; i >= b; i--)

typedef long long           LL;
typedef long double         LD;
typedef unsigned long long  ULL;
typedef unsigned int        UI;

const int   N = 10005;
const int   SL = 200005;
const LL    Mod = 1000000007;
const LL    INF = 1000000000;
const LD    Eps = 1e-6;
const LD    PI = acos(-1.0);
const LD    E = 2.7182818284590452353602874713527;
const int   dir = 4;
const int   prime = 31;

LL gcd(LL a, LL b) { 
    return a > b ? gcd(b, a) : a != 0 ? gcd(b%a, a) : b;
}
LL lcm(LL a, LL b) { return a / gcd(a, b) * b; }
LL length(LL n) { return n < 10 ? 1 : 1 + length(n / 10); }
void File() { freopen(".in", "r", stdin); freopen(".out", "w", stdout); }
template<class A, class B>  int minn(A a, B b) { return a < b ? a : b; }
template<class A, class B>  int maxx(A a, B b) { return a > b ? a : b; }

LL Phi(LL n) {
    LL result = n;
    for (LL i = 2; i * i <= n; ++i)
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    if (n > 1)
        result -= result / n;
    return result;
}

LL BinPow(LL a, LL b, LL mod) {
    if (b == 0) return 1 % mod;
    LL p = BinPow(a, b >> 1, mod);
    p = (p * p) % mod;
    if (b & 1)  p *= a;
    return p % mod;
}

LL Shtrix(LL n, LL m) {
    while (gcd(n, m) != 1)
        m /= gcd(n, m);
    return m;
}

LL Ans(LL n, LL m) {
    if (n == 0 || m == 1)   return 0;
    if (gcd(n, m) == 1)     return BinPow(n, Ans(n - 1, Phi(m)), m);
    LL _m = Shtrix(n, m), m_, x, y;
    m_ = m / _m;
    x = BinPow(n, Ans(n - 1, Phi(_m)), _m);
    if (n >= 5) y = 0;
    else if (n == 4)    y = BinPow(n, 9, m_);
    else if (n == 3)    y = BinPow(n, 2, m_);
    else if (n == 2)    y = 2 % m_;
    else y = 1 % m_;
    return (((x * m_) % m * BinPow(m_, Phi(_m) - 1, _m)) % m +((y * _m) % m *  BinPow(_m, Phi(m_) - 1, m_)) % m) % m;
}

int main()
{
    LL n, m;
    while (cin >> n >> m) {
        cout << Ans(n, m) << endl;
    }
    return 0;
}
