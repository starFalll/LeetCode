## C++ Multithread

### Condition

```c++
#include <mutex>
std::mutex g_i_mutex; 
{
	const std::lock_guard<std::mutex> lock(g_i_mutex);
}

```



[1195. Fizz Buzz Multithreaded](https://leetcode.com/problems/fizz-buzz-multithreaded/)

```c++
#include <condition_variable>
#include <mutex>
class FizzBuzz {
private:
    int n;
    int count;
    mutex m;
    condition_variable cv;
public:
    FizzBuzz(int n) {
        this->n = n;
        this->count = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while(1) {
            unique_lock<mutex> lock(m);
            while (count <= n && !(this->count % 3 == 0 && this->count % 5 != 0)) {
                cv.wait(lock);
            }
            if (count > n) return;
            printFizz();
            this->count++;
            cv.notify_all();
        }
        
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while (1) {
            unique_lock<mutex> lock(m);
            while (count <= n && !(this->count % 5 == 0 && this->count % 3 != 0)) {
                cv.wait(lock);
            }
            if (count > n) return;
            printBuzz();
            this->count++;
            cv.notify_all();
        }
        
        
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while (1) {
            unique_lock<mutex> lock(m);
            while (count <= n && (this->count % 5 != 0 || this->count % 3 != 0)) {
                cv.wait(lock);
            }
            if (count > n) return;
            printFizzBuzz();
            this->count++;
            cv.notify_all();
        }
        
        
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while (1) {
            unique_lock<mutex> lock(m);
            while (count <= n && (this->count % 5 == 0 || this->count % 3 == 0)) {
                cv.wait(lock);
            }
            if (count > n) return;
            printNumber(this->count);
            this->count++;
            cv.notify_all();
        }
        
        
    }
};
```

