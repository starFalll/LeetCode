## C++ Multithread

### Mutex

```c++
#include <mutex>
std::mutex g_i_mutex; 
{
	const std::lock_guard<std::mutex> lock(g_i_mutex);
}

{
	const std::unique_lock<std::mutex> lock(g_i_mutex);
}
```

Difference between `lock_guard` and `unique_lock`:

`lock_guard` cannot lock and unlock mannually

`unique_lock` has `lock()` and `unlock` function to use, it can defer lock:

```c++
std::mutex mtx;

void worker(int id) {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);  // 不立即获取锁
    std::this_thread::sleep_for(std::chrono::seconds(1));      // 模拟一些不需要锁的工作
    lock.lock();                                               // 在需要时手动加锁
    std::cout << "Thread " << id << " is working with the resource.\n";
    // 自动解锁，当 `lock` 退出作用域时
}
```

lock many lock at the same time: `std::lock`

```c++
std::lock(lock1, lock2);
```



## Condition Variable

condition variable must use unique_lock

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

## multithreading

```c++
// C++ program to demonstrate
// multithreading using three
// different callables.
#include <iostream>
#include <thread>
using namespace std;

// A dummy function
void foo(int Z)
{
    for (int i = 0; i < Z; i++) {
        cout << "Thread using function"
                " pointer as callable\n";
    }
}

// A callable object
class thread_obj {
public:
    void operator()(int x)
    {
        for (int i = 0; i < x; i++)
            cout << "Thread using function"
                    " object as callable\n";
    }
};

// class definition
class Base {
public:
    // non-static member function
    void foo()
    {
        cout << "Thread using non-static member function "
                "as callable"
             << endl;
    }
    // static member function
    static void foo1()
    {
        cout << "Thread using static member function as "
                "callable"
             << endl;
    }
};

// Driver code
int main()
{
    cout << "Threads 1 and 2 and 3 "
            "operating independently"
         << endl;

    // This thread is launched by using
    // function pointer as callable
    thread th1(foo, 3);

    // This thread is launched by using
    // function object as callable
    thread th2(thread_obj(), 3);

    // Define a Lambda Expression
    auto f = [](int x) {
        for (int i = 0; i < x; i++)
            cout << "Thread using lambda"
                    " expression as callable\n";
    };

    // This thread is launched by using
    // lambda expression as callable
    thread th3(f, 3);

    // object of Base Class
    Base b;
  
    thread th4(&Base::foo, &b);

    thread th5(&Base::foo1);

    // Wait for the threads to finish
    // Wait for thread t1 to finish
    th1.join();

    // Wait for thread t2 to finish
    th2.join();

    // Wait for thread t3 to finish
    th3.join();

    // Wait for thread t4 to finish
    th4.join();

    // Wait for thread t5 to finish
    th5.join();

    return 0;
}

```

## Semaphore

```c++
#include <semaphore.h>
```

`sem_init(&semaphore, 0, 3)` initializes the semaphore to allow a maximum of 3 threads to access the critical section simultaneously. The second parameter (`0`) indicates that the semaphore is shared between threads in the same process (set to non-zero for inter-process semaphores).

`sem_wait(&semaphore)` is called to decrement the semaphore. If the value is greater than 0, the thread proceeds; otherwise, it blocks until the semaphore is available.

`sem_post(&semaphore)` to increment the semaphore, signaling that it has released the resource. **If the value of the semaphore resulting from this operation is zero, then one of the threads blocked waiting for the semaphore shall be allowed to return successfully from its call to [*sem_wait*()](https://pubs.opengroup.org/onlinepubs/009695399/functions/sem_wait.html)**

Means: count from -1->0, wake one waiting thread.
