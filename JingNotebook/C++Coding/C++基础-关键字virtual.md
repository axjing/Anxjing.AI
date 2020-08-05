<!--
 * @Author: Anxjing.AI
 * @Date: 2020-08-05 15:12:29
 * @LastEditTime: 2020-08-05 19:09:22
 * @LastEditors: Anajing.AI
 * @Description: 
 * @FilePath: \Anxjing.AI\JingNotebook\C++Coding\C++基础-关键字virtual.md
 * @THIS FILE IS PART OF Anxjing.AI PROJECT
--> 
# C++基础-关键字virtual

# virtual：虚函数说明符

virtual 说明符指定非静态成员函数为虚函数并支持动态调用派发。它只能在非静态成员函数的首个声明（即当它于类定义中声明时）的 声明说明符序列 中出现。 
- 解释
虚函数是可在派生类中覆盖其行为的成员函数。与非虚函数相反，即使没有关于该类实际类型的编译时信息，仍然保留被覆盖的行为。当使用到基类的指针或引用来处理派生类时，对被覆盖的虚函数的调用，将会调用定义于派生类中的行为。当使用有限定名字查找（即函数名出现在作用域解析运算符 :: 的右侧）时，此行为被抑制。 

```C++
#include <iostream>
struct Base {
   virtual void f() {
       std::cout << "base\n";
   }
};
struct Derived : Base {
    void f() override { // 'override' 可选
        std::cout << "derived\n";
    }
};
int main()
{
    Base b;
    Derived d;
 
    // 通过引用调用虚函数
    Base& br = b; // br 的类型是 Base&
    Base& dr = d; // dr 的类型也是 Base&
    br.f(); // 打印 "base"
    dr.f(); // 打印 "derived"
 
    // 通过指针调用虚函数
    Base* bp = &b; // bp 的类型是 Base*
    Base* dp = &d; // dp 的类型也是 Base*
    bp->f(); // 打印 "base"
    dp->f(); // 打印 "derived"
 
    // 非虚函数调用
    br.Base::f(); // 打印 "base"
    dr.Base::f(); // 打印 "base"
}
```

*若某个成员函数 vf 在类 Base 中被声明为 virtual，且某个直接或间接派生于 Base 的类 Derived 拥有一个下列几项与之相同的成员函数声明 
名字 
形参列表（但非返回类型） 
cv 限定符 
引用限定符 
则类 Derived 中的此函数亦为虚函数（无论其声明中是否使用关键词 virtual）并覆盖 Base::vf（无论其声明中是否使用单词 override）。 
要覆盖的 Base::vf 不需要可见（可声明为 private，或用私有继承继承）。 
要覆盖的 Base::vf 不需要可访问或可见。（ Base::vf 能声明为 private ，或者能用私有继承继承 Base。 Derived 的基类中的任何同名成员不妨碍覆盖确定，即使在名字查找时它们会隐藏 Base::vf。）* 
```C++
class B {
    virtual void do_f(); // 私有成员
 public:
    void f() { do_f(); } // 公开接口
};
struct D : public B {
    void do_f() override; // 覆盖 B::do_f
};
 
int main()
{
    D d;
    B* bp = &d;
    bp->f(); // 内部调用 D::do_f();
}
```
*每个虚函数都有其最终覆盖函数，它是进行虚函数调用时所执行的函数。基类 Base 的虚成员函数 vf 是最终覆盖函数，除非派生类声明或（通过多重继承）继承了覆盖 vf 的另一个函数。 *
```C++ 
struct A { virtual void f(); };     // A::f 是虚函数
struct B : A { void f(); };         // B::f 覆盖 A::f in B
struct C : virtual B { void f(); }; // C::f 覆盖 A::f in C
struct D : virtual B {}; // D 不引入覆盖函数，B::f 在 D 中为最终
struct E : C, D  {       // E 不引入覆盖函数，C::f 在 E 中为最终
    using A::f; // 非函数声明，仅令 A::f 能为查找所见
};
int main() {
   E e;
   e.f();    // 虚调用调用 C::f，e 中的最终覆盖函数
   e.E::f(); // 非虚调用调用 A::f，它在 E 中可见
}
若一个函数拥有多于一个最终覆盖函数，则程序非良构： 
struct A {
    virtual void f();
};
struct VB1 : virtual A {
    void f(); // 覆盖 A::f
};
struct VB2 : virtual A {
    void f(); // 覆盖 A::f
};
// struct Error : VB1, VB2 {
//     // 错误：A::f 在 Error 中拥有两个最终覆盖函数
// };
struct Okay : VB1, VB2 {
    void f(); // OK：这是 A::f 的最终覆盖函数
};
struct VB1a : virtual A {}; // 不声明覆盖函数
struct Da : VB1a, VB2 {
    // Da 中，A::f 的最终覆盖函数是 VB2::f
};
```
具有相同名字但不同形参列表的函数并不覆盖同名的基类函数，但会隐藏它：在无限定名字查找检查派生类的作用域时，查找找到该声明而不再检查基类。 
```C++
struct B {
    virtual void f();
};
struct D : B {
    void f(int); // D::f 隐藏 B::f（错误的形参列表）
};
struct D2 : D {
    void f(); // D2::f 覆盖 B::f（它不可见也不要紧）
};
 
int main()
{
    B b;   B& b_as_b   = b;
    D d;   B& d_as_b   = d;    D& d_as_d = d;
    D2 d2; B& d2_as_b  = d2;   D& d2_as_d = d2;
 
    b_as_b.f(); // 调用 B::f()
    d_as_b.f(); // 调用 B::f()
    d2_as_b.f(); // 调用 D2::f()
 
    d_as_d.f(); // 错误：D 中的查找只找到 f(int)
    d2_as_d.f(); // 错误：D 中的查找只找到 f(int)
}
```
若函数以说明符 override 声明，但不覆盖任何虚函数，则程序非良构： 
```C++
struct B {
    virtual void f(int);
};
struct D : B {
    virtual void f(int) override; // OK，D::f(int) 覆盖 B::f(int)
    virtual void f(long) override; // 错误：f(long) 不覆盖 B::f(int)
};
若函数以说明符 final 声明，而另一函数试图覆盖之，则程序非良构： 
struct B {
    virtual void f() const final;
};
struct D : B {
    void f() const; // 错误：D::f 试图覆盖 final B::f
};
```

- 非成员函数和静态成员函数不能为虚函数。 
函数模板不能被声明为 virtual。这只适用于自身是模板的函数——类模板的常规成员函数可被声明为虚函数。 
虚函数（无论是声明为 virtual 者还是覆盖函数）不能有任何关联制约 ---C++11
```C++
struct A {
    virtual void f() requires true; // 错误：受制约的虚函数
};
```
- consteval 虚函数不能覆盖非 consteval 虚函数或被它覆盖。 
---C++20 在编译时替换虚函数的默认实参。 

- 协变返回类型

若函数 Derived::f 覆盖 Base::f，则其返回类型必须要么相同要么为协变（covariant）。当满足所有下列要求时，两个类型为协变： 
两个类型均为到类的指针或引用（左值或右值）。不允许多级指针或引用。 
Base::f() 的返回类型中被引用/指向的类，必须是 Derived::f() 的返回类型中被引用/指向的类的无歧义且可访问的直接或间接基类。 
Derived::f() 的返回类型必须有相对于 Base::f() 的返回类型的相等或较少的 cv 限定。 
Derived::f 的返回类型中的类必须要么是 Derived 自身，要么必须是于 Derived::f 声明点的某个完整类型。 
进行虚函数调用时，最终覆盖函数的返回类型被隐式转换成所调用的被覆盖函数的返回类型： 
```C++
class B {};
 
struct Base {
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual B* vf4();
    virtual B* vf5();
};
 
class D : private B {
    friend struct Derived; // Derived 中，B 是 D 的可访问基类
};
 
class A; // 前置声明的类是不完整类型
 
struct Derived : public Base {
    void vf1();    // 虚函数，覆盖 Base::vf1()
    void vf2(int); // 非虚函数，隐藏 Base::vf2()
//  char vf3();    // 错误：覆盖 Base::vf3，但具有不同且非协变的返回类型
    D* vf4();      // 覆盖 Base::vf4() 并具有协变的返回类型
//  A* vf5();      // 错误：A 是不完整类型
};
 
int main()
{
    Derived d;
    Base& br = d;
    Derived& dr = d;
 
    br.vf1(); // 调用 Derived::vf1()
    br.vf2(); // 调用 Base::vf2()
//  dr.vf2(); // 错误：vf2(int) 隐藏 vf2()
 
    B* p = br.vf4(); // 调用 Derived::vf4() 并将结果转换为 B*
    D* q = dr.vf4(); // 调用 Derived::vf4() 而不将结果转换为 B*
 
}
```
- 虚析构函数
虽然析构函数是不继承的，但若基类声明其析构函数为 virtual，则派生的析构函数始终覆盖它。这使得可以通过指向基类的指针 delete 动态分配的多态类型对象 
```C++
class Base {
 public:
    virtual ~Base() { /* 释放 Base 的资源 */ }
};
 
class Derived : public Base {
    ~Derived() { /* 释放 Derived 的资源 */ }
};
 
int main()
{
    Base* b = new Derived;
    delete b; // 进行对 Base::~Base() 的虚函数调用
              // 由于它是虚函数，故它调用的是 Derived::~Derived()，
              // 这就能释放派生类的资源，然后遵循通常的析构顺序
              // 调用 Base::~Base()
}
```

