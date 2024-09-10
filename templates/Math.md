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

## [Euler's Sieve](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)

A way to generate prime list:

```c++
void generatePrime(int n, vector<int>& res) {
        vector<int> primes;        // 存储所有找到的质数
        vector<bool> isPrime(n + 1, true); // 标记数组，初始为所有数都为质数
        isPrime[0] = isPrime[1] = false;   // 0 和 1 不是质数

        for (int i = 2; i <= n; ++i) {
            if (isPrime[i]) {
                primes.push_back(i);   // 如果 i 是质数，加入质数列表
            }
            for (int j = 0; j < primes.size() && i * primes[j] <= n; ++j) {
                isPrime[i * primes[j]] = false; // 标记合数
                if (i % primes[j] == 0) {  // 如果 i 是 primes[j] 的倍数，跳出循环
                    break;
                }
            }
        }

        // 输出质数
        for (int prime : primes) {
            cout << prime << " ";
        }
        cout << endl;
    }
```

Time complexity: *O*(*n*).

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

