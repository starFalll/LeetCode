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