- 若类是多态的（声明或继承了至少一个虚函数），且其析构函数非虚，则删除它是未定义行为，无论不调用派生的析构函数时是否会导致资源泄漏。 
一条有用的方针是，任何基类的析构函数必须为公开且虚，或受保护且非虚。 
在构造和析构期间，当从构造函数或从析构函数中直接或间接调用虚函数（包括在类的非静态数据成员的构造或析构期间，例如在成员初始化器列表中），且对其实施调用的对象是正在构造或析构中的对象时，所调用的函数是构造函数或析构函数的类中的最终覆盖函数，而非进一步的派生类中的覆盖函数。 换言之，在构造和析构期间，进一步的派生类并不存在。
 
- 当构建具有多个分支的复杂类时，在属于一个分支的构造函数内，多态被限制到该类及其基类：若它获得了指向这个子层级之外的某个基类子对象的指针或引用，且试图进行虚函数调用（例如通过显式成员访问），则行为未定义： 
```C++
struct V {
    virtual void f();
    virtual void g();
};
 
struct A : virtual V {
    virtual void f(); // A::f 是 V::f 在 A 中的最终覆盖函数
};
struct B : virtual V {
    virtual void g(); // B::g 是 V::g 在 B 中的最终覆盖函数
    B(V*, A*);
};
struct D : A, B {
    virtual void f(); // D::f 是 V::f 在 D 中的最终覆盖函数
    virtual void g(); // D::g 是 V::g 在 D 中的最终覆盖函数
 
    // 注意：A 在 B 之前初始化
    D() : B((A*)this, this) 
    {
    }
};
 
// B 的构造函数，从 D 的构造函数调用 
B::B(V* v, A* a)
{
    f(); // 对 V::f 的虚调用（尽管 D 拥有最终覆盖函数，D 也不存在）
    g(); // 对 B::g 的虚调用，在 B 中是最终覆盖函数
 
    v->g(); // v 的类型 V 是 B 的基类，虚调用如前调用 B::g
 
    a->f(); // a 的类型 A 不是 B 的基类，它属于层级中的不同分支。
            // 尝试通过这个分支进行虚调用导致未定义行为，
            // 即使此情况下 A 已完成构造
            // （它在 B 之前构造，因为它在 D 的基类列表中先于 B 出现）
            // 实践中，对 A::f 的虚调用会试图使用 B 的虚成员函数表，
            // 因为它在 B 的构造期间是活跃的
}
```

# virtual：虚基类说明符

任何类类型（无论是以 类关键词 class 还是 struct 声明者）均可被声明为派生于一或多个基类，各基类也可以派生自其自身的基类，组成继承层级结构。 
基类的列表在类声明语法的 基类子句 中提供。基类子句 由字符 : 后随一或多个 基类说明符 的逗号分隔列表组成。 

```
attr(可选) ccess-specifier((可选) virtual-specifier(可选) class-or-decltype
attr(C++11) - 可选的任何数量属性的序列 
ccess-specifier - private、public 或 protected 之一 
virtual-specifier - 关键词 virtual 
ccess-specifier 与 virtual-specifier 可以任意顺序出现 
基类子句 中的 基类说明符 可以是包展开。 
声明为 final 的 class 或 struct 不能出现于 基类子句 中。 
(C++11 起)
若省略 访问说明符，则它对以类关键词 struct 声明的类默认为 public，对以类关键词 class 声明的类为 private。
 ```
