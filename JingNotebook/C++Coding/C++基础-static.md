<!--
 * @Author: Anxjing.AI
 * @Date: 2020-08-06 09:56:51
 * @LastEditTime: 2020-08-07 17:15:09
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\C++Coding\C++基础-static.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
-->
# C++基础-static


## 写在前：C++内存的几个区：
1. 栈(stack)：由编译器自动分配释放，存放函数的参数值，局部变量的值（除static），其操作方式类似于数据结构中的栈。
2. 堆(heap)：一般由程序员分配释放，若程序员不释放，程序结束时可能由OS回收。注意它与数据结构中的堆(优先队列)是两回事，分配方式倒是类似于链表。
3. 全局区(静态区)：全局变量和静态变量的存储是放在一块的，初始化的全局变量和静态变量在一块区域，未初始化的全局变量和未初始化的静态变量在相邻的另一块区域(BSS)，程序结束后由系统释放。
4. 文字常量区：常量字符串就是放在这里的，如char str[]=”hello”，程序结束后由系统释放，区别const修饰的变量。
5. 程序代码区：存放函数体的二进制代码。


## 静态成员数据和静态成员函数

将数据成员声明为时 **`static`** ，只会为类的所有对象维护数据的一个副本。

静态数据成员不是给定的类类型的对象的一部分。 因此，静态数据成员的声明不被视为一个定义。 在类范围中声明数据成员，但在文件范围内执行定义。 这些静态类成员具有外部链接。如：

```cpp
// static_data_members.cpp
class BufferedOutput
{
public:
   // Return number of bytes written by any object of this class.
   short BytesWritten()
   {
      return bytecount;
   }

   // Reset the counter.
   static void ResetCount()
   {
      bytecount = 0;
   }

   // Static member declaration.
   static long bytecount;
};

// Define bytecount in file scope.
long BufferedOutput::bytecount;

int main()
{
}
```
该成员 `bytecount` 在类 `BufferedOutput` 中声明，但它必须在类声明的外部定义。

对于存在的静态成员，类类型的所有对象的存在则没有必要。 静态成员还可以使用成员选择（**.** 和 **->** ）运算符。 例如：

```cpp
BufferedOutput Console;

long nBytes = Console.bytecount;
```

在前面的示例中，不会评估对对象(`Console`) 的引用；返回的值是静态对象 `bytecount` 的值。

静态数据成员遵循类成员访问规则，因此只允许类成员函数和友元拥有对静态数据成员的私有访问权限。 例外情况是，无论静态数据成员的访问限制如何，都必须在文件范围内进行定义。 如果进行显式初始化数据成员，则必须使用定义提供初始值设定项。

静态成员的类型不是由其类名称限定的。 因此，的类型 `BufferedOutput::bytecount` 为 **`long`** 。

## static访问权限



[参考链接1](https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/cpp)

[参考衔接2](https://github.com/axjing/Anxjing.AI/blob/master/JingNotebook)