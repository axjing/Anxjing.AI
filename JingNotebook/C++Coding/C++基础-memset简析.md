<!--
 * @Author: Anxjing.AI
 * @Date: 2020-07-21 21:02:38
 * @LastEditTime: 2020-08-02 11:15:25
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\C++Coding\C++基础-memset简析.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
--> 
# memset函数简析
```
功 能: 将s所指向的某一块内存中的每个字节的内容全部设置为ch指定的ASCII值,块的大小由第三个参数指定,这个函数通常为新申请的内存做初始化工作

用 法: void *memset(void *s, char ch, unsigned n);

在以下情况下，该函数的行为是不确定的：

该对象不可复制。
count 大于的大小 目的。
它在<cstring>头文件中定义。

memset（）参数
目的：指向要复制字符的对象的指针。
ch：要复制的字符。
计数：要复制的次数。
memset（）返回值
memset（）函数返回目标目的地的指针dest。

对比：
memcpy用来做内存拷贝，你可以拿它拷贝任何数据类型的对象，可以指定拷贝的数据长度；例：char a[100],b[50]; memcpy(b, a, sizeof(b));注意如用sizeof(a)，会造成b的内存地址溢出。

strcpy就只能拷贝字符串了，它遇到'/0'就结束拷贝；例：char a[100],b[50];strcpy(a,b);如用strcpy(b,a)，要注意a中的字符串长度（第一个‘/0’之前）是否超过50位，如超过，则会造成b的内存地址溢出。
```


# memset：char型初始化函数

## 头文件：<string.h> 或 <memory.h>

## 函数原型：void *memset(void *s , int ch , size_t  n )

```
memset(结构体/数组名 , 用于替换的ASCII码对应字符 , 前n个字符 );

memset(结构体/数组名 , "用于替换的字符“ , 前n个字符 );

函数解释：将s中的前n个字节用ch替换并且返回s

函数作用：在一段内存块中填充某一个给定的值，常用于较大的对结构体和数组的清零操作。
```

```C++
//例1
#include<iostream>
//#include"string.h"
using namespace std;
int main()
{
    char str[10];
    str[9] = 'w';
    memset(str,97,9);
    for(int i=0;i<10;i++){
        cout<<str[i]<<" ";
    }
    return 0;
} 
```
*输出：a a a a a a a a a w*

说明：使用memset似乎不需要使用额外的头文件。

```C++
//例2
#include<iostream>
//#include"string.h"
using namespace std;
int main()
{
    char str[10];
    str[9] = 'a';
    memset(str,97,sizeof(char)*10);
    for(int i=0;i<10;i++){
        cout<<str[i]<<" ";
    }
    return 0;
} 
```
*输出：a a a a a a a a a a*

 

```C++
#include<iostream>
using namespace std;
int main()
{
    char str[10];
    memset(str,65,sizeof(str)-3);
    for(int i=0;i<10;i++){
        cout<<str[i]<<" ";
    } 
    return 0;
}
```
*输出：A A A A A A A *



void * memset（void * dest，int ch，size_t count）;
该memset()函数接受三个参数：dest， ch 和 count。所代表的字符ch 首先转换为无符号字符，然后将其复制到第一个count 指向的对象的字符 dest。


示例：memset（）函数的工作方式
#include <cstring>
#include <iostream>

using namespace std;

int main()
{
    char dest[50];
    char ch = 'a';
    memset(dest, ch, 20);

    cout << "After calling memset" << endl;
    cout << "dest contains " << dest; 
    return 0;
}
运行该程序时，输出为：

调用memset之后
目标包含aaaaaaaaaaaaaaaaaaaaaa
**欢迎关注**