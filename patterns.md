PROBLEM PATTERNS: HOW TO PICK A TECHNIQUE

=====================================================================
1. CONSTRAINTS -> REQUIRED COMPLEXITY  (C++ does ~1e8 simple ops/sec)
=====================================================================
  n <= 10          O(n!)            try all permutations (next_permutation)
  n <= 20          O(2^n * n)       bitmask / try all subsets
  n <= 50          O(n^4)           
  n <= 500         O(n^3)           triple loop, Floyd-Warshall
  n <= 5,000       O(n^2)           double loop, simple DP
  n <= 1e5 / 2e5   O(n log n)       sort, binary search, set/map, heap, segment tree
  n <= 1e6         O(n) or O(n log n) with small constant
  n <= 1e7         O(n)             linear sieve, single pass
  n <= 1e9         O(sqrt n) or O(log n)   math / divisors / binary search
  n <= 1e18        O(log n)         formula, binary exponentiation, binary search

  If your idea is O(n^2) and n = 2e5, it will TLE. Find a better idea.

=====================================================================
2. KEYWORD -> TECHNIQUE
=====================================================================
  "minimize the maximum" / "maximize the minimum"
        -> BINARY SEARCH ON ANSWER (see binary_search.cpp)
  "smallest x such that ..." / "largest x such that ..." (and checking x is easy)
        -> BINARY SEARCH ON ANSWER
  "sum of subarray", "many range sum queries"
        -> PREFIX SUM
  "add v to range [l, r]" many times, then print final array
        -> DIFFERENCE ARRAY
  "number of subarrays with sum / xor = K"
        -> PREFIX SUM + map of counts
  "max / min number of non-overlapping intervals / activities"
        -> GREEDY, sort by END time
  "merge intervals", "union of segments"
        -> sort by start, sweep
  "pair elements to minimize / maximize sum of a[i]*b[i]"
        -> sort one ascending, other descending (min); both ascending (max)
  "minimum number of operations", "can always take the best option now"
        -> try GREEDY; test it on tiny cases; if it fails, think DP
  "number of ways", "count modulo 1e9+7"
        -> DP or combinatorics (nCr mod p in number_theory.cpp)
  "divisors", "gcd", "lcm", "coprime", "prime"
        -> number_theory.cpp
  "modulo", "remainder", "cyclic", "last digit", "periodic"
        -> look for a pattern/period: brute force small cases by hand
  "k-th smallest", "median", "maintain sorted order with insertions/removals"
        -> multiset / priority_queue / binary search
  "two arrays/strings, find pair with condition"
        -> sort + TWO POINTERS
  "longest subarray / substring with property" (property keeps true when shrinking)
        -> TWO POINTERS (sliding window)
  "grid, shortest path, minimum moves, unweighted"
        -> BFS
  "all subsets", "n <= 20"
        -> bitmask loop: for (int mask = 0; mask < (1<<n); mask++)
  "count pairs (i, j) with a[i] + a[j] ..." 
        -> sort + two pointers or binary search; or map of counts
  "construct any array/string satisfying ..." 
        -> look at small cases, find the pattern, then generalize
  "minimum number of coins / cuts / steps" with huge n
        -> greedy or formula, NOT simulation

=====================================================================
3. HOW TO DECIDE A GREEDY SORT KEY
=====================================================================
  Ask: "if I have two items, in which order should I process them?"
  Write the cost for both orders, compare, and the rule falls out.
  Example: two jobs with (time t, weight w), minimize sum of w * finish_time.
    Order A then B costs  w_A*t_A + w_B*(t_A + t_B)
    Order B then A costs  w_B*t_B + w_A*(t_A + t_B)
    A first is better when  w_A * t_B > w_B * t_A  -> sort by w/t descending.
  Always test the rule on 3-4 tiny examples before coding.

=====================================================================
4. BINARY SEARCH ON ANSWER: 4-STEP RECIPE
=====================================================================
  1. State: "Is answer = x feasible?"
  2. Check it is MONOTONE: if x works then x+1 works (or x-1 works).
  3. Write check(x) in O(n) (usually a greedy scan).
  4. Search range: lo = smallest possible answer, hi = largest possible answer.
     Use first_true(...) for "minimize", last_true(...) for "maximize"
     from binary_search.cpp.

=====================================================================
5. WHEN YOU ARE STUCK
=====================================================================
  - Solve for n = 1, 2, 3 by hand. Look for a pattern.
  - Write a slow brute force (even O(n!)) on paper, then find what repeats.
  - Sort the input. Many problems become obvious after sorting.
  - Think about the answer's bounds. Is it at most ~log n? At most n?
  - Reread the statement. Look for a constraint you ignored
    ("distinct", "permutation", "sum of n over tests <= ...").
  - Ask a teammate to read the statement independently.