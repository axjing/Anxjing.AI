<!--
 * @Author: Anxjing.AI
 * @Date: 2020-09-01 09:17:51
 * @LastEditTime: 2020-09-01 14:00:14
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\C++Coding\C++预处理指令.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
-->
# C++预处理指令
C语言、C++语言的预处理器。用于在编译器处理程序之前预扫描源代码，完成头文件的包含, 宏扩展, 条件编译, 行控制（line control）等操作

## 编译的四个阶段
C语言标准规定，预处理是指前4个编译阶段（phases of translation）。
1. 三字符组与双字符组的替换
1. 行拼接（Line splicing）: 把物理源码行（Physical source line）中的换行符转义字符处理为普通的换行符，从而把源程序处理为逻辑行的顺序集合。
1. 单词化（Tokenization）: 处理每行的空白、注释等，使每行成为token的顺序集。
1. 扩展宏与预处理指令（directive）处理.

## 包含头文件
```cpp
#include <stdio.h>

```

## 条件编译
```cpp
#if VERBOSE >= 2
  print("trace message");
#endif

#ifdef __unix__ /* __unix__ is usually defined by compilers targeting Unix systems */
# include <unistd.h>
#elif defined _WIN32 /* _WIN32 is usually defined by compilers targeting 32 or 64 bit Windows systems */
# include <windows.h>
#endif



#if !(defined __LP64__ || defined __LLP64__) || defined _WIN32 && !defined _WIN64
	// we are compiling for a 32-bit system
#else
	// we are compiling for a 64-bit system
#endif
```

## 宏定义与扩展
- 类似对象的宏（无参数的宏）
- 类似函数的宏（带参数的宏），在第一个标识符与左括号之间，绝不能有空格。
- 
```cpp
#define <identifier> <replacement token list>                    // object-like macro
#define <identifier>(<parameter list>) <replacement token list>  // function-like macro, note parameters


#undef <identifier>                                              // delete the macro
```

[来源维基百科](https://zh.wikipedia.org/wiki/C%E9%A2%84%E5%A4%84%E7%90%86%E5%99%A8)

## 特殊宏与指令
__FILE__ 与 __LINE__, 扩展为当前文件与行号。例如:
```cpp
// debugging macros so we can pin down message origin at a glance
#define WHERESTR  "[file %s, line %d]: "
#define WHEREARG  __FILE__, __LINE__
#define DEBUGPRINT2(...)       fprintf(stderr, __VA_ARGS__)
#define DEBUGPRINT(_fmt, ...)  DEBUGPRINT2(WHERESTR _fmt, WHEREARG, __VA_ARGS__)
//...

  DEBUGPRINT("hey, x=%d\n", x);
C或C++语言标准定义了宏： __STDC__, __STDC_VERSION__, __cplusplus,__DATE__,__TIME__,__func__等。
```
## 常见预处理指令
```cpp
#空指令，//无任何效果
#include    //包含一个源代码文件
#define    //定义宏
#undef    //取消已定义的宏
#if    //如果给定条件为真，则编译下面代码
#ifdef    //如果宏已经定义，则编译下面代码
#ifndef    //如果宏没有定义，则编译下面代码
#elif    //如果前面的#if给定条件不为真，当前条件为真，则编译下面代码
#endif    //结束一个#if……#else条件编译块
#error    //停止编译并显示错误信息
```