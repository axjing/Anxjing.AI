<!--
 * @Author: Anxjing.AI
 * @Date: 2020-08-05 19:36:50
 * @LastEditTime: 2020-08-11 11:30:28
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\C++Coding\C++基础-函数重载.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
--> 
# 函数重载


## 函数重载示例：
以下代码演示了文件范围内的 print 函数重载。

默认参数不被视为函数类型的一部分。 因此，它不用于选择重载函数。 仅在默认自变量上存在差异的两个函数被视为多个定义而不是重载函数。

不能为重载运算符提供默认参数。
```C++
// function_overloading.cpp
// compile with: /EHsc
#include <iostream>
#include <math.h>
#include <string>

// Prototype three print functions.
int print(std::string s);             // Print a string.
int print(double dvalue);            // Print a double.
int print(double dvalue, int prec);  // Print a double with a
                                     //  given precision.
using namespace std;
int main(int argc, char *argv[])
{
    const double d = 893094.2987;
    if (argc < 2)
    {
        // These calls to print invoke print( char *s ).
        print("This program requires one argument.");
        print("The argument specifies the number of");
        print("digits precision for the second number");
        print("printed.");
        exit(0);
    }

    // Invoke print( double dvalue ).
    print(d);

    // Invoke print( double dvalue, int prec ).
    print(d, atoi(argv[1]));
}

// Print a string.
int print(string s)
{
    cout << s << endl;
    return cout.good();
}

// Print a double in default precision.
int print(double dvalue)
{
    cout << dvalue << endl;
    return cout.good();
}

//  Print a double in specified precision.
//  Positive numbers for precision indicate how many digits
//  precision after the decimal point to show. Negative
//  numbers for precision indicate where to round the number
//  to the left of the decimal point.
int print(double dvalue, int prec)
{
    // Use table-lookup for rounding/truncation.
    static const double rgPow10[] = {
        10E-7, 10E-6, 10E-5, 10E-4, 10E-3, 10E-2, 10E-1,
        10E0, 10E1,  10E2,  10E3,  10E4, 10E5,  10E6 };
    const int iPowZero = 6;

    // If precision out of range, just print the number.
    if (prec < -6 || prec > 7)
    {
        return print(dvalue);
    }
    // Scale, truncate, then rescale.
    dvalue = floor(dvalue / rgPow10[iPowZero - prec]) *
        rgPow10[iPowZero - prec];
    cout << dvalue << endl;
    return cout.good();
}
```
- 解释：C++ 允许同一范围内具有相同名称的多个函数的规范。 这些函数称为重载函数。 重载函数使你能够为函数提供不同的语义，具体取决于参数的类型和数量。

*如， print 采用 std::string 自变量的函数执行的任务可能与使用类型的参数的任务不同 double 。 重载使您无需使用名称（如 print_string 或） print_double 。 在编译时，编译器根据调用方传入的参数类型选择要使用的重载。 如果调用 print(42.0) ，则 void print(double d) 将调用函数。 如果调用 print("hello world") ，则 void print(std::string) 将调用此重载。*

可以重载成员函数和非成员函数。 下表显示了 C++ 使用函数声明的哪些部分来区分同一范围内具有相同名称的函数组。

**重载注意事项**
函数声明元素	是否用于重载？
函数返回类型	否
自变量的数量	是
自变量的类型	是
省略号存在或缺失	是
名称的使用 typedef	否
未指定的数组边界	否
const 或 volatile	是，应用于整个函数时
引用限定符	是

## 自变量匹配
选择重载函数以实现当前范围内的函数声明与函数调用中提供的参数的最佳匹配。 如果找到合适的函数，则调用该函数。 在此上下文中，"合适" 是指：
- 找到完全匹配项。
- 已执行不重要的转换。
- 已执行整型提升。
- 已存在到所需自变量类型的标准转换。
- 已存在到所需参数类型的用户定义的转换（转换运算符或构造函数）。
- 已找到省略号所表示的自变量。
编译器为每个自变量创建一组候选函数。 候选函数是这样一种函数，其中的实际自变量可以转换为形式自变量的类型。

为每个自变量生成一组“最佳匹配函数”，并且所选函数是所有集的交集。 如果交集包含多个函数，则重载是不明确的并会生成错误。 对于至少一个自变量而言，最终选择的函数始终是比组中的所有其他函数更好的匹配项。 如果没有明确入选方，则函数调用会生成错误。

