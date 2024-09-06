# Math

## Fermat's little theorem

if *p* is a [prime number](https://en.wikipedia.org/wiki/Prime_number), then for any [integer](https://en.wikipedia.org/wiki/Integer) *a*,If *a* is not divisible by *p*:

![a^{p-1} \equiv 1 \pmod p.](https://wikimedia.org/api/rest_v1/media/math/render/svg/58a9e1a77254c598a3bbd20ee75962c540381c54)

Then:
$$
a^{-1} = a^{p-2} MOD p
$$


We can use this way to devide a large number.

[2842. Count K-Subsequences of a String With Maximum Beauty](https://github.com/starFalll/LeetCode/blob/master/algorithms/2842.Count%20K-Subsequences%20of%20a%20String%20With%20Maximum%20Beauty.md)

## [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)

A way to generate prime list:

```c++
void generatePrime(int n, vector<int>& res) {
        std::vector<bool> primes(n + 1, true);
        primes[0] = primes[1] = false;
        for (int p = 2; p * p <= n; ++p) {
            if (primes[p]) {
                for (int i = p * p; i <= n; i += p) {
                    primes[i] = false;
                }
            }
        }
        std::vector<int> prime_list;
        for (int i = 2; i <= n; ++i) {
            if (primes[i]) {
                res.push_back(i);
            }
        }
    }
```

Time complexity: *O*(*n* log log *n*).

## Greatest Common Divisor (GCD)

```c++
int gcd(int a, int b) {
      return b == 0 ? a : gcd(b, a % b);
  }
// gcd(48, 18) = 6
```

calculate slope of the line:

https://leetcode.com/problems/max-points-on-a-line/description/

```c++
int dx = points[j][0] - points[i][0];
int dy = points[j][1] - points[i][1];
int d = gcd(dx, dy);
++m[{dx/d, dy/d}];
```

