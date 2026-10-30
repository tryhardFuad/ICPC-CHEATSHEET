/*
 * GREEDY
 *
 * THEORY:
 *  Make the locally best choice at each step and never undo it.
 *  It only works when the problem has the "greedy choice property":
 *  some optimal solution contains your locally best choice.
 *
 *  How to convince yourself it is correct:
 *   1. EXCHANGE ARGUMENT: take any optimal solution, swap in your greedy
 *      choice, show the result is no worse.
 *   2. Try to find a counterexample on small inputs (brute force compare).
 *
 *  Common patterns:
 *   - Sort by some key, then scan.  (most common, think about WHICH key)
 *   - Sort by end time for interval scheduling.
 *   - Sort by deadline + min-heap to drop the worst chosen item.
 *   - Always take the smallest/largest available (priority_queue).
 *   - Two pointers on a sorted array.
 *   - Process from the largest value down (canonical coin systems only).
 *
 *  Warning signs it is NOT greedy: coin change with arbitrary coins
 *  (e.g. coins {1,3,4}, target 6: greedy gives 4+1+1, optimal is 3+3).
 *  That needs DP.
 *
 *  Habit: before coding, write down the greedy rule in one sentence and
 *  try to break it with a tiny example.
 *
 *  Choosing a sort key: take two items, write the cost of both orders,
 *  compare. The rule falls out of the inequality.
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ---- 1. Activity selection: max number of non-overlapping intervals ----
// Sort by END time. Take an interval if it starts at or after the last end.
int max_non_overlapping(vector<pair<int,int>> iv) {      // {start, end}
    sort(iv.begin(), iv.end(), [](const pair<int,int>& x, const pair<int,int>& y) {
        return x.second < y.second;
    });
    int cnt = 0, last_end = INT_MIN;
    for (auto& p : iv) {
        if (p.first >= last_end) { cnt++; last_end = p.second; }
    }
    return cnt;
}

// ---- 2. Merge overlapping intervals ----
vector<pair<int,int>> merge_intervals(vector<pair<int,int>> iv) {
    sort(iv.begin(), iv.end());
    vector<pair<int,int>> res;
    for (auto& p : iv) {
        if (!res.empty() && p.first <= res.back().second)
            res.back().second = max(res.back().second, p.second);
        else
            res.push_back(p);
    }
    return res;
}

// ---- 3. Maximum subarray sum (Kadane) ----
ll kadane(const vector<ll>& a) {
    ll best = a[0], cur = a[0];
    for (size_t i = 1; i < a.size(); i++) {
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
    }
    return best;
}

// ---- 4. Job scheduling with deadlines, maximize profit ----
// Each job takes 1 unit of time. Sort by deadline. Keep a min-heap of chosen
// profits. If chosen jobs exceed the deadline, drop the smallest profit.
ll max_profit_jobs(vector<pair<int,ll>> jobs) {          // {deadline, profit}
    sort(jobs.begin(), jobs.end());
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (auto& j : jobs) {
        pq.push(j.second);
        if ((int)pq.size() > j.first) pq.pop();
    }
    ll total = 0;
    while (!pq.empty()) { total += pq.top(); pq.pop(); }
    return total;
}

// ---- 5. Fractional knapsack: take best value/weight ratio first ----
double fractional_knapsack(vector<pair<double,double>> items, double cap) {  // {value, weight}
    sort(items.begin(), items.end(), [](const pair<double,double>& x, const pair<double,double>& y) {
        return x.first * y.second > y.first * x.second;   // compare ratios without division
    });
    double total = 0;
    for (auto& it : items) {
        if (cap <= 0) break;
        double take = min(it.second, cap);
        total += it.first * (take / it.second);
        cap -= take;
    }
    return total;
}

// ---- 6. Minimize sum of products: pair smallest with largest ----
// Given arrays a and b, rearrange to minimize sum a[i]*b[i].
// (To MAXIMIZE: sort both ascending.)
ll min_dot_product(vector<ll> a, vector<ll> b) {
    sort(a.begin(), a.end());
    sort(b.rbegin(), b.rend());
    ll s = 0;
    for (size_t i = 0; i < a.size(); i++) s += a[i] * b[i];
    return s;
}

// ---- 7. Coin change, ONLY valid for canonical systems (like 1,5,10,25,100) ----
int greedy_coins(vector<int> coins, int target) {
    sort(coins.rbegin(), coins.rend());
    int cnt = 0;
    for (int c : coins) {
        cnt += target / c;
        target %= c;
    }
    return cnt;
}

int main() {
    cout << max_non_overlapping({{1,3},{2,4},{3,5},{6,8}}) << "\n";     // 3
    for (auto& p : merge_intervals({{1,3},{2,6},{8,10},{9,12}}))
        cout << "[" << p.first << "," << p.second << "] ";               // [1,6] [8,12]
    cout << "\n";
    cout << kadane({-2, 1, -3, 4, -1, 2, 1, -5, 4}) << "\n";             // 6
    cout << max_profit_jobs({{2,100},{1,19},{2,27},{1,25},{3,15}}) << "\n"; // 142
    cout << fractional_knapsack({{60,10},{100,20},{120,30}}, 50) << "\n";   // 240
    cout << min_dot_product({1, 3, -5}, {-2, 4, 1}) << "\n";             // -25
    cout << greedy_coins({1, 5, 10, 25}, 63) << "\n";                    // 6
}
