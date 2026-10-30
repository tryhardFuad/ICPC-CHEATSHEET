MATH & COUNTING QUICK SHEET

=====================================================================
1. CONTRIBUTION TECHNIQUE (very common)
=====================================================================
  Instead of enumerating all subarrays/pairs, ask: "how many times does
  element i contribute to the answer?"  Then answer = sum over i of
  (value_i * times_i).

  Example: sum of ALL subarray sums of a[0..n-1] (0-indexed).
    a[i] is in (i+1) * (n-i) subarrays  (choices for left end * right end)
    answer = sum a[i] * (i+1) * (n-i)       (use long long, maybe mod)

  Example: sum of |a[i]-a[j]| over all pairs. Sort the array first.
    After sorting, a[i] is the larger one in i pairs (with earlier elements)
    and the smaller one in (n-1-i) pairs.
    answer = sum a[i] * (i - (n-1-i)) = sum a[i] * (2i - n + 1)

=====================================================================
2. COUNTING PAIRS
=====================================================================
  Pairs (i < j) among n items:        n*(n-1)/2
  Pairs with a[i] + a[j] = X:         sweep left to right, keep a map of counts,
                                      add count[X - a[i]] before inserting a[i]
  Equal pairs:                         for each value with frequency f add f*(f-1)/2
  Complement counting:                 count ALL, subtract the BAD ones.
                                       Often easier than counting good directly.

=====================================================================
3. INCLUSION-EXCLUSION (two or three sets)
=====================================================================
  |A or B|      = |A| + |B| - |A and B|
  |A or B or C| = |A|+|B|+|C| - |A&B| - |A&C| - |B&C| + |A&B&C|
  Numbers in [1,n] divisible by a or b:   n/a + n/b - n/lcm(a,b)
  Numbers in [1,n] divisible by a:        n/a      (integer division)
  Numbers in [l,r] divisible by a:        r/a - (l-1)/a

=====================================================================
4. COMBINATORICS
=====================================================================
  Arrange n distinct items:                n!
  Arrange with repeats (counts c1,c2,..):  n! / (c1! * c2! * ...)
  Choose r of n:                           nCr
  Stars and bars: put n identical balls in k boxes (boxes can be empty):
                                           C(n + k - 1, k - 1)
  Each box at least 1:                     C(n - 1, k - 1)
  Binary strings of length n:              2^n
  Subsets of n items:                      2^n
  Paths in a grid, right/down only, (r x c moves): C(r + c, r)
  Derangements D(n) = (n-1) * (D(n-1) + D(n-2)),  D(0)=1, D(1)=0

=====================================================================
5. PARITY AND SMALL FACTS
=====================================================================
  Sum of n numbers is even <=> the count of odd numbers is even.
  A product is odd <=> all factors are odd.
  n is a perfect square <=> it has an odd number of divisors.
  x ^ x = 0,  x ^ 0 = x,  XOR is its own inverse.
  a + b = (a ^ b) + 2 * (a & b)
  a | b = (a ^ b) + (a & b)
  Swap without temp: a ^= b; b ^= a; a ^= b;  (just use swap())
  Max sum of 2 elements: take the two largest. Min: the two smallest.
  Last digit of n: n % 10.  Remove last digit: n / 10.
  Number of digits of n: to_string(n).size()
  gcd(a, b) = gcd(a, b - a);  gcd with 0: gcd(a, 0) = a.
  lcm of 1..n grows very fast (n=40 already exceeds 1e16).

=====================================================================
6. MODULAR ARITHMETIC PITFALLS
=====================================================================
  - After a SUBTRACTION do:   ((a - b) % MOD + MOD) % MOD
  - Multiply in long long BEFORE %:  (1LL * a * b) % MOD
  - Never divide mod a number; multiply by its inverse (number_theory.cpp).
  - Do % after EVERY multiplication inside a loop.
  - Compare modded values only for equality, never for < or >.

=====================================================================
7. SIMULATION SHORTCUTS
=====================================================================
  - If a process repeats with a cycle, find the cycle length L and use (k % L).
  - If something happens "every k steps": use division, not a loop.
  - If n is huge (1e9+) and the loop would be slow: the answer is a formula.
    Compute it for n = 1..10 by hand and look for the pattern.

=====================================================================
8. CONSTRUCTIVE PROBLEMS ("print any valid array/string")
=====================================================================
  - Try sorted order, alternating (big, small, big, small), or all-equal.
  - Try the smallest case that works, then extend it.
  - If the answer is "impossible" in some cases, find the exact condition
    by brute force on tiny n and print NO / -1 for those cases.