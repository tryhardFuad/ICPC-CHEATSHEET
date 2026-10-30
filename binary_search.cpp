/*
 * BINARY SEARCH
 *
 * THEORY:
 *  Works on any monotone predicate: FFF...FTTT...T (or the reverse).
 *  Goal: find the boundary. O(log range * cost of check).
 *
 *  Two uses:
 *   1. Search a sorted array for a value.
 *   2. "Binary search on the answer": if answer x works, then x+1 (or x-1)
 *      also works. Look for phrases like "minimize the maximum" or
 *      "maximize the minimum", or "smallest x such that ...".
 *
 *  STL (sorted array a):
 *    lower_bound(a.begin(), a.end(), x)  -> first element >= x
 *    upper_bound(a.begin(), a.end(), x)  -> first element >  x
 *    count of x    = upper_bound - lower_bound
 *    binary_search(a.begin(), a.end(), x) -> bool exists
 *
 *  BUGS TO AVOID:
 *   - mid = lo + (hi - lo) / 2 (avoids overflow)
 *   - When lo = mid is possible, use mid = lo + (hi - lo + 1) / 2 or you loop forever.
 *   - Make sure hi really satisfies the predicate (for "first true").
 *   - For doubles, loop a fixed ~100 times instead of while(hi - lo > eps).
 *
 *  RECIPE FOR BINARY SEARCH ON ANSWER:
 *   1. State: "Is answer = x feasible?"
 *   2. Check it is monotone (if x works, x+1 works, or x-1 works).
 *   3. Write check(x) in O(n), usually a greedy scan.
 *   4. lo = smallest possible answer, hi = largest possible answer.
 *      "minimize"  -> first_true.   "maximize" -> last_true.
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ---- TEMPLATE 1: first x in [lo, hi] where check(x) is true ----
// Requires check(hi) == true. Pattern FFFTTT.
ll first_true(ll lo, ll hi, function<bool(ll)> check) {
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// ---- TEMPLATE 2: last x in [lo, hi] where check(x) is true ----
// Requires check(lo) == true. Pattern TTTFFF.
ll last_true(ll lo, ll hi, function<bool(ll)> check) {
    while (lo < hi) {
        ll mid = lo + (hi - lo + 1) / 2;
        if (check(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

// ---- TEMPLATE 3: real-valued answer ----
double real_search(double lo, double hi, function<bool(double)> check) {
    for (int it = 0; it < 100; it++) {
        double mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;      // minimizing. swap hi/lo updates if maximizing
        else lo = mid;
    }
    return lo;
}

// ---- Plain search for a value in sorted vector, returns index or -1 ----
int find_index(const vector<int>& a, int x) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == x) return mid;
        if (a[mid] < x) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// ---- EXAMPLE A: smallest x with x*x >= n ----
ll ceil_sqrt(ll n) {
    return first_true(0, 2000000000LL, [&](ll x) { return x * x >= n; });
}

// ---- EXAMPLE B: maximize the minimum distance (aggressive cows) ----
// Place k cows in sorted stall positions so the minimum gap is as large as possible.
// check(d): can we place k cows with every gap >= d?  (greedy)
ll aggressive_cows(vector<ll> pos, int k) {
    sort(pos.begin(), pos.end());
    auto check = [&](ll d) {
        int cnt = 1;
        ll last = pos[0];
        for (size_t i = 1; i < pos.size(); i++) {
            if (pos[i] - last >= d) { cnt++; last = pos[i]; }
        }
        return cnt >= k;
    };
    return last_true(1, pos.back() - pos[0], check);
}

// ---- EXAMPLE C: minimize the maximum (split array into k parts, min largest sum) ----
// check(m): can we split into <= k parts, each sum <= m?
ll split_array(const vector<ll>& a, int k) {
    ll lo = *max_element(a.begin(), a.end());
    ll hi = accumulate(a.begin(), a.end(), 0LL);
    auto check = [&](ll m) {
        int parts = 1;
        ll cur = 0;
        for (ll x : a) {
            if (cur + x > m) { parts++; cur = 0; }
            cur += x;
        }
        return parts <= k;
    };
    return first_true(lo, hi, check);
}

int main() {
    vector<int> a = {1, 3, 3, 5, 7, 9};
    cout << (lower_bound(a.begin(), a.end(), 3) - a.begin()) << "\n";   // 1
    cout << (upper_bound(a.begin(), a.end(), 3) - a.begin()) << "\n";   // 3
    cout << find_index(a, 7) << "\n";                                    // 4
    cout << ceil_sqrt(10) << "\n";                                       // 4
    cout << aggressive_cows({1, 2, 4, 8, 9}, 3) << "\n";                 // 3
    cout << split_array({7, 2, 5, 10, 8}, 2) << "\n";                    // 18
}
