/*
 * @Description: ��ϰcout
 * @Author: Xjing An
 * @Date: 2019-09-24 09:31:54
 * @LastEditTime: 2019-10-06 19:15:20
 * @LastEditors: Please set LastEditors
 */
#include <iostream> //���ļ��е����������������У���python��import����,/ iosteram(input&out stream)�а���������������ĺ���
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iomanip>
#include <windows.h> //window�����ն�
#include <string>
#include <limits>
using namespace std;

//exp23 ָ��ͺ���
// ʵ���������ֽ���
void swap23(int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp;
    cout << "swap a23 = " << a23 << endl;
    cout << "swap b23 = " << b23 << endl;
}


int main()
{
    //exp23 ָ��ͺ���
    int a23 = 10;
    int b23 = 20;
    swap23(a, b);
    cout << "a23 = " << a23 << endl;
    cout << "b23 = " << b23 << endl;
    
    //exp22 ��Ŀ�����,���ص��Ǳ��������Լ�����ֵ
    //�﷨�� ���ʽ1 �� ���ʽ2 �����ʽ3��
    //������ʽ1Ϊ�棬ִ�б��ʽ2�������ر��ʽ2�Ľ��
    //������ʽ1Ϊ�٣�ִ�б��ʽ3�������ر��ʽ3�Ľ��
    int a22 = 10;
    int b22 = 20;
    int c22 = 0;
    c22 = (a22>b22 ? a22:b22);
    (a22>b22 ? a22 : b22) = 100;
    cout << a22 << endl;
    cout << b22 << endl;
    cout << c22 << endl;
    

    //exp21 bool��������
    bool flag21 = true;
    cout << flag21 << "bool������ռ�õ��ڴ�ռ䣺" << sizeof(flag21) << endl;
    
    //exp20�ַ�������
    char str20[] = "I Love You!!!";
    string str201 = "C++��I Love You!!!"; // ����һ��include <string>
    cout << "C����ַ�����" << str20 << endl;
    cout << "C+����ַ�����" << str201 << endl;
    
    //exp19�ַ��͵Ĵ����������ڴ�ռ䡢��������ֻ���õ����ţ�ֻ���ǵ����ַ�
    char ch19 = 'a';
    cout << "a=" << ch19 << "�ַ��ͱ����Ĵ�С��" << sizeof(ch19) << endl;
    cout << "ASCIIֵ��" << int(ch19) << endl;
    
    //exp18 ָ������������
    //������vs˫����
    float f1 = 3.14f;
    double f2 = -3.13;
    float f3 = 3e-21;
    cout << "f1=" << f1 << "�ַ����ȣ�" << sizeof(f1) << endl;
    cout << "f2=" << f2 << "�ַ����ȣ�" << sizeof(f2) << endl;
    cout << "f3=" << f3 << "�ַ����ȣ�" << sizeof(f3) << endl;
    double score[] {11, 22, 33, 44, 55};
    double *ptr_score = score;
    
    for (int i = 0; i < 5; i++){
        cout << *ptr_score++ << endl;
    }
    //���������Ǿ���������׵�ַ
    cout << sizeof(score) << "\t" << sizeof(ptr_score) << endl;
    cout << ptr_score[3] << endl;
    // exp17ָ��--------------------------------------
    /**
     * ָ����һ��ֵΪ�ڴ��ַ�ı����������ݶ���
     * 
     * */
    double num17 = 1024.5;
    //����һ��ָ�룬ָ��num17����
    double* ptr_num17 = &num17;
    double &ref_num17 = num17;
    cout << "ptr_num is Value:" << ptr_num17 << "\t" << &num17 << "\t"<< ref_num17 <<  endl;
    cout << "ptr_num17 ָ��ռ��ֵ��" << *ptr_num17 << endl;

    //exp16 ����--------------------------------------
    int num16[] = {1, 2, 4, 'c', 231231};
    cout << num16[2] << endl;
    // ��̬¼����Ϣ����ֵ
    const int N1 = 5;
    int num161[N1];

    for (int i = 0; i < sizeof(num161) / sizeof(int); i++){
        cout << "�������" << (i+1) << endl;
        cin >> num161[i];
    }
    for (int i = 0; i<sizeof(num161) / sizeof(int); i++){
        cout << num161[i] << endl;
    }


    //exp15-------------------------------------------
    //break ����ѭ�� continue�����´�ѭ��


    //exp14-------------------------------------------
    //for 
    /**
     * for(���ʽ1�����ʽ2�����ʽ3){
          ��䣻
    }*/
    const int N = 20;
    for (int i=0; i<N; i++){
        cout << "zaibiekangqiao"<< endl;
        if (i == 6){
            break;
        }
    }

    // exp13------------------------------------------
    // while
    int i = 0;  //ѭ�������ĳ�ʼֵ
    int sum = 0; //���������ۼӺ͵ı���
    while (i <= 100) //ѭ������������
    {
        cout << "-----" << endl;
        sum = sum + i; //�ۼ�
        i++;    //ѭ����������
        cout << sum << endl;
    }
    
        
    //exp12-------------------------------------------
    int num0 = 5;
    cout << sizeof(num0++) << endl;  //4
    cout << num0 << endl;            //5
    //exp11 ---------------------------------------
    // �˵�ѡ��
    // switch(���ʽ){case ����1�� ��䣻break; } ����
    int choice = 1;
    switch (choice)
    {
    case 1:
        cout << 1 << endl;
        break;
    case 2:
        cout << 2 << endl;
        break;
    case 3:
        cout << 3 << endl;
        break;
    
    default:
        break;
    }
    // exp10--------------------------------------
    // if  else if  else
    double flower_price; //���ĵ���
    cout << "����ǰ�ĺڰ�����ȥ�� ����֮��͸��һĨ���⣬�·�һ�ѵ�ȼ�Ļ�ѡ�����" << endl;
    cin >> flower_price;
    cout << flower_price << endl;
    //exp9----------------------------------------
    //if �������
    double price_louis = 35000.0;
    double price_hemes = 11044.5;
    double price_chanel = 1535.0;
    double total = 0;   // �ܼ�
    double zhekou = 0;  // �ۿ�
    total = price_chanel + price_hemes + price_louis;
    /**
     *��������������Ʒ��һ����Ʒ���۴���1000
     *��������Ʒ�ܶ����5000���ۿ���Ϊ30%
     *����û���ۿ�
     */
    if (price_louis > 1000 || price_hemes >1000 || price_chanel > 1000 || total > 5000){
        cout << "�ۿ�Ϊ0.3" << endl;
    }
    else{
        cout << "û���ۿ�" << endl;
    }

    //exp8----------------------------------------
    //����������ʽ����=����ֵ�����
    double salary = 3200.0; //���������
    int num9 = 1024;
    //���������
    num9 += 90;
    num9 -= 90;
    num9 /= 90;
    num9 *= 90;
    num9 %= 90; //ȡģ��ȡ��

    cout << num9 << endl;

    //ǰ�õ�������������õ�����ǰ�õݼ������õݼ�
    int num_8 = 10;
    int num_8_1 = 10;
    //int num_80 = ++num_8; //ǰ�õ��������ñ���+1,Ȼ����б��ʽ����
    int num_81 = ++num_8 * 9;
    cout<< "ǰ�õ�����" << "num_80" << "ǰ�õ������ʽ��" << num_81 << endl;
    //int num_82 = num_8++; //���õ������Ƚ��б��ʽ���㣬���ñ���+1
    int num_83 = num_8_1++ * 9;
    cout<< "���õ�����" << "num_82" << "���õ������ʽ��" << num_83 << endl;

    //int num_84 = --num_8; //ǰ�õ��������ñ���+1,Ȼ����б��ʽ����
    int num_85 = --num_8 * 9;
    cout<< "ǰ�õݼ���" << "num_84" << "ǰ�õݼ����ʽ��" << num_85 << endl;
    //int num_86 = num_8--; //���õ������Ƚ��б��ʽ���㣬���ñ���+1
    int num_87 = num_8-- * 9;
    cout<< "���õݼ���" << "num_86" << "���õݼ����ʽ��" << num_87 << endl;
    
    // ��ϵ�����>, <, >=, <=, ==, !=

    int a = 4, b = 16;
    cout << (a>b) << endl;
    cout << (a<b) << endl;

    // �߼������ a && b, a����b; a || b a��b; ! ��
    cout << ("---------------") <<endl;
    cout << (a && b) << endl;
    cout << (a||b) << endl;
    cout << (!a) <<endl;
    cout << ("---------------") <<endl;

    //λ�������&��|�� ~, ^, <<, >>, ��λ�롢�򡢷ǡ�������ƣ����ơ�(������ֹת��Ϊ�����ƣ��������ת��Ϊ��������)
    cout << ("---------------") <<endl;
    cout << (a & b) << endl;
    cout << (a|b) << endl;
    cout << (~a) <<endl;
    cout << (a^b) << endl;
    cout << (4<<a) << endl;
    cout << (a >> 4) << endl;
    cout << ("---------------") <<endl;
    



    //exp7-----------------------------------------
    // �Ӽ��˳���ȡģ
    double attack7 = 272;
    double attack8 = 250;
    double attack9 = 240;

    int num1 = -5, num2 =2;
    num1 = num2++ - --num2; //���ã�ǰ��
    cout << num1 << "\t" << num2 << endl;

    cout << num1 / num2 << endl; //����
    cout << num1 % num2 << endl; //ȡģ


    //cout << setfill("--") << endl;

    cout << setw(8) << attack7 << 
            setw(8) << attack8 <<
            setw(8) << attack9 << endl;
    //exp6-----------------------------------------
    // ������ϰ
    int num;
    char ch;
    cout << "������һ�����ݣ�";
    cin >> ch;
    cout << num << "\t" << ch << endl;


    //exp5-----------------------------------------
    // �޸��ն˱��⣺���ྲWorkSpace
    //SetConsoleTitle("���ྲ��WorkSpace");
    /**�˺�*/
    double value_attack = 57.88;
    /**�˺��ɳ�ֵ*/
    double grouth_attack = 4.5;
    /**��������*/
    double distance_attack = 27.58;
    
    cout << "���ƣ���������֮��"<<endl;
    cout << "�˺���" << value_attack << "(" << distance_attack << ")" <<endl;
    //exp4------------------------------------------
    //sizeof ���������������͵ĳ���
    cout <<sizeof(double)<<endl;
    cout <<sizeof(long double) << endl;
    cout <<sizeof(3.14f)<< endl;
    cout << "type: \t\t" << "************size**************"<< endl;  
    cout << "bool: \t\t" << "��ռ�ֽ�����" << sizeof(bool);  
    cout << "\t���ֵ��" << (numeric_limits<bool>::max)();  
    cout << "\t\t��Сֵ��" << (numeric_limits<bool>::min)() << endl;  
    cout << "char: \t\t" << "��ռ�ֽ�����" << sizeof(char);  
    cout << "\t���ֵ��" << (numeric_limits<char>::max)();  
    cout << "\t\t��Сֵ��" << (numeric_limits<char>::min)() << endl;  
    cout << "signed char: \t" << "��ռ�ֽ�����" << sizeof(signed char);  
    cout << "\t���ֵ��" << (numeric_limits<signed char>::max)();  
    cout << "\t\t��Сֵ��" << (numeric_limits<signed char>::min)() << endl;  
    cout << "unsigned char: \t" << "��ռ�ֽ�����" << sizeof(unsigned char);  
    cout << "\t���ֵ��" << (numeric_limits<unsigned char>::max)();  
    cout << "\t\t��Сֵ��" << (numeric_limits<unsigned char>::min)() << endl;  
    cout << "wchar_t: \t" << "��ռ�ֽ�����" << sizeof(wchar_t);  
    cout << "\t���ֵ��" << (numeric_limits<wchar_t>::max)();  
    cout << "\t\t��Сֵ��" << (numeric_limits<wchar_t>::min)() << endl;  
    cout << "short: \t\t" << "��ռ�ֽ�����" << sizeof(short);  
    cout << "\t���ֵ��" << (numeric_limits<short>::max)();  
    cout << "\t\t��Сֵ��" << (numeric_limits<short>::min)() << endl;  
    cout << "int: \t\t" << "��ռ�ֽ�����" << sizeof(int);  
    cout << "\t���ֵ��" << (numeric_limits<int>::max)();  
    cout << "\t��Сֵ��" << (numeric_limits<int>::min)() << endl;  
    cout << "unsigned: \t" << "��ռ�ֽ�����" << sizeof(unsigned);  
    cout << "\t���ֵ��" << (numeric_limits<unsigned>::max)();  
    cout << "\t��Сֵ��" << (numeric_limits<unsigned>::min)() << endl;  
    cout << "long: \t\t" << "��ռ�ֽ�����" << sizeof(long);  
    cout << "\t���ֵ��" << (numeric_limits<long>::max)();  
    cout << "\t��Сֵ��" << (numeric_limits<long>::min)() << endl;  
    cout << "unsigned long: \t" << "��ռ�ֽ�����" << sizeof(unsigned long);  
    cout << "\t���ֵ��" << (numeric_limits<unsigned long>::max)();  
    cout << "\t��Сֵ��" << (numeric_limits<unsigned long>::min)() << endl;  
    cout << "double: \t" << "��ռ�ֽ�����" << sizeof(double);  
    cout << "\t���ֵ��" << (numeric_limits<double>::max)();  
    cout << "\t��Сֵ��" << (numeric_limits<double>::min)() << endl;  
    cout << "long double: \t" << "��ռ�ֽ�����" << sizeof(long double);  
    cout << "\t���ֵ��" << (numeric_limits<long double>::max)();  
    cout << "\t��Сֵ��" << (numeric_limits<long double>::min)() << endl;  
    cout << "float: \t\t" << "��ռ�ֽ�����" << sizeof(float);  
    cout << "\t���ֵ��" << (numeric_limits<float>::max)();  
    cout << "\t��Сֵ��" << (numeric_limits<float>::min)() << endl;  
    cout << "size_t: \t" << "��ռ�ֽ�����" << sizeof(size_t);  
    cout << "\t���ֵ��" << (numeric_limits<size_t>::max)();  
    cout << "\t��Сֵ��" << (numeric_limits<size_t>::min)() << endl;  
    cout << "string: \t" << "��ռ�ֽ�����" << sizeof(string) << endl;  
    // << "\t���ֵ��" << (numeric_limits<string>::max)() << "\t��Сֵ��" << (numeric_limits<string>::min)() << endl;  
    cout << "type: \t\t" << "************size**************"<< endl;
    

    //exp3-------------------------------------------
    //����cout��ʾ����
    //1.ǿ����С���ķ�ʽ��ʾ
    cout << fixed;
    // 2.������ʾ�ľ���
    cout << setprecision(2);
    //���double���͵Ĳ���
    double double_num = 10.0 / 3.0;
    cout << double_num <<endl;

    //exp2-----------------------------------------
    //��֪Բ����İ뾶�͸ߣ���Բ��������
    const float PI = 3.141592653; //const ������һ��float���͵ĳ���
    float radius = 4.5f;
    float height = 90.0f;
    double volume = PI * pow(radius, 2);
    cout <<volume<<endl;


    //exp1---------------------------------------
    cout <<"hello world!!!"<<endl;
    cout <<"�����ҵ���Ʋ���ѽ\n";
    cout <<"��ô���ҵ����õľ�ҵ\n";
    cout <<"ѧϰC++\n";
    SetConsoleOutputCP(65001);
    system("pause");
    
    return 0;
}

//ÿ�����ռһ��
//ע��ֺţ�������
//ע��ֺţ��ո�
//
/*
 *�ļ�����
 *��  ����
 *��  �ߣ�
 *ʱ  �䣺
 *��  ����
*/