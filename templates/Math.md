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
        vector<int> primes;        // Store all found prime numbers
        vector<bool> isPrime(n + 1, true); // Mark the array, initially all numbers are prime
        isPrime[0] = isPrime[1] = false;   // 0 and 1 are not prime numbers

        for (int i = 2; i <= n; ++i) {
            if (isPrime[i]) {
                primes.push_back(i);   // If i is a prime number, add it to the prime number list
            }
            for (int j = 0; j < primes.size() && i * primes[j] <= n; ++j) {
                isPrime[i * primes[j]] = false; // mark the Composite number
                if (i % primes[j] == 0) {  // If i is a multiple of primes[j], exit the loop
                    break;
                }
            }
        }

        // Output prime number
        for (int prime : primes) {
            cout << prime << " ";
        }
        cout << endl;
    }
```

Time complexity: *O*(*n*).

## Greatest Common Divisor (GCD)

Time complexity: O(log(min(a, b)))

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

## Rand n to Rand m

if Rand7 = [0, 6]

Rand5 to Rand7:

```c++
int rand7()
{
    int vals[5][5] = {
        {1,2,3,4,5},
        {6,7,1,2,3},
        {4,5,6,7,1},
        {2,3,4,5,6},
        {7,0,0,0,0}
    };
    int result = 0;
    while(result == 0)
    {
        int i = rand5();
        int j = rand5();
        result = vals[i - 1][j - 1];
    }
    return result;
}
```

Simplify:

```c++
int rand7()
{
    int i;
    do{
        i = 5 * rand5() + rand5();    // Generates an integer interval of [0,24]
    }while(i > 20);                            // Control the integer interval [0,24] to [0,20]
    return i%7;                            // Map [0,20] to [0,6]
}
```

General:

```c++
// randn to randm
int randm()
{
    int i;
    do{
        i = n * randn() + randn();    
    }while(i > m*t-1);         // m*t is the largest number which is a multiple of m and less than n
    return i%m;         
}
```

Example:

[470. Implement Rand10() Using Rand7()](https://leetcode.com/problems/implement-rand10-using-rand7/)

Rand7 [1, 7], rand10 [1, 10]

```c++
// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

class Solution {
public:
    int rand10() {
        int i;
        do {
            i = 7*(rand7()-1) + rand7()-1;
        } while(i > 39);
        return i%10+1;
    }
};
```

## Sqrt

Precision:

```c++
// p is the precison
double precisionSqrt(int n,int p){
	int s=0;
	int e=n;
	double ans;
	while(s<=e){
		long long int mid=(s+e)/2;
		if(mid*mid==n){
			ans=mid;
      break;
		}
		else if(mid*mid<n){
			ans=mid;
			s=mid+1;
		}
		else{
			e=mid-1;
		}
	}
	
	float inc=0.1;
	for(int i=0;i<p;i++){
		while(ans*ans<=n){
			ans+=inc;
		}
		ans=ans-inc;
		inc=inc/10;
	}
	
	return ans;
}
int main(){
	cout<<precisionSqrt(5,3)<<endl; // out: 2.236
	return 0;
}
```

## Divisible

When there are questions about divide, considering about using the remainder.

[1497. Check If Array Pairs Are Divisible by k](https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/)