```C++
struct Base {
    int a, b, c;
};
// 每个 Derived 类型对象包含 Base 为子对象
struct Derived : Base {
    int b;
};
// 每个 Derived2 类型对象包含 Derived 与 Base 为子对象
struct Derived2 : Derived {
    int c;
};
```
- 列于 基类子句 中的类是直接基类。它们的基类是间接基类。同一类不能被多次指定为直接基类，但同一类可以既是直接又是间接基类。 
每个直接和间接基类都作为基类子对象，以实现定义的偏移量存在于派生类的对象表示中。因为空基类优化，空基类通常不会增加派生类对象的大小。基类子对象的构造函数被派生类的构造函数所调用：可在成员初始化器列表中向这些构造函数提供实参。 
虚基类
对于每个指定为 virtual 的不同基类，最终派生对象中仅含有该类型的一个基类子对象，即使该类在继承层级中出现多次也是如此（只要它每次都以 virtual 继承）。 
```C++
struct B { int n; };
class X : public virtual B {};
class Y : virtual public B {};
class Z : public B {};
// 每个 AA 类型对象拥有一个 X，一个 Y，一个 Z 和两个 B：
// 其一是 Z 的基类，另一者为 X 与 Y 所共享
struct AA : X, Y, Z {
    void f() {
        X::n = 1; // 修改虚 B 子对象的成员
        Y::n = 2; // 修改同一虚 B 子对象的成员
        Z::n = 3; // 修改非虚 B 子对象的成员
 
        std::cout << X::n << Y::n << Z::n << '\n'; // 打印 223
    }
};
```
- 继承层级有虚基类的例子之一是标准库的 iostream 的继承层级：std::istream 与 std::ostream 使用虚继承从 std::ios 派生。std::iostream 同时派生于 std::istream 和 std::ostream，故每个 std::iostream 实例含一个 std::ostream 子对象、一个 std::istream 子对象和仅一个 std::ios 子对象（因而有一个 std::ios_base）。 
所有虚基类子对象都在任何非虚基类子对象之前初始化，故只有最终派生类会在其成员初始化器列表中调用虚基类的构造函数： 
```C++
struct B {
    int n;
    B(int x) : n(x) {}
};
struct X : virtual B { X() : B(1) {} };
struct Y : virtual B { Y() : B(2) {} };
struct AA : X, Y     { AA() : B(3), X(), Y() {} };
 
// AA 的默认构造函数调用 X 和 Y 的默认构造函数
// 但这些构造函数不调用 B 的构造函数，因为 B 是虚基类
AA a; // a.n == 3
// X 的默认构造函数调用 B 的构造函数
X x; // x.n == 1
```
## 涉及虚继承时，
对类成员的无限定名字查找有特殊规则（有时被称为“优先性（dominance）规则”），见 unqualified_lookup#成员函数的定义。 
- 公开继承

当类使用 public 成员访问说明符从基类派生时，基类的所有公开成员可作为派生类的公开成员访问，基类的所有受保护成员可作为派生类的受保护成员访问（基类的私有成员始终不可访问，除非设为友元）。 
公开继承塑造了面向对象编程的子类型关系：派生类对象是（IS-A）基类对象。到派生类对象的引用和指针，可被期待到其任何公开基类的引用和指针的代码所用（见 LSP），或者以 DbC 的说法，派生类应该维护其公开基类的类不变式，不应强化其所覆盖的成员函数的任何前条件，或弱化其任何后条件。 

- 受保护继承

当类使用 protected 成员访问说明符从基类派生时，基类的所有公开和受保护成员可作为派生类的受保护成员访问（基类的私有成员始终不可访问，除非设为友元）。 
受保护继承可用于“受控制的多态”：在派生类的成员中，以及所有进一步派生的类的成员中，派生类是（IS-A）基类：到派生类的引用和指针可用于期待到基类的引用和指针处。 
- 私有继承

当类使用 private 成员访问说明符从基类派生时，基类的所有公开和受保护成员可作为派生类的私有成员访问（基类的私有成员始终不可访问，除非设为友元）。 
私有继承常用于基于策略的设计，因为策略常是空基类，而使用基类可以同时启用静多态并活用空基类优化 
私有继承亦可用于实现合成关系（基类子对象是派生类对象的实现细节）。除非派生类需要访问基类的受保护成员（包含构造函数），需要覆盖基类的虚成员，需要基类在某个其他基类子对象之前构造或在其之后销毁，需要共享虚基类或需要控制虚基类的构造，否则使用成员方案可以提供更好的封装，而且通常是更受偏好的方式。使用成员来实现合成关系，亦不适用于从参数包进行多重继承的情况，或在编译时通过模板元编程确定各基类身份的情况。 
与受保护继承相似，私有继承亦可用于受控制的多态：在派生类的成员内（但不在进一步派生的类中），派生类是（IS-A）基类。 
```C++
template<typename Transport>
class service : private Transport  // 从 Transport 策略私有继承
{
public:
    void transmit() {
        this->send(...);  // 使用 Transport 提供的任何东西进行发送
    }
};
// TCP 传输策略
class tcp {
public:
    void send(...);
};
// UDP 传输策略
class udp {
public:
    void send(...);
};
 
service<tcp> service(host, port); 
service.transmit(...); // 通过 TCP 发送
```
成员名字查找
针对类成员进行的无限定和有限定的名字查找规则。 