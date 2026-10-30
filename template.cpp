/*
 * BASE TEMPLATE (with debug macro)
 *
 * dbg(x) prints "x = value" to stderr ONLY when compiled with -DLOCAL.
 * On the judge it does nothing, so you can leave dbg() calls in.
 * If you cannot pass -DLOCAL, just delete the dbg lines before submitting.
 *
 * REMEMBER:
 *  - int max ~ 2.1e9. If a value or product can exceed that, use long long.
 *  - Use '\n', not endl (endl is slow).
 *  - Reset global arrays/vectors between test cases.
 *  - Delete the "cin >> t" line if the problem has a single test case.
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << endl
#else
#define dbg(x)
#endif

const int MOD = 1e9 + 7;
const ll INF = 1e18;

void solve() {
    int n;
    cin >> n;
    vll a(n);
    for (auto &x : a) cin >> x;

    // your code here
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;                // delete this line if single test case
    while (t--) solve();
    return 0;
}