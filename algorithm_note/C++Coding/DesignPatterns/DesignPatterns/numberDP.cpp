#include<iostream>
using namespace std;

/*
���ģʽ��Design Pattern����������ѵ�ʵ�������������ı���б��ܶ������Ƿ���ʹ�á�ʹ�����ģʽ�кܶ�ô���
�����ô���
��֤����ɿ���
ʹ������ױ��������
*/

//����ģʽ

/**
����ģʽ��ȷ��һ����ֻ��һ��ʵ�����������ʵ����������ϵͳ�ṩ;
����ģʽ�ַ�Ϊ������ģʽ������ģʽ������
1. ����ģʽ���������м���������ʵ��������̬ʵ�������߳��ǰ�ȫ��
2. ����ģʽ����������ʵ��������Ҫ��ʱ���ʵ�������̲߳���ȫ��Ҫ��������
���ã���֤һ����ֻ��һ��ʵ�������ṩһ����������ȫ�ַ��ʵ㣬ʹ��ϵͳ��ֻ��Ψһ
��һ������ʵ����
Ӧ�ã������ڹ�����Դ������־���̳߳�
ʵ��Ҫ�㣺
�����У�Ҫ����һ��ʵ�����ͱ��������Ĺ��캯��������Ϊ�˱�֤ȫ��ֻ��һ��ʵ����
���ֹ���ⲿ������Ĺ��캯��������ʵ������Ҫ�����캯���ķ���Ȩ�ޱ��Ϊprivate��
ͬʱ��ֹ������������ʱ��ֵʱ�����������Ҳ������������Ȩ�ޱ��Ϊprivate��
���⣬��Ҫ�ṩһ��ȫ�ַ��ʵ㣬����Ҫ�����ж���һ��static���������������ڲ�Ψһ�����ʵ����
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
	SinglePatterns(){}//��ֹ�ⲿ����ù��촴������
	SinglePatterns(SinglePatterns const &singlePatterns);//��ֹcopy��������
	SinglePatterns& operator=(SinglePatterns const &singlePatterns);//��ֹ��ֵ����

};

int main()
{
	SinglePatterns& a = SinglePatterns::getInstance();
	a.printTest();
	return 0;
}