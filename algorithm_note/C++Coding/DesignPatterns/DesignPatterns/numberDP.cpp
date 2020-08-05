#include<iostream>
using namespace std;

/*
设计模式（Design Pattern）代表了最佳的实践，在面向对象的编程中被很多老鸟们反复使用。使用设计模式有很多好处：
可重用代码
保证代码可靠性
使代码更易被他人理解
*/

//单例模式

/**
单例模式：确保一个类只有一个实例，并且这个实例化向整个系统提供;
单例模式又分为（饿汉模式，懒汉模式）两种
1. 饿汉模式：程序运行即创建对象并实例化，静态实现所以线程是安全的
2. 懒汉模式：创建对象不实例化，需要的时候才实例化，线程不安全需要（加锁）
作用：保证一个类只有一个实例，并提供一个访问它的全局访问点，使得系统中只有唯一
的一个对象实例。
应用：常用于管理资源，如日志、线程池
实现要点：
在类中，要构造一个实例，就必须调用类的构造函数，并且为了保证全局只有一个实例，
需防止在外部调用类的构造函数而构造实例，需要将构造函数的访问权限标记为private，
同时阻止拷贝创建对象时赋值时拷贝对象，因此也将它们声明并权限标记为private；
另外，需要提供一个全局访问点，就需要在类中定义一个static函数，返回在类内部唯一构造的实例。
**/

class SinglePatterns
{
public:
	static SinglePatterns& getInstance()
	{
		static SinglePatterns instance;
		return instance;
	}
	void printTest()
	{
		cout<<"What are You nong sha lie???"<<endl;
		cout << "Pleace Enter: https://www.zhihu.com/people/anxjing" << endl;

	}
private:
	SinglePatterns(){}//防止外部电调用构造创建对象
	SinglePatterns(SinglePatterns const &singlePatterns);//防止copy创建对象
	SinglePatterns& operator=(SinglePatterns const &singlePatterns);//阻止赋值对象

};

int main()
{
	SinglePatterns& a = SinglePatterns::getInstance();
	a.printTest();
	return 0;
}