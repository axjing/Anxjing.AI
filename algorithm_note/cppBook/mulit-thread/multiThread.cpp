//
// Created by Anders on 2020/8/22.
//

#include "multiThread.h"
#include "multiThread.h"
#include <thread>
#include <mutex>
#include <iostream>
#include "../try1try/tryMain.cpp"

using namespace std;


multiThread::multiThread(/* args */)
{
}

multiThread::~multiThread()
{
}

int multiThread::testAI0(int n) {
    cout << "+++++++++++++++++++++++" << endl;
    return 1;

}

int multiThread::testAI1(int n) {
    cout << "HHHHHHHHHHHHHHHHHHHHHHHHH" << endl;
    return 1;

}

int multiThread::testAI2(int n) {
    cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO" << endl;
    return 1;

}

int multiThread::testAI3(int n) {
    cout << ")))))))))))))))))))))))))))))))))))))))))))" << endl;
    return 1;

}


int multiThread::testAI4(int n) {
    cout << "((((((((((((((((((((((((()))))))))))))))))))))))))" << endl;
    return 1;

}

int multiThread::testAI5(int n) {
    cout << "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}" << endl;
    return 1;
}


int multiThread::testAI6(int n) {
    cout << "[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
    return 1;
}

int multiThread::testAI7(int n) {
    cout << "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPpp" << endl;
    return 1;
}

int multiThread::testAI8(int n) {
    cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWwwwwwwwww" << endl;
    return 1;
}

int main() {
    int a = 1;
    int n = 100;
    trymain();
//	 thread threads[100];
//	 // thread threads1[100];
//	 // thread threads2[100];
//	 // thread threads3[100];
//	 multiThread test;
//	 test.testAI0;
//
//	 thread t(multiThread::testAI0,a);
//	 t.join();
//	 thread t0(multiThread::testAI1, a);
//	 t0.join();
//	 thread t1(multiThread::testAI2, a);
//	 t1.join();
//	 thread t2(multiThread::testAI3, a);
//	 t2.join();
//	 thread t3(multiThread::testAI4, a);
//	 t3.join();
//	 this_thread::sleep_for(chrono::microseconds(2));
//
//	 for (int i = 0; i < 0; i++) {
//	 	threads[i] = thread(multiThread::testAI5, a);
//	 	threads[i].join();
//	 	this_thread::sleep_for(chrono::microseconds(5));
//
//	 	threads1[i] = thread(multiThread::testAI6, a);
//	 	threads1[i].join();
//	 	this_thread::sleep_for(chrono::microseconds(5));
//
//	 	threads2[i] = thread(multiThread::testAI7, a);
//	 	threads2[i].join();
//	 	this_thread::sleep_for(chrono::microseconds(5));
//
//	 	threads3[i] = thread(multiThread::testAI5, a);
//	 	threads3[i].join();
//	 	this_thread::sleep_for(chrono::microseconds(5));
//	 }




    cout << "ok"<<endl;
    system("pause");

}