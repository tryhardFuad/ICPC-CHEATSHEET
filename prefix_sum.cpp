/*
 * PREFIX SUMS & DIFFERENCE ARRAYS
 *
 * THEORY:
 *  Prefix sum:  P[0] = 0, P[i] = a[1] + ... + a[i]   (1-indexed array a)
 *  Range sum a[l..r] = P[r] - P[l-1].   Build O(n), query O(1).
 *
 *  2D prefix: P[i][j] = sum of rectangle (1,1)..(i,j)
 *    P[i][j] = a[i][j] + P[i-1][j] + P[i][j-1] - P[i-1][j-1]
 *    sum (r1,c1)..(r2,c2) = P[r2][c2] - P[r1-1][c2] - P[r2][c1-1] + P[r1-1][c1-1]
 *
 *  Difference array: reverse of prefix sum. For many "add v to a[l..r]"
 *  updates and one final read:  d[l] += v;  d[r+1] -= v;
 *  then prefix-sum d to recover the array.
 *
 *  Prefix XOR works the same way: xor(l..r) = PX[r] ^ PX[l-1].
 *
 *  Classic trick: subarray sum == K  <=>  P[r] - P[l-1] == K.
 *  Scan left to right, keep a map of how many times each prefix value
 *  has occurred, add count[P[r] - K] to the answer.
 *
 *  Use long long for prefix sums. Sums overflow int very easily.
 *  Allocate n+2 for difference arrays (because of r+1).
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ---- 1D prefix sum (a is 1-indexed, a[0] unused) ----
vector<ll> build_prefix(const vector<ll>& a) {
    int n = (int)a.size() - 1;
    vector<ll> P(n + 1, 0);
    for (int i = 1; i <= n; i++) P[i] = P[i-1] + a[i];
    return P;
}
ll range_sum(const vector<ll>& P, int l, int r) { return P[r] - P[l-1]; }

// ---- 2D prefix sum (1-indexed grid) ----
vector<vector<ll>> build_prefix2d(const vector<vector<ll>>& a, int n, int m) {
    vector<vector<ll>> P(n + 1, vector<ll>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            P[i][j] = a[i][j] + P[i-1][j] + P[i][j-1] - P[i-1][j-1];
    return P;
}
ll rect_sum(const vector<vector<ll>>& P, int r1, int c1, int r2, int c2) {
    return P[r2][c2] - P[r1-1][c2] - P[r2][c1-1] + P[r1-1][c1-1];
}

// ---- Difference array: range add, then rebuild ----
struct RangeAdd {
    int n;
    vector<ll> d;
    RangeAdd(int n) : n(n), d(n + 2, 0) {}
    void add(int l, int r, ll v) { d[l] += v; d[r + 1] -= v; }   // 1-indexed
    vector<ll> build() {                                          // returns 1-indexed
        vector<ll> a(n + 1, 0);
        ll cur = 0;
        for (int i = 1; i <= n; i++) { cur += d[i]; a[i] = cur; }
        return a;
    }
};

// ---- Count subarrays with sum exactly K (works with negatives) ----
ll count_subarrays_sum_k(const vector<ll>& a, ll K) {   // a is 0-indexed here
    map<ll, ll> cnt;
    cnt[0] = 1;
    ll s = 0, ans = 0;
    for (ll x : a) {
        s += x;
        auto it = cnt.find(s - K);
        if (it != cnt.end()) ans += it->second;
        cnt[s]++;
    }
    return ans;
}

// ---- Count subarrays with sum divisible by k ----
ll count_subarrays_div_k(const vector<ll>& a, int k) {
    vector<ll> cnt(k, 0);
    cnt[0] = 1;
    ll s = 0, ans = 0;
    for (ll x : a) {
        s = ((s + x) % k + k) % k;
        ans += cnt[s];
        cnt[s]++;
    }
    return ans;
}

int main() {
    vector<ll> a = {0, 3, 1, 4, 1, 5};          // 1-indexed
    auto P = build_prefix(a);
    cout << range_sum(P, 2, 4) << "\n";          // 1+4+1 = 6

    int n = 3, m = 3;
    vector<vector<ll>> g(n + 1, vector<ll>(m + 1, 0));
    int v = 1;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) g[i][j] = v++;
    auto P2 = build_prefix2d(g, n, m);
    cout << rect_sum(P2, 2, 2, 3, 3) << "\n";    // 5+6+8+9 = 28

    RangeAdd ra(5);
    ra.add(1, 3, 2);
    ra.add(2, 5, 1);
    auto res = ra.build();
    for (int i = 1; i <= 5; i++) cout << res[i] << " ";   // 2 3 3 1 1
    cout << "\n";

    cout << count_subarrays_sum_k({1, 2, 3, -3, 3}, 3) << "\n";     // 4
    cout << count_subarrays_div_k({4, 5, 0, -2, -3, 1}, 5) << "\n"; // 7
}
