/*
 * MATH BASICS
 *
 * THEORY:
 *  Sum 1..n            = n(n+1)/2
 *  Sum of squares      = n(n+1)(2n+1)/6
 *  Arithmetic series   = (first + last) * count / 2
 *  Geometric series    = a(r^n - 1)/(r - 1)
 *  Ceil division (a,b > 0): (a + b - 1) / b
 *  Parity: even+even=even, odd+odd=even, odd*odd=odd.
 *  Number of pairs from n items: n(n-1)/2
 *  Permutations of n: n!   nPr = n!/(n-r)!   nCr = n!/(r!(n-r)!)
 *  nCr properties: nCr = nC(n-r),  nCr = (n-1)C(r-1) + (n-1)C(r)
 *  Digits of n: floor(log10(n)) + 1  (or to_string(n).size())
 *  Max safe sizes: 20! fits in long long, 21! does not.
 *
 * WATCH OUT:
 *  - C++ '/' and '%' truncate toward zero. For negative numbers use the
 *    floor_div / pos_mod helpers below.
 *  - Do not use pow() for integers (floating point errors). Write your own.
 *  - sqrtl() can be off by one; fix with the isqrt helper.
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll ceil_div(ll a, ll b) {            // a >= 0, b > 0
    return (a + b - 1) / b;
}

ll floor_div(ll a, ll b) {           // b > 0, works for negative a
    ll q = a / b;
    if (a % b != 0 && a < 0) q--;
    return q;
}

ll pos_mod(ll a, ll m) {             // result always in [0, m)
    return ((a % m) + m) % m;
}

ll isqrt(ll n) {                     // floor(sqrt(n)) exactly
    ll r = (ll)sqrtl((long double)n);
    while (r * r > n) r--;
    while ((r + 1) * (r + 1) <= n) r++;
    return r;
}

bool is_perfect_square(ll n) {
    ll r = isqrt(n);
    return r * r == n;
}

ll ipow(ll b, int e) {               // exact integer power (watch overflow)
    ll r = 1;
    while (e--) r *= b;
    return r;
}

int digit_sum(ll n) {
    int s = 0;
    while (n > 0) { s += n % 10; n /= 10; }
    return s;
}

string to_base(ll n, int base) {     // base 2..10
    if (n == 0) return "0";
    string s;
    while (n > 0) { s += char('0' + n % base); n /= base; }
    reverse(s.begin(), s.end());
    return s;
}

// Pascal triangle nCr for small n (n <= ~60 with long long, or any n with mod)
// C[n][r] table, O(n^2)
vector<vector<ll>> pascal(int n, ll mod = 0) {
    vector<vector<ll>> C(n + 1, vector<ll>(n + 1, 0));
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
            if (mod) C[i][j] %= mod;
        }
    }
    return C;
}

// Bit tricks
//  x & 1            -> is odd
//  x & (x-1)        -> clears lowest set bit
//  x & -x           -> isolates lowest set bit
//  __builtin_popcountll(x) -> number of set bits
//  (x & (x-1)) == 0 && x > 0 -> power of two
//  1LL << k         -> use 1LL, not 1, when k >= 31

int main() {
    cout << ceil_div(7, 2) << "\n";          // 4
    cout << floor_div(-7, 2) << "\n";        // -4
    cout << pos_mod(-7, 5) << "\n";          // 3
    cout << isqrt(99) << "\n";               // 9
    cout << digit_sum(12345) << "\n";        // 15
    cout << to_base(10, 2) << "\n";          // 1010
    auto C = pascal(10);
    cout << C[5][2] << "\n";                 // 10
}
