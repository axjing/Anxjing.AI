<!--
 * @Author: Anxjing.AI
 * @Date: 2020-08-06 09:56:51
 * @LastEditTime: 2020-08-06 09:58:16
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\C++Coding\C++基础-static.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
-->
# C++基础-static




## C++内存的几个区：
1. 栈(stack)：由编译器自动分配释放，存放函数的参数值，局部变量的值（除static），其操作方式类似于数据结构中的栈。
2. 堆(heap)：一般由程序员分配释放，若程序员不释放，程序结束时可能由OS回收。注意它与数据结构中的堆(优先队列)是两回事，分配方式倒是类似于链表。
3. 全局区(静态区)：全局变量和静态变量的存储是放在一块的，初始化的全局变量和静态变量在一块区域，未初始化的全局变量和未初始化的静态变量在相邻的另一块区域(BSS)，程序结束后由系统释放。
4. 文字常量区：常量字符串就是放在这里的，如char str[]=”hello”，程序结束后由系统释放，区别const修饰的变量。
5. 程序代码区：存放函数体的二进制代码。