考虑下面的声明（针对下面的讨论中的标识，将函数标记为 Variant 1、Variant 2 和 Variant 3）：
```C++
Fraction &Add( Fraction &f, long l );       // Variant 1
Fraction &Add( long l, Fraction &f );       // Variant 2
Fraction &Add( Fraction &f, Fraction &f );  // Variant 3

Fraction F1, F2;
//请考虑下列语句：

F1 = Add( F2, 23 );
```

前面的语句生成两个集：

|集 1：其第一个自变量的类型为 Fraction 的候选函数|设置2：可将第二个参数转换为类型的候选函数**`int`**|
|--------------------------------------------------------------------------|-----------------------------------------------------------------------------------|
|Variant 1|变体1（ **`int`** 可以 **`long`** 使用标准转换转换为）|
|Variant 3||

集2中的函数是指具有从实参类型到形参类型的隐式转换的函数，在此类函数中有一个函数，将实参类型转换为其形参类型的 "成本" 是最小的。

这两个集的交集为 Variant 1。 不明确的函数调用的示例为：
```C++
F1 = Add( 3, 6 );
```
前面的函数调用生成以下集：

|集1：具有类型为的第一个参数的候选函数**`int`**|集2：具有类型为的第二个参数的候选函数**`int`**|
|---------------------------------------------------------------------|----------------------------------------------------------------------|
|变体2（ **`int`** 可以 **`long`** 使用标准转换转换为）|变体1（ **`int`** 可以 **`long`** 使用标准转换转换为）|

由于这两个集的交集为空，因此编译器将生成错误消息。

对于参数匹配，具有n个默认参数的函数被视为n+ 1 个单独函数，每个函数都有不同数目的参数。

省略号 (...) 用作通配符；它与任何自变量匹配。 如果不想要非常小心地设计重载函数集，它可能会导致许多不明确的集。

> 在遇到函数调用之前，不能确定重载函数的歧义。 此时，将为函数调用中的每个自变量生成集，并且可以确定是否存在明确的重载。 这意味着，多义性可保持在你的代码中，直到它们由特定函数调用引发。

## 参数类型差异
重载函数区分使用不同的初始值设定项的自变量类型。 因此，对于重载而言，给定类型的自变量和对该类型的引用将视为相同。 由于它们采用相同的初始值设定项，因此它们被视为是相同的。 例如，max( double, double ) 被视为与 max( double &, double & ) 相同。 声明两个此类函数会导致错误。

出于相同的原因，由或修改的类型的函数自变量的 const volatile 处理方式与用于重载的基类型的处理方式不同。

但是，函数重载机制可以区分由和限定的引用 const volatile 以及对基类型的引用。 它可以实现如下所示的代码：
```C++
// argument_type_differences.cpp
// compile with: /EHsc /W3
// C4521 expected
#include <iostream>

using namespace std;
class Over {
public:
   Over() { cout << "Over default constructor\n"; }
   Over( Over &o ) { cout << "Over&\n"; }
   Over( const Over &co ) { cout << "const Over&\n"; }
   Over( volatile Over &vo ) { cout << "volatile Over&\n"; }
};

int main() {
   Over o1;            // Calls default constructor.
   Over o2( o1 );      // Calls Over( Over& ).
   const Over o3;      // Calls default constructor.
   Over o4( o3 );      // Calls Over( const Over& ).
   volatile Over o5;   // Calls default constructor.
   Over o6( o5 );      // Calls Over( volatile Over& ).
}
```
输出
```output
Over default constructor
Over&
Over default constructor
const Over&
Over default constructor
volatile Over&
```
在 const 重载时，指向和对象的指针 volatile 也被视为不同于基类型的指针。

## 自变量匹配和转换
当编译器尝试根据函数声明中的参数匹配实际参数时，如果未找到任何确切匹配项，它可以提供标准转换或用户定义的转换来获取正确类型。 转换的应用程序受这些规则的限制：

- 不考虑包含多个用户定义的转换的转换序列。

- 不考虑可通过删除中间转换来缩短的转换序列。

最终的转换序列（如果有）称为最佳匹配序列。 可以通过多种方式使用标准转换将类型的对象转换 **`int`** 为类型 **`unsigned long`** （如[标准转换](../cpp/standard-conversions.md)中所述）：

- 从转换 **`int`** 到 **`long`** ，然后从转换为 **`long`** **`unsigned long`** 。

- 从转换 **`int`** 为 **`unsigned long`** 。

第一个序列（虽然它实现了所需的目标）不是最佳匹配顺序，但存在较短的序列。

下表显示了一组称为常用转换的转换，这些转换对确定哪个序列是最佳匹配项有一定的限制。 该表后面的列表中讨论了常用转换影响序列选择的实例。

### 常用转换

