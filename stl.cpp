/*
 * STL CHEATSHEET: copy only the block you need.
 * Each block is in its own { } so names do not clash.
 * Complexities are written next to each operation.
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {

    // ---------- SORTING ----------
    {
        vector<int> a = {5, 2, 9, 1};
        sort(a.begin(), a.end());                 // ascending
        sort(a.rbegin(), a.rend());               // descending
        sort(a.begin(), a.end(), greater<int>()); // descending (alternative)

        // sort pairs by first asc, ties by second DESC
        vector<pair<int,int>> p = {{1,5}, {2,3}, {1,2}};
        sort(p.begin(), p.end(), [](const pair<int,int>& x, const pair<int,int>& y) {
            if (x.first != y.first) return x.first < y.first;
            return x.second > y.second;
        });

        // sort indices by value (keeps original positions)
        vector<int> v = {50, 10, 40};
        vector<int> idx(v.size());
        iota(idx.begin(), idx.end(), 0);          // idx = 0,1,2
        sort(idx.begin(), idx.end(), [&](int i, int j) { return v[i] < v[j]; });
        // idx is now 1,2,0
    }

    // ---------- UNIQUE / COORDINATE COMPRESSION ----------
    {
        vector<int> a = {10, 5, 10, 7, 5};
        vector<int> s = a;
        sort(s.begin(), s.end());
        s.erase(unique(s.begin(), s.end()), s.end());   // s = 5 7 10
        // compressed index of a[i]:
        for (int x : a) {
            int id = lower_bound(s.begin(), s.end(), x) - s.begin();   // 0-indexed
            cout << id << " ";
        }
        cout << "\n";
    }

    // ---------- SET / MULTISET (sorted, O(log n) each) ----------
    {
        set<int> s;
        s.insert(5); s.insert(1); s.insert(9);
        s.erase(5);                               // erase by value
        bool has = s.count(1);                    // 0 or 1
        int mn = *s.begin();                      // smallest
        int mx = *s.rbegin();                     // largest
        auto it = s.lower_bound(4);               // first element >= 4  (USE MEMBER, not std::)
        if (it != s.end()) cout << *it << "\n";
        auto it2 = s.upper_bound(4);              // first element > 4
        // largest element <= x:
        auto it3 = s.upper_bound(4);
        if (it3 != s.begin()) { --it3; cout << *it3 << "\n"; }

        multiset<int> ms;
        ms.insert(3); ms.insert(3); ms.insert(7);
        ms.erase(ms.find(3));                     // removes ONE copy of 3
        // ms.erase(3) would remove ALL copies of 3!
        int copies = ms.count(3);
    }

    // ---------- MAP (key -> value, sorted by key) ----------
    {
        map<string,int> m;
        m["abc"]++;                               // auto-creates with 0
        m["abc"] += 5;
        if (m.count("abc")) cout << m["abc"] << "\n";
        for (auto& [key, val] : m) cout << key << " " << val << "\n";   // C++17
        // m[x] on a missing key CREATES it. Use m.count(x) or m.find(x) to only check.
        // unordered_map is O(1) average but can be slow on bad input; map is safer.
    }

    // ---------- PRIORITY QUEUE (heap) ----------
    {
        priority_queue<int> mx;                                   // MAX-heap
        priority_queue<int, vector<int>, greater<int>> mn;        // MIN-heap
        mx.push(5); mx.push(9);
        int top = mx.top(); mx.pop();                             // top = 9
        // pairs: compares first, then second
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
        pq.push({10, 3});
    }

    // ---------- VECTOR / ARRAY HELPERS ----------
    {
        vector<int> a = {3, 1, 4, 1, 5};
        int mx = *max_element(a.begin(), a.end());
        int mn = *min_element(a.begin(), a.end());
        int pos_max = max_element(a.begin(), a.end()) - a.begin();   // index of max
        ll sum = accumulate(a.begin(), a.end(), 0LL);                // 0LL, not 0!
        int c = count(a.begin(), a.end(), 1);                        // occurrences of 1
        reverse(a.begin(), a.end());
        bool sorted_ok = is_sorted(a.begin(), a.end());
        vector<int> filled(10, -1);                                  // 10 copies of -1
        fill(filled.begin(), filled.end(), 0);
        vector<vector<int>> grid(5, vector<int>(7, 0));              // 5 x 7 grid of 0
        a.insert(a.begin() + 2, 99);                                 // O(n)
        a.erase(a.begin() + 2);                                      // O(n)
    }

    // ---------- PERMUTATIONS / SUBSETS ----------
    {
        vector<int> a = {1, 2, 3};                // MUST start sorted to get all permutations
        do {
            for (int x : a) cout << x << " ";
            cout << "\n";
        } while (next_permutation(a.begin(), a.end()));

        int n = 4;
        for (int mask = 0; mask < (1 << n); mask++)            // all subsets of n items
            for (int i = 0; i < n; i++)
                if (mask >> i & 1) { /* item i is in this subset */ }
    }

    // ---------- STRINGS ----------
    {
        string s = "hello world";
        int len = s.size();
        string sub = s.substr(6, 5);              // substr(start, LENGTH) -> "world"
        size_t p = s.find("wor");                 // returns string::npos if not found
        if (p != string::npos) cout << p << "\n";
        reverse(s.begin(), s.end());
        sort(s.begin(), s.end());
        int x = stoi("123");                      // string -> int
        ll y = stoll("1234567890123");            // string -> long long
        string t = to_string(456);                // number -> string
        int d = '7' - '0';                        // char digit -> int
        char c = 'a' + 3;                         // 'd'
        // read a whole line (after a cin >> n, first call cin.ignore())
        // string line; cin.ignore(); getline(cin, line);
        // split by spaces:
        stringstream ss("a bb ccc");
        string w;
        while (ss >> w) cout << w << "\n";
    }

    // ---------- BITSET / BITS ----------
    {
        bitset<32> b(10);                          // 00...1010
        int ones = b.count();
        int pc = __builtin_popcount(10u);          // use popcountll for long long
        int highest_bit = 31 - __builtin_clz(10);  // index of highest set bit (x > 0)
        int lowest_bit = __builtin_ctz(12);        // index of lowest set bit (x > 0) -> 2
    }

    // ---------- MIN / MAX / SWAP / MEMSET ----------
    {
        int a = 3, b = 5;
        int m = min(a, b);
        ll m2 = max(1LL * a, 5LL);                 // both args must be the SAME type
        swap(a, b);
        int arr[100];
        memset(arr, 0, sizeof arr);                // memset only safely sets 0 or -1
        // for other values use fill(arr, arr + 100, value)
    }

    // ---------- LAMBDA RECURSION (DFS) ----------
    {
        int n = 5;
        vector<vector<int>> g(n);
        g[0] = {1, 2}; g[1] = {3}; g[2] = {4};
        vector<bool> vis(n, false);
        function<void(int)> dfs = [&](int u) {
            vis[u] = true;
            for (int v : g[u]) if (!vis[v]) dfs(v);
        };
        dfs(0);
    }

    // ---------- OUTPUT TRICKS ----------
    {
        cout << fixed << setprecision(9) << 3.14159 << "\n";    // print doubles
        cout << (true ? "YES" : "NO") << "\n";
        vector<int> a = {1, 2, 3};
        for (int i = 0; i < (int)a.size(); i++)
            cout << a[i] << " \n"[i + 1 == (int)a.size()];       // spaces, newline at end
    }
}