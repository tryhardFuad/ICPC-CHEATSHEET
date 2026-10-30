/*
 * NUMBER THEORY
 * (CP-Algorithms has full theory for all of this: sieve, euclid, binary
 *  exponentiation, modular inverse.)
 *
 * THEORY:
 *  gcd(a,b): Euclid, gcd(a,b) = gcd(b, a%b). O(log).
 *  lcm(a,b) = a / gcd(a,b) * b   (divide first to avoid overflow)
 *
 *  Modular arithmetic:
 *    (a+b)%m = ((a%m)+(b%m))%m
 *    (a*b)%m = ((a%m)*(b%m))%m
 *    (a-b)%m = ((a%m)-(b%m)+m)%m
 *    Division is NOT direct. Multiply by the modular inverse.
 *
 *  Fast power: a^e in O(log e) by squaring.
 *
 *  Modular inverse of a mod m:
 *    - m prime:   a^(m-2) mod m   (Fermat's little theorem), a not multiple of m
 *    - any m:     extended gcd, exists only if gcd(a,m) = 1
 *
 *  Prime facts:
 *    - n is composite => it has a divisor <= sqrt(n). Trial division is O(sqrt n).
 *    - Sieve of Eratosthenes: all primes up to N in O(N log log N).
 *    - Number of divisors of n <= ~1344 for n <= 1e9, ~103680 for n <= 1e18.
 *
 *  Euler phi(n) = count of 1..n coprime to n
 *               = n * prod(1 - 1/p) over distinct primes p of n.
 *
 *  Linear Diophantine ax+by=c has solutions iff gcd(a,b) | c.
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

ll gcd_(ll a, ll b) { return b == 0 ? a : gcd_(b, a % b); }   // or std::__gcd
ll lcm_(ll a, ll b) { return a / gcd_(a, b) * b; }

// a^e mod m. Safe when m < ~3e9 (so products fit in long long)
ll power(ll b, ll e, ll m = MOD) {
    ll r = 1 % m;
    b %= m;
    while (e > 0) {
        if (e & 1) r = r * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return r;
}

// Fermat inverse, m must be prime
ll inv_prime(ll a, ll m = MOD) { return power(a, m - 2, m); }

// Extended gcd: finds x, y with a*x + b*y = gcd(a,b). returns gcd.
ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Inverse for any m when gcd(a,m)=1. returns -1 if none.
ll inv_any(ll a, ll m) {
    ll x, y;
    ll g = extgcd(((a % m) + m) % m, m, x, y);
    if (g != 1) return -1;
    return ((x % m) + m) % m;
}

bool is_prime(ll n) {                     // O(sqrt n)
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

// Sieve with smallest prime factor. Gives primes AND fast factorization.
// Call sieve() once at the start of main. Change N if you need a bigger range.
const int N = 1000000;
int spf[N + 1];
vector<int> primes;

void sieve() {
    for (int i = 2; i <= N; i++) {
        if (spf[i] == 0) { spf[i] = i; primes.push_back(i); }
        for (int p : primes) {
            if (p > spf[i] || (ll)i * p > N) break;
            spf[i * p] = p;
        }
    }
}

// Factorize using spf, needs sieve() first. O(log n). n <= N
vector<pair<int,int>> factorize_spf(int n) {
    vector<pair<int,int>> f;
    while (n > 1) {
        int p = spf[n], c = 0;
        while (n % p == 0) { n /= p; c++; }
        f.push_back({p, c});
    }
    return f;
}

// Factorize by trial division. O(sqrt n), n up to ~1e12 fine.
vector<pair<ll,int>> factorize(ll n) {
    vector<pair<ll,int>> f;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int c = 0;
            while (n % p == 0) { n /= p; c++; }
            f.push_back({p, c});
        }
    }
    if (n > 1) f.push_back({n, 1});
    return f;
}

// All divisors of n, sorted. O(sqrt n)
vector<ll> divisors(ll n) {
    vector<ll> d;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            d.push_back(i);
            if (i != n / i) d.push_back(n / i);
        }
    }
    sort(d.begin(), d.end());
    return d;
}

ll phi(ll n) {                            // Euler totient, O(sqrt n)
    ll r = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            r -= r / p;
        }
    }
    if (n > 1) r -= r / n;
    return r;
}

// nCr mod prime with precomputed factorials. O(n) precompute, O(1) query.
// Call precompute_fact() once at the start of main.
const int MX = 1000000;
ll fact[MX + 1], inv_fact[MX + 1];

void precompute_fact() {
    fact[0] = 1;
    for (int i = 1; i <= MX; i++) fact[i] = fact[i-1] * i % MOD;
    inv_fact[MX] = power(fact[MX], MOD - 2);
    for (int i = MX; i > 0; i--) inv_fact[i-1] = inv_fact[i] * i % MOD;
}

ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] % MOD * inv_fact[n - r] % MOD;
}

int main() {
    cout << gcd_(12, 18) << " " << lcm_(12, 18) << "\n";   // 6 36
    cout << power(2, 10) << "\n";                           // 1024
    cout << inv_prime(3) << "\n";                           // 333333336
    cout << inv_any(3, 11) << "\n";                         // 4
    sieve();
    cout << primes.size() << "\n";                          // 78498
    for (auto& pr : factorize_spf(360)) cout << pr.first << "^" << pr.second << " ";
    cout << "\n";                                           // 2^3 3^2 5^1
    for (ll d : divisors(36)) cout << d << " ";
    cout << "\n";
    cout << phi(36) << "\n";                                // 12
    precompute_fact();
    cout << nCr(10, 3) << "\n";                             // 120
}
