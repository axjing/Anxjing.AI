<!--
 * @Author: Anxjing.AI
 * @Date: 2020-08-19 17:03:00
 * @LastEditTime: 2020-08-22 11:09:10
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\C++Coding\C++基础-thread多线程.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
-->
# C++基础：std::thread多线程
# std::thread
## C++11 线程支持库 std::thread 
- 定义于头文件 <thread>
- class thread;

    - 类 thread 表示单个执行线程。线程允许多个函数同时执行。
    
    - 线程在构造关联的线程对象时立即开始执行（等待任何OS调度延迟），从提供给作为构造函数参数的顶层函数开始。顶层函数的返回值将被忽略，而且若它以抛异常终止，则调用 std::terminate 。顶层函数可以通过 std::promise 或通过修改共享变量（可能需要同步，见 std::mutex 与 std::atomic ）将其返回值或异常传递给调用方。
    
    - std::thread 对象也可能处于不表示任何线程的状态（默认构造、被移动、 detach 或 join 后），并且执行线程可能与任何 thread 对象无关（ detach 后）。
    
    - 没有两个 std::thread 对象会表示同一执行线程； std::thread 不是可复制构造 (CopyConstructible) 或可复制赋值 (CopyAssignable) 的，尽管它可移动构造 (MoveConstructible) 且可移动赋值 (MoveAssignable) 。
    - 
    - 
## 操作
- join 等待线程完成其执行(公开成员函数)
主线程等待子线程的终止。即主线程的代码块中，使用join()方法时主线程需要等待（阻塞）子线程结束了才能继续执行join()之后的代码块。
- detach容许线程从线程句柄独立开来执行(公开成员函数)

当thread::detach()函数被调用后，执行的线程从线程对象中被分离，已不再被一个线程对象所表达--这是两个独立的事情。C++线程对象可以被销毁，同时OS执行的线程可以继续。如果程序想要知道执行的线程何时结束，就需要一些其它的机制。join()函数在那个thread对象上不能再被调用，因为它已经不再和一个执行的线程相关联。

- swap 交换二个 thread 对象 (公开成员函数)非成员函数

[成员函数介绍](https://zh.cppreference.com/w/cpp/thread/thread)

## 一次启动多个线程
```cpp
//h文件

#include <thread>
#include <string>


class multiThread
{
public:
	/* data */
	static int testAI0(int n);
	static int testAI1(int n);
	static int testAI2(int n);
	static int testAI3(int n);
	static int testAI4(int n);
	static int testAI5(int n);
	static int testAI6(int n);
	static int testAI7(int n);
	static int testAI8(int n);

public:
	multiThread(/* args */);
	~multiThread();
};
```

```cpp
#include "multiThread.h"
#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

multiThread::multiThread(/* args */)
{
}

multiThread::~multiThread()
{
}

int multiThread::testAI0(int n) {
	cout << "你瞅啥？" << endl;
	return 1;

}

int multiThread::testAI1(int n) {
	cout << "瞅你咋滴！！！" << endl;
	return 1;

}

int multiThread::testAI2(int n) {
	cout << "再瞅一遍！！！" << endl;
	return 1;

}

int multiThread::testAI3(int n) {
	cout << "就瞅一遍了！！！" << endl;
	return 1;

}


int multiThread::testAI4(int n) {
	cout << "你有病啊？" << endl;
	return 1;

}

int multiThread::testAI5(int n) {
	cout << "你有药啊？" << endl;
	return 1;
}


int multiThread::testAI6(int n) {
	cout << "你有多少？" << endl;
	return 1;
}

int multiThread::testAI7(int n) {
	cout << "你吃多少我有多少？" << endl;
	return 1;
}

int multiThread::testAI8(int n) {
	cout << "你吃多少我有多少？" << endl;
	return 1;
}

int main() {
	int a = 1;
	int n = 100;
	thread threads[100];
	thread threads1[100];
	thread threads2[100];
	thread threads3[100];
	multiThread test;
	test.testAI0;
	
	thread t(multiThread::testAI0,a);
	t.join();
	thread t0(multiThread::testAI1, a);
	t0.join();
	thread t1(multiThread::testAI2, a);
	t1.join();
	thread t2(multiThread::testAI3, a);
	t2.join();
	thread t3(multiThread::testAI4, a);
	t3.join();
	this_thread::sleep_for(chrono::microseconds(2));

	for (int i = 0; i < 0; i++) {
		threads[i] = thread(multiThread::testAI5, a);
		threads[i].join();
		this_thread::sleep_for(chrono::microseconds(5));

		threads1[i] = thread(multiThread::testAI6, a);
		threads1[i].join();
		this_thread::sleep_for(chrono::microseconds(5));

		threads2[i] = thread(multiThread::testAI7, a);
		threads2[i].join();
		this_thread::sleep_for(chrono::microseconds(5));

		threads3[i] = thread(multiThread::testAI5, a);
		threads3[i].join();
		this_thread::sleep_for(chrono::microseconds(5));
	}
	

	

	cout << "ok"<<endl;
}
```