|从类型转换|转换为类型|
|-----------------------|---------------------|
|*类型名称*|*类型名称***&**|
|*类型名称***&**|*类型名称*|
|*类型名称* **[]**|*类型名称*__\*__|
|*类型名称* **（** *参数列表* **）**|**（** __\*__ *类型名称* **）（** *参数列表* **）**|
|*类型名称*|**`const`***类型名称*|
|*类型名称*|**`volatile`***类型名称*|
|*类型名称*__\*__|**`const`***类型名称*__\*__|
|*类型名称*__\*__|**`volatile`***类型名称*__\*__|

在其中尝试转换的序列如下：

1. 完全匹配。 用于调用函数的类型与函数原型中声明的类型之间的完全匹配始终是最佳匹配。 常用转换的序列将归类为完全匹配。 但是，不进行任何转换的序列被认为比转换的序列更好：

   - 从指针，到指向 **`const`** （ `type` <strong>\*</strong> 到 **`const`** `type` <strong>\*</strong> ）的指针。

   - 从指针，到指向 **`volatile`** （ `type` <strong>\*</strong> 到 **`volatile`** `type` <strong>\*</strong> ）的指针。

   - 从引用，到对 **`const`** （ `type` **&** 到 **`const`** `type` **&** ）的引用。

   - 从引用，到对 **`volatile`** （ `type` **&** 到 **`volatile`** `type` **&** ）的引用。

1. 使用提升的匹配。 任何未分类为仅包含整数升级、从到的转换 **`float`** **`double`** 和普通转换的序列都分类为使用提升的匹配项。 尽管比不上完全匹配，但使用提升的匹配仍优于使用标准转换的匹配。

1. 使用标准转换的匹配。 未归类为完全匹配或仅包含标准转换和常用转换的使用提升的匹配的序列将归类为使用标准转换的匹配。 在此类别中，以下规则将适用：

   - 从指向派生类的指针转换为指向直接或间接基类的指针，更适合转换为 `void *` 或 `const void *` 。

   - 从指向派生类的指针到指向基类的指针的转换会产生一个到直接基类的更好匹配。


如果内置提升或转换不存在，则用户定义的转换将适用。 基于将匹配的自变量的类型选择这些转换。 考虑下列代码：
```C++
// argument_matching1.cpp
class UDC
{
public:
   operator int()
   {
      return 0;
   }
   operator long();
};

void Print( int i )
{
};

UDC udc;

int main()
{
   Print( udc );
}
```
类的可用用户定义的转换 UDC 来自类型 int 和类型 long 。 因此，编译器会考虑针对将匹配的对象类型的转换：UDC。 转换为 int exists，并选中它。

在匹配参数的过程中，标准转换可应用于参数和用户定义的转换的结果。 因此，下面的代码将适用：
```C++
void LogToFile( long l );
...
UDC udc;
LogToFile( udc );
```
## <a name="argument-matching-and-the-this-pointer"></a>参数匹配和 this 指针

类成员函数的处理方式不同，具体取决于它们是否声明为 **`static`** 。 由于非静态函数具有提供指针的隐式参数，因此将 **`this`** 非静态函数视为具有比静态函数更多的参数; 否则，其声明方式是相同的。

这些非静态成员函数要求隐含的 **`this`** 指针与通过其调用函数的对象类型匹配，或者对于重载运算符，它们要求第一个参数与要对其应用运算符的对象匹配。 （有关重载运算符的详细信息，请参阅[重载运算符](../cpp/operator-overloading.md)。）

与重载函数中的其他参数不同，在尝试匹配指针参数时，不会引入临时对象，也不会尝试转换 **`this`** 。

当 `->` 使用成员选择运算符访问类的成员函数时 `class_name` ， **`this`** 指针参数具有类型 `class_name * const` 。 如果将成员声明为 **`const`** 或 **`volatile`** ，则类型分别为 `const class_name * const` 和 `volatile class_name * const` 。

`.` 成员选择运算符以相同的方式工作，只不过隐式 `&` (address-of) 运算符将成为对象名称的前缀。 下面的示例演示了此工作原理：

```cpp
// Expression encountered in code
obj.name

// How the compiler treats it
(&obj)->name
```

处理 `->*` 和 `.*`（指向成员的指针）运算符的左操作数的方式与处理与参数匹配相关的 `.` 和 `->`（成员选择）运算符的方式相同。

## <a name="ref-qualifiers-on-member-functions"></a><a name="ref-qualifiers"></a>成员函数的 Ref 限定符

通过引用限定符，可以根据指向的对象 **`this`** 是右值还是左值，来重载成员函数。  当你选择不提供对数据的指针访问权限时，可以使用此功能来避免不必要的复制操作。 例如，假设类 `C` 在其构造函数中初始化某些数据，并在成员函数中返回该数据的副本 `get_data()` 。 如果类型为的对象 `C` 是要销毁的右值，则编译器将选择 `get_data() &&` 重载，这会移动数据而不是复制数据。

```cpp
#include <iostream>
#include <vector>

using namespace std;

class C
{

public:
    C() {/*expensive initialization*/}
    vector<unsigned> get_data() &
    {
        cout << "lvalue\n";
        return _data;
    }
    vector<unsigned> get_data() &&
    {
        cout << "rvalue\n";
        return std::move(_data);
    }

private:
    vector<unsigned> _data;
};

int main()
{
    C c;
    auto v = c.get_data(); // get a copy. prints "lvalue".
    auto v2 = C().get_data(); // get the original. prints "rvalue"
    return 0;
}
```

## 重载、重写和隐藏

同一范围内具有同一名称的任何两个函数声明都可以引用同一函数或重载的两个不同的函数。 如果声明的自变量列表包含等效类型的自变量（如上一节所述），函数声明将引用同一函数。 否则，它们将引用使用重载选择的两个不同的函数。

严格遵守类范围;因此，在基类中声明的函数与派生类中声明的函数不在同一范围内。 如果使用与基类中的虚函数相同的名称声明派生类中的函数，则派生类函数会*重写*基类函数。 有关详细信息，请参阅[虚拟函数](../cpp/virtual-functions.md)。

如果基类函数未被声明为 "virtual"，则认为派生类函数*隐藏*它。 重写和隐藏与重载不同。

严格观察到块范围;因此，在文件范围中声明的函数与在本地声明的函数不在同一范围内。 如果在本地声明的函数与在文件范围中声明的函数具有相同名称，则在本地声明的函数将隐藏文件范围内的函数而不是导致重载。 例如：

```cpp
// declaration_matching1.cpp
// compile with: /EHsc
#include <iostream>

using namespace std;
void func( int i )
{
    cout << "Called file-scoped func : " << i << endl;
}

void func( char *sz )
{
   cout << "Called locally declared func : " << sz << endl;
}

int main()
{
   // Declare func local to main.
   extern void func( char *sz );

   func( 3 );   // C2664 Error. func( int ) is hidden.
   func( "s" );
}
```

前面的代码显示函数 `func` 中的两个定义。 由于语句，采用类型的自变量的定义 `char *` 是的本地定义 `main` **`extern`** 。 因此，采用类型的参数的定义 **`int`** 是隐藏的，而对的第一次调用 `func` 是错误的。

对于重载的成员函数，不同版本的函数可能获得不同的访问权限。 它们仍被视为在封闭类的范围内，因此是重载函数。 请考虑下面的代码，其中的成员函数 `Deposit` 将重载；一个版本是公共的，另一个版本是私有的。

此示例的目的是提供一个 `Account` 类，其中需要正确的密码来执行存款。 这是通过使用重载来完成的。

对中的的调用将 `Deposit` `Account::Deposit` 调用私有成员函数。 此调用是正确 `Account::Deposit` 的，因为是成员函数，并且有权访问类的私有成员。

```cpp
// declaration_matching2.cpp
class Account
{
public:
   Account()
   {
   }
   double Deposit( double dAmount, char *szPassword );

private:
   double Deposit( double dAmount )
   {
      return 0.0;
   }
   int Validate( char *szPassword )
   {
      return 0;
   }

};

int main()
{
    // Allocate a new object of type Account.
    Account *pAcct = new Account;

    // Deposit $57.22. Error: calls a private function.
    // pAcct->Deposit( 57.22 );

    // Deposit $57.22 and supply a password. OK: calls a
    //  public function.
    pAcct->Deposit( 52.77, "pswd" );
}

double Account::Deposit( double dAmount, char *szPassword )
{
   if ( Validate( szPassword ) )
      return Deposit( dAmount );
   else
      return 0.0;
}
```

## <a name="restrictions-on-overloading"></a>重载限制

多个限制管理可接受的重载函数集：

- 重载函数集内的任意两个函数必须具有不同的参数列表。

- 仅基于返回类型重载具有相同类型的参数列表的函数是错误的



[参考链接1](https://docs.microsoft.com/en-us/cpp/cpp/welcome-back-to-cpp-modern-cpp?view=vs-2019)

[参考衔接2](https://github.com/axjing/Anxjing.AI/blob/master/JingNotebook)