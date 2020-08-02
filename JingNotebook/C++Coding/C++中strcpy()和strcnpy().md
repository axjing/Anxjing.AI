<!--
 * @Author: Anxjing.AI
 * @Date: 2020-08-01 19:49:54
 * @LastEditTime: 2020-08-02 11:07:38
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\C++Coding\C++中strcpy()和strcnpy().md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
--> 
# C ++ strcpy（）
C ++中的strcpy（）函数将字符串从源复制到目标。
strcpy（）原型
```
char * strcpy（char * dest，const char * src）;
```
该strcpy()函数有两个参数：dest和src。它将src指向的字符串复制到dest指向的存储位置。空终止符也会被复制。

在以下情况下，行为是不确定的：

为dest指针分配的内存不够大。
字符串重叠。
它在<cstring>头文件中定义。
```
strcpy（）参数
dest：指向内容复制到的字符数组的指针。
src：指向从中复制内容的字符数组的指针。
strcpy（）返回值
strcpy（）函数返回目标的指针dest。
```
示例：strcpy（）函数的工作方式
```C++
#include <cstring>
#include <iostream>

using namespace std;

int main()
{
    char src[] = "Hello AnxJing.AI!!!";
    
    /* Large enough to store content of src */
    char dest[20];
    
    strcpy(dest,src);
    cout << dest;
    return 0;
}
```
运行该程序时，输出为：
```
Hello AnxJing.AI!!!
```

# C ++ strncpy（）
C ++中的strncpy（）函数将指定字节的字符从源字符复制到目标。
strncpy（）原型
```
char * strncpy（char * dest，const char * src，size_t count）;
```
该strncpy()函数接受三个参数：dest，src和count。它将最多计数字符从指向的字符串复制到src指向的存储位置dest。

如果计数小于长度 src，将第一个字符复制到dest并且它不是以null终止的。如果count大于长度 src，将src中的所有字符复制到dest并添加其他终止空字符，直到总共写入了计数字符为止。

如果字符串重叠，则行为未定义。

它在<cstring>头文件中定义。
```
strncpy（）参数
dest：指向内容复制到的字符数组的指针。
src：指向从中复制内容的字符数组的指针。
count：要复制的最大字符数。
strncpy（）返回值
strncpy（）函数返回目标目标块的指针dest。
```
示例：strncpy（）函数的工作方式
```C++
#include <cstring>
#include <iostream>

using namespace std;

int main()
{
    char src[] = "It's Monday and it's raining";
    char dest[40];

    /* count less than length of src */
    strncpy(dest,src,10);
    cout << dest << endl;

    /* count more than length of src */
    strncpy(dest,src,strlen(src)+10);
    cout << dest << endl;
    return 0;
}
```
运行该程序时，输出为：
```
It's Monday
It's Monday and it's raining
```

参考资料：
学习C++手记，整理多篇资源；侵删

https://www.programiz.com/cpp-programming/library-function/cstring/strcpy
