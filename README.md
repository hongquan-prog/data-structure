# 数据结构

## 一、算法的时间复杂度

判断一个算法的效率时，操作数量的常数项和其他次要项可以省略，只需要关注最高阶项即可

### 1.1算法的复杂度

- 时间复杂度
  - 算法运行后对时间需求量的定性描述
- 空间复杂度
  - 算法运行后对空间需求量的定性描述

注：数据结构课程关注的是算法的效率问题，因此会集中讨论算法的时间复杂度，但是使用的方法

### 1.2大O表示法

- 算法效率严重依赖操作
- 操作数量的估算可以作为时间复杂度的估算
- 在判断时首先关注操作数量的最高次项
- O(5) = O(1)
- O(2n + 1) = O(2n) = O(n)
- O(n^2 + n + 1) = O(n^2)
- O(n^3+1) = O(n^3)

### 1.3常见时间复杂度

- 时间复杂度为O(n)

``` c++
for(int i = 0; i < n; i++)
{
    //复杂度为O(1)的操作
}
//循环n次
```

- 对数阶的时间复杂度O(logn)

``` c++
int i = 1;
while(i < n)
{
    //复杂度为O(1)的操作
    i = i * 2;
}
//循环log2^n次
```

- 平方阶的时间复杂度O(n^2)

``` c++
for(int i = 0; i < n; i++)
{
    for(int j = 0; j < n; j++)
    {
    //复杂度为O(1)的操作
    }
}
//循环n^2次
```

- 下面这段代码的时间复杂度为多少

``` c++
for(int i = 0; i < n; i++)
{
    for(int j = i; j < n; j++)
    {
    //复杂度为O(1)的操作
    }
}
//循环((n + 1) * n)/2次
//O(n^2)
```

- 函数func的时间复杂度是多少

``` c++
void func(int n)
{
    int i = 0;
    while(i < n) // n
    {
        t(n); // n + 1
        i++
    }
}

void t(int n)
{
    int i = 0;

    while(i < n)
    {
        cout << i << endl;
        i++;
    }
}
//循环了n * (n + 1) 次
//O(n^2)
```

### 1.4总结

- 时间复杂度是算法运行时对时间的需求量
- 大O表示法用于描述算法的时间复杂度
- 大O表示法只关注操作数量的最高次项
- 常见的时间复杂度:线性阶，平方阶，对数阶

## 二、算法效率的度量

### 2.1常见的时间复杂度

| 操作数量示例 | 大O表示法 | 术语 |
|------------|----------|------|
| 15 | $\color{#00FF00}{O(1)}$ | 常数阶 |
| 3log2^n | $\color{#00FF00}{O(logn)}$ | 对数阶 |
| 3n + 5 | $\color{#00FF00}{O(n)}$ | 线性阶 |
| 3n*log2^n + 4n + 2 | $\color{#00FF00}{O(nlogn)}$ | nlogn阶 |
| 5n^2 + 3n + 1 | $\color{#00FF00}{O(n^2)}$ | 平方阶 |
| 6n^3 + 2n^2 + n + 1 | $\color{#0000FF}{O(n^3)}$ | 立方阶 |
| 2^n + 1 | $\color{#FF0000}{O(2^n)}$ | 指数阶 |
| n! + 3 | $\color{#FF0000}{O(n!)}$ | 阶乘阶 |

### 2.2空间复杂度

- 定义: S(n) = S(f(n))
  - n 为算法的问题规模
  - f(n) 为空间使用函数，与n有关

推导时间复杂度的方法同样适用于推导空间复杂度

``` c++
long sum1(int n)                //1
{
    long ret = 0;               //1
    int * array = new int [n];  //n

    for(int i = 0 ; i < n; i++) //1
    {
        array[i] = i + 1;
    }

    for(int i = 0; i < n; i++)  //1
    {
        ret += array[i];
    }

    delete[] array;

    return ret;
}
//所需空间为n + 4
//空间复杂度S(n + 4) = S(n)
```

### 2.3时间与空间的策略

- 多数情况下，算法的时间复杂度更加令人关注
- 如果有必要，可以通过增加额外的空间降低时间复杂度
- 同样的，也可以增加算法的耗时降低空间复杂度

## 三、数据结构如何学习

1. 先从概念上理解数据元素之间的关系
2. 考虑这种关系可以解决什么问题
3. 考虑这种关系可以产生哪些算法
4. 理解和熟悉最终的算法
5. 选择一种熟悉的语言编码实战

数据结构是计算机领域的基础课程，在学习过程中养成的思维方式将影响整个职业生涯

## 四、泛型编程简介

### 4.1 数据结构的特点

- 专注于数据元素之间的关系
- 专注于特定结构之上的算法
- 不关心数据元素的类型

### 4.2 C++ 函数模板

- 一种特殊的函数，可以用不同类型进行调用
- 看起来和普通函数相似，区别是类型可以被参数化
- 语法规则

``` c++
template <typename T>
void swap(T& a, T& b)
{
    T c = a;

    a = b;
    b = c;
}
```

- 函数模板的使用
  - 自动推导
  - 具体类型显式调用

``` c++
int a = 0;
int b = 1;

swap(a , b);              //自动推导
float c = 2;
float d = 3;
swap<float>(c, d);        //显式调用
```

### 4.3 C++ 类模板

- 以相同的方式除了不同的类
- 在类声明前用template进行标示
- \<typename T\>用于说明类中使用的是泛指类型

``` c++
template <typename T>
class Operator
{
    public:
    T op(T a, T b);
}
```

- 函数模板的使用
  - 具体类型显式调用
  - 使用具体类型\<Type\>定义对象

``` c++
Opreator<int> op1;
Operator<double> op2;

int i = op1.op(1,2);
double d = op2.op(0.01, 0.02);
```

## 五、智能指针

### 5.1内存泄漏

- 动态内存申请，用完后不归还
- C++语言没有垃圾回收机制
- 指针无法控制所指向的堆空间生命周期

### 5.2当代C++软件平台中的智能指针

- 指针生命周期结束的时候主动释放堆空间
- 一片堆空间最多智能有一个指针标识
- 杜绝指针运算和指针比较

### 5.3智能指针的设计方案

- 通过类模板描述指针的行为
  - 能够定义不同类型的指针对象
- 重载指针特征操作符（-> 和 *）
  - 利用对象模拟原生指针的行为

### 5.4智能指针的使用军规

- 智能用来指向堆空间中的单个对象或者变量

### 5.5 小结

- 指针特征操作符（-> 和 *）可以被重载
- 重载特征操作符可以$\color{#0000ff}{用对象代替指针}$
- 智能指针$\color{#FF0000}{只能够指向堆空间中的内存}$
- 智能指针的意义在于$\color{#FF0000}{最大程度的避免内存问题}$

## 六、C++异常简介

### 6.1 C++内置了异常处理的语法元素try...catch

- try 语句处理正常逻辑代码
- catch 处理异常情况
- try语句中的异常由对应的catch语句处理

``` c++
try
{
    double r = divide(1, 0);
}
catch(...)
{
    cout << "Divede by zero" << endl;
}
```

- C++通过throw语句抛出异常
- C++异常处理分析，throw抛出的异常必须被catch处理
  - 当前函数能够处理异常，程序继续往下执行
  - 当前函数无法处理异常，则函数停止执行并返回，未被处理的异常会顺着调用栈向上传播，直到被处理为止。

- 异常的类型可以是自定义类型
- 对于类类型的匹配仍然是自上而下严格匹配
- 赋值兼容性原则在异常匹配中仍然适用
- 一般而言
  - 匹配子类异常的catch在上面
  - 匹配父类异常的catch在下面

### 6.2异常功能定义

|异常类|功能定义|
|-----|-------|
|ArithmeticException|计算异常|
|NullPointerException|空指针异常|
|IndexOutofBoundsException|越界异常|
|NoEnoughMemoryException|内存不足异常|
|InvalidParameterException|参数错误异常|

### 6.3设计原则

在可复用代码库的设计时，尽可能使用面向对象的计数进行构架，尽可能使用异常处理机制分离正常逻辑和异常逻辑

## 七、创建顶层父类

### 7.1当代软件架构实践的经验

- 尽量使用单继承
- 尽量保持系统中只存在单一继承树
- 尽量使用组合关系代替继承关系

- C++语言的灵活性使得代码中可以存在多个继承树
- C++编译器的差异使得同样的代码可能表现不同的行为
  - $\color{#FF0000}{new操作如果失败会发生什么？}$
  - 有的返回NULL
  - 有的抛出标准异常

### 7.2 创建顶层父类的意义

- 保持单一继承树，所有数据结构都继承自Object
- 定义动态申请的行为，提高代码的可移植性

``` c++
class Object
{
    public:
    void * operator new(unsigned int size) throw();
    void operator delete(void * p);
    void * operator new[] (unsigned int size) throw();
    void operator delete[](void * p);
    virtual ~Object() = 0;
};
```

### 7.3开发方式和注意事项

- 迭代开发
  - 每完成一个小目标，持续开发，最终打造可复用的类库
- 单一继承树
  - 所有的类继承自Object，规范堆创建对象时候的行为
- 只抛出异常，不处理异常
  - 提高代码的可移植性(不支持异常时可以注释宏扩展)，通过THROW_EXCEPTION抛出异常
- 弱耦合性
  - 尽量不使用标准库中的类和函数，提高可移植性

## 八、线性表的性质和操作

### 8.1线性表的表现形式

- 零个或者多个元素的集合
- 数据元素在位置排列上是有序的
- 数据元素个数有限
- 数据元素类型相同

### 8.2线性表的抽象定义

- 线性表是具有相同类型的n(n >= 0)个元素的有限序列

### 8.3线性表的性质

- a0为线性表的第一个元素，只有一个后继
- an-1为线性表的最后一个元素，只有一个前驱
- 除了a0和an-1之外，其他元素既有前驱也有后继
- 线性表中的元素是可以任意存取的

### 8.4下面哪些可以用线性表描述

- 班级中的同学关系(N 一个人可能有多个好朋友)
- 公司中的上下级关系(N 一个领导可能有多个下属)
- 图书馆用物品排队占座(N 物品和人不是同类)
- 花名册是上名字之间的关系(和排列方式有关)

### 8.5线性表支持的操作

- 插入
- 删除
- 获取值
- 设置值
- 获取长度
- 清空表

### 8.6线性表对应程序中是一个特殊的数据类型

``` c++
template <typename T>
class List:public Object
{
    public:
    virtual bool insert(int i, const T& e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool get(int i, T& e) const = 0;
    virtual bool set(int i, const T& e) = 0;
    virtual int length(void) const = 0;
    virtual void clear(void) = 0;
}
```

### 8.7线性表的顺序存储结构

顺序存储的定义：线性表的顺序存储结构，是指用一段地址连续的存储但愿依次存储线性表的数据元素。

顺序结构的元素获取操作：

- 判断目标位置是否合法
- 将目标位置作为数组下标获取元素

顺序结构的元素插入:

- 判断目标位置是否合法
- 将目标位置之后所有元素后移动一位
- 将新元素插入目标位置
- 线性长度加一

顺序存储结构的删除操作:

- 判断位置是否合法
- 将该位置后所有元素向前移动一位
- 数据长度减去1

完成顺序结构线性表的抽象实现:

- 抽象类模板，存储空间和大小由子类实现
- 实现顺序存储线性表的关键操作（增，删，查，改）
- 提供数组操作符，方便访问元素

StaticList设计要点：

- 类模板
  - 使用原生数组作为存储空间
  - 使用模板参数决定数组大小

DynamicList设计要点：

- 类模板

  - 申请连续存储空间作为顺序存储空间
  - 动态设置顺序存储空间的大小
  - 保证重置顺序存储空间时的异常安全性

- 函数异常安全的概念

  - 不泄漏任何资源
  - 不允许破坏数据

- 函数异常安全的基本保证

  - 如果异常抛出
  - 对象内任何成员仍然能够保持有效状态
  - 没有数据破坏和资源泄漏

### 8.8顺序存储线性表的效率分析

- 在涉及到效率的时候通常考虑最坏情况（插入和删除操作是线性表中最耗时的操作）

```c++
template <typename T>
class SeqList:public List<T>
{
protected:
    T * m_array;
    int m_length;

public:
    //O(n)
    bool insert(int i, const T &e);
    //O(n)
    bool remove(int i);
    //O(1)
    bool set(int i, const T &e);
    //O(1)
    bool get(int i, T &e)const;
    //O(1)
    int  length(void) const;
    //O(1)
    void clear(void);
    //O(1)
    T& operator[] (int i);
    //O(1)
    T operator[] (int i) const;
    //O(1)
    virtual  int capacity(void)const = 0;
};

// 不同类型之间的插入和删除所用时间不同
SeqList<int> S1;
SeqList<string> S2;
```

- 效率不能只看时间复杂度，还要根据具体场景考虑，基于顺序存储结构的线性表不适合类类型的数据存储

### 8.9下面的代码正确吗？为什么？

```c++
StaticList<int *, 5> s1;
StaticList<int *, 5> s2;

for(int i = 0; i < s1.capacity(); i++)
    s1.insert(0, new int(i));

s2 = s1;

for(int i = 0; i < s1.capacity(); i++)
{
    delete s1[i];
    delete s2[i];
}
```

- 不正确，因为s2=s1是浅拷贝，两个对象指向同一段空间，同一个空间被释放两次

```c++
DyanmicList<int> d1;
DyanmicList<int> d2 = d1;

for(int i = 0; i < d1.capacity(); i++)
{
    d1.insert(0, i);
    d2.insert(0, i*i);
}

delete d1[i];
delete d2[i];
```

- 不正确，拷贝构造将d2的m_array赋值为d1的m_array，并且同一段内存被释放两次
- 对于容器类型的类，可以考虑禁用拷贝构造和赋值操作

```c++
int main()
{
    StaticList<int, 5> s1;
    for(int i = 0; i< s1.capacity(); i++)
    {
        s1[i] = i * i;
    }
    return 0;
}
```

- 不正确，线性表必须先插入元素才能使用[]访问

### 8.10 线性表的链式存储结构

顺序存储线性表最大的问题

- 插入和删除需要大量移动元素

链式存储的定义

- 为了表示每个元素和与其直接后继元素之间的关系，数据元素除了要存储本身的信息外，还需要存储其直接后继信息。

|......| ai | 地址0x80AB0C | ai+1 | 地址0x80FFD0 | ...... |
|------|----|-------------|------|--------------|--------|

- ai和ai+1是线性表中两个相邻元素，但是在物理地址上不存在相邻关系

专业术语的统一：

- 顺序表
  - 基于顺序存储结构的线性表
- 链表
  - 基于链式存储结构的线性表
  - 单链表：每个节点只包含后继信息
  - 循环链表：单链表的最后一个节点的直接后继节点为第一个节点
  - 双向链表：每个节点包含直接前驱和后继的地址信息

链表中的基本概念：

- 头节点
  - 链表中的辅助节点，包含执行第一个元素的指针
- 数据节点
  - 链表中代表数据元素的节点，表现形式为:(数据，地址)
- 尾节点
  - 链表中最后一个数据节点，包含的地址信息为空

单链表中的内部结构

- 头节点->数据->NULL
- 头节点的意义在于：辅助数据元素定位，方便进行插入和删除操作，因此，头节点不存储数据

在目标位置插入数据元素

- 从头节点通过指针找到指定位置
- 从堆空间申请新的节点
- 执行操作：
  - 拷贝插入值到新申请的节点(node->value = e)
  - 将新申请的节点指针指向下一个节点(node->next = current->next)
  - 将当前位置的节点的指针指向新申请的节点(current->next = node)

在目标位置删除元素

- 从头节点通过指针找到指定位置
- 使用toDel指向要删除的节点
- 执行操作：
  - toDel = current->next;
  - current->next = toDel->next;
  - delete toDel;

LinkList设计要点

- 类模板，通过头节点访问后继节点
- 实现内部节点类型Node,用于描述数据域和指针域
- 实现关键操作（增删查改）

```c++
template <typename T>
class LinkList:public List<T>
{
  protected:
    struct Node:public Object
    {
      T value;
      Node * next;
    };

    Node m_head;
    int m_length;

  public:
    LinkList();
};
```

问题

- 头节点是否存在隐患？
  - 泛指类型如下：
  - 头节点中包含了该自定义类型的一个变量，无参构造函数会抛出异常
- 解决方法

```c++
mutable struct:public Object
{
  char reserve[sizeof(T)];
  Node* next;
}m_header;
```

- $\color{#FF0000}{为了保证内存一致，两个结构体应该还需要注意一点，如果存在继承关系，需要继承自相同的父类}$
- $\color{#FF0000}{如果需要保存自定义类型的数据，必须提供无参构造函数}$

问题：顺序表的整体时间复杂度比单链表的时间复杂度低，但是单链表使用更多，为什么？

- 效率的深度分析
  - 实际工程开发中，时间复杂度只是效率的一个参考
    - 对于内置基础类型，顺序表和单链表的效率不相上下
    - 对于自定义类型，顺序表效率低于单链表
  - 插入和删除
    - 顺序表：涉及大量数据的复制
    - 单链表：只涉及指针操作
  - 数据访问
    - 顺序表：随机访问，直接定位对象
    - 单链表：顺序访问，必须从头到尾，无法直接定位
  
- 工程中的选择
  - 顺序表
    - 数据元素相对简单，不涉及深拷贝
    - 数据元素相对稳定，访问操作多于插入和删除操作
  - 单链表
    - 数据元素的类型相对复杂，复制操作相对耗时
    - 数据元素不稳定，需要经常插入和删除，访问操作比较少

### 8.11 静态单链表

- 单链表的缺陷
  - 触发条件
    - 长时间使用单链表对象频繁单增加和删除数据元素
  - 可能的结果
    - 堆空间产生大量内存碎片，系统运行缓慢
  - 新的线性表
    - 设计思路
    - 在单链表内部增加一片预留的空间，所有的Node对象都在这里面进行动态的创建和销毁。
    - 顺序表 + 单链表 = 静态单链表
  - 静态单链表的实现思路
    - 通过模板定义静态单链表
    - 在类中定义固定的大小空间
    - 重写create和destory函数
    - 在Node类中重载operator new，用于在指定内存上创建对象
- 注意事项
  - StaticLinkList中对create和destory进行重写，注意析构顺序

小结

- 顺序表和链表结合产生静态单链表
- 静态单链表是链表的子类,支持单链表的所有操作
- 静态单链表在预留的空间中创建对象
- 静态单链表适合频繁增加或者删除元素的场合（最大元素个数固定）

## 九、数组类

### 9.1 课程目标

- 完成Array类的具体实现
- 完成StaticArray类的具体实现
- 完成DynamicArray设计要点

### 9.2 需求分析

- 数组类包含长度信息
- 数组类能够主动发现越界

### 9.3 Array设计要点

- 抽象类模板，存储空间的位置和大小由子类完成
- 重载数组操作符，判断下标是否合法
- 提供数组长度访问的抽象函数
- 提供数组对象间的复制操作

``` c++
template <typename T>
class Array:public Object
{
    protected:
    T* m_array;
    public:
    virtual bool set(int position, const T& value);
    virtual bool get(int position, T& value);
    virtual int length(void) const = 0;
    T& operator[](int position);
    T operator[](int position) const;
};
```

### 9.4 StaticArray设计要点

- 封装原生数组
- 使用模板参数决定原生数组的大小
- 实现函数返回数组长度
- 拷贝构造和赋值操作

### 9.5 DynamicArray设计要点

- 动态确定内部数组空间的大小
- 实现函数返回数组长度
- 拷贝构造和赋值操作

## 十、典型问题分析

### 问题1:创建对象时的空指针问题

``` c++
__strdup(const char * s)
{
  size_t len = strlen(s) + 1;
  void *new = malloc(len);

  if(new == NULL)
    return NULL;

  return (char *) memcpy(new, s, len);
}
```

为了增加程序的健壮性，外部需要判断字符串是否为空

### 问题2:LinkList中元素删除问题

为了避免在delete操作时候发生异常，因此在删除元素的时候应该把delete操作放在最后。

### 问题3:List中遍历操作与删除操作的混合使用

### 问题4:在StaticLinkList中元素删除的效率问题

找到删除元素之后跳出循环，避免继续查找

### 问题5:StaticLinkList是否需要析构函数

- 需要,因为如果静态链表中有数据，在析构时不会发生多态行为，父类中会调用父类的destory，但是由于并没有申请空间，此时会错误的释放空间。
- 根据析构顺序，子类析构后才会析构父类，所以应该在子类的析构函数中将链表清空，这样在父类中的destory就不会被执行到

## 十一、循环链表

### 11.1 概念

- 任意一个元素都有一个前驱和一个后继
- 所有元素堆关系构成一个逻辑上的环

### 11.2 实现

- 循环链表是一种特殊的单链表
- 尾节点的指针保存了首节点的地址

### 11.3循环链表的实现思路

- 通过模板定义CircleList,继承自LinkList
- 通过内部函数last_to_first(),用于将链表首尾相连接
- 特殊处理:首元素的插入操作和删除操作
- 重新实现:清空操作和遍历操作
  
### 11.4 循环链表的实现要点

- 插入位置为0时:
  - 头节点和尾节点均指向新节点
  - 新的节点成为首节点插入链表
- 删除位置为0时:
  - 头节点和尾节点均指向位置为1的节点
  - 安全销毁首节点

## 十二、双链表

### 12.1 单链表单另一个缺陷

- 单向性
  - 只能从头节点开始访问链表中的数据元素
- 缺陷
  - 如果需要逆向访问链表中数据元素将极其低效

```c++
int main()
{
    LinkList<int> l;

    // O(n)
    for(int i = 0; i < 5; i++)
    {
        l.insert(0, i);
    }

    // O(n^2)
    for(int i = l.length() - 1; i >= 0; i--)
    {
        cout << l.get(i) << endl;
    }
}
```

### 12.2 新的线性表

- 设计思路：
  - 在单链表中增加一个指针pre
  - 用于指向当前节点的前驱节点

在目标位置插入数据元素

- 从头节点通过指针找到指定位置
- 从堆空间申请新的节点
- 执行操作：
  - 拷贝插入值到新申请的节点(node->value = e)
  - 1、将新申请的节点next指针指向下一个节点(node->next = next)
  - 2、如果下一个节点非空，则将下一个节点的pre指向新申请的节点(next->pre = node)
  - 3、如果当前节点不是头节点，将新申请的节点pre指针指向当前位置的节点(node->pre = current)
  - 4、如果当前节点是头节点，将新申请的节点pre指针指向NULL(node->pre = NULL)
  - 5、将当前位置的节点的next指针指向新申请的节点(current->next = node)
- 循环链表在0位置插入时则在上述操作完成之后，将最后一个节点的next指向第一个节点，将第一个节点指向最后一个节点

在目标位置删除元素

- 从头节点通过指针找到指定位置
- 使用toDel指向要删除的节点
- 执行操作：
  - 1、将当前节点的next指向要删除节点的后面一个节点（current->next = next）
  - 2、如果next节点非空，将next节点的pre指向要删除节点的前驱（next->pre = toDel->pre）
  - delete toDel;
- 循环链表在0位置删除时则在上述操作完成之后，将最后一个节点的next指向第一个节点，将第一个节点指向最后一个节点

## 十三、栈的概念和实现

栈的定义

- 栈是一种特殊的线性表
- 栈仅仅能在线性表的一端进行操作
  - 栈顶：允许操作的一端
  - 栈底：不允许操作的一端

- 后进先出(LIFO)

### 13.1 栈的操作

- 创建栈(Stack)
- 销毁栈(~Stack)
- 清空栈(clear)
- 入栈(push)
- 出栈(pop)
- 获取栈顶元素(top)
- 获取栈大小(size)

```c++
template <typename T>
class Stack:public Object
{
public:
  virtual void push(const T& e) = 0;
  virtual void pop() = 0;
  virtual T top() const = 0;
  virtual void clear() = 0;
  virtual int size() const = 0;
};
```

### 13.2 顺序栈的设计要点

- StaticStack使用原生数组作为存储空间
- StaticStack最大容量由模板参数决定

### 13.3 链式栈的设计要点

- 类模板，抽象父类Stack的直接子类
- 在内部组合使用LinkList类，实现栈的链式存储
- 只在单链表的头部进行操作

### 13.4 栈的应用实现

- 符号匹配问题
  - 在C语言中有一些符号成对出现
    - 括号:(),{},[],<>
    - 引号:'',""
- 问题
  - 如何实现符号的成对检测
- 算法思路
  - 从第一个字符开始扫描
  - 遇见普通字符时候忽略
  - 遇见左符号时亚栈
  - 遇见右符号弹出栈顶符号，并进行匹配
- 结束
  - 成功:所有字符扫描完毕，且栈空
  - 失败，匹配失败或者所有字符扫描完毕但是栈非空
- 栈的后进先出的特性适用于检测成对出现对符号
- 栈非常适合就近匹配的场合

## 十四、队列的概念及其实现

### 14.1 队列是一种特殊的线性表

- 队列能在线性表的两端进行操作
  - 队头(Head):取出数据的一端
  - 队尾(Rear):插入数据的一端
- 具有先进先出的特性

## 14.2 队列的操作

- 创建队列(Queue)
- 销毁队列(~Queue)
- 清空队列(clear)
- 进队列(add)
- 出队列(remove)
- 获取队头元素(front)
- 获取队的长度(length)
  
### 14.3 StaticQueue实现要点

- 关键操作
  - 进队列:m_space[m_rear] = e; m_rear = (m_rear + 1) % N
  - 出队列:m_front = (m_front + 1) % N;
- 队空:(m_length = 0) && (m_front == m_rear)
- 队满:(m_length = N) && (m_front == m_rear)

## 14.4 LinkQueue实现要点

- 类模板，抽象父类Queue的直接子类
- 在内部使用链式存储结构实现元素的存储
- 在链表的头部和尾部进行操作
- 问题：使用LinkList类实现链式队列是否合适，是否有更好的方法?

```c++
namespace data_structure
{
    template <typename T>
    class Queue:public Object
    {
    public:
        virtual void add(const T& e) = 0;
        virtual void remove() = 0;
        virtual T front() const = 0;
        virtual void clear() = 0;
        virtual int length() const = 0;
    };
}
```

### 14.5 用栈实现队列

- 准备两个栈用于实现队列: stack_in和stack_out
  - 当有新元素入队时:压入stack_in
  - 需要出队的时候:
  - stack_out.size() == 0
    - 将stack_in中的元素逐个弹出并压入stack_out
    - 将stack_out的栈顶元素弹出
  - stack_out.size() > 0
    - 将stack_out的栈顶元素弹出

### 14.6 用队列实现栈

- 准备两个队列用于实现栈: queue_1[in]和queue2[out]
  - 当有新元素入栈的时候,将其加入队列[in]
  - 当需要出栈的时候:
    - 将队列[in]中的n-1个元素出队列并进入[out]中
    - 将队列[in]中的最后一个元素出队列(出栈)
    - 交换两个队列的角色

## 十五、字符串类的创建

历史遗留问题

- C语言不支持真正意义的字符串
- C语言用字符数组和一组函数实现字符操作
- C语言不支持自定义类型，依次无法获得字符串类型
- 从C到C++的进化过程引入了自定义类型
- 在C++中可以通过类完成字符串类型的定义

字符串类的设计

``` c++
namespace data_structure
{
    class String:public Object
    {
    protected:
        char * m_str;
        int m_length;

        void init(const char * s);
    public:
        String();
        String(const char * s);
        String(const String& s);
        String(char c);
        int length() const;
        const char * str() const;

        /*比较操作符重载函数*/
        bool operator == (const String& s) const;
        bool operator == (const char* s) const;
        bool operator != (const String& s) const;
        bool operator != (const char* s) const;
        bool operator > (const String& s) const;
        bool operator > (const char* s) const;
        bool operator < (const String& s) const;
        bool operator < (const char* s) const;
        bool operator >= (const String& s) const;
        bool operator >= (const char* s) const;
        bool operator <= (const String& s) const;
        bool operator <= (const char* s) const;
        /*加法操作符重载函数*/
        String operator + (const String& s) const;
        String operator + (const char* s) const;
        String& operator += (const String& s);
        String& operator += (const char* s);
        /*赋值操作符重载函数*/
        String& operator = (const String& s);
        String& operator = (const char* s);
        String& operator = (char c);
        char operator [](int i) const;
        char& operator [](int i);

        bool startWith(const char* s) const;
        bool startWith(const String& s) const;
        bool startWith(char c) const;
        bool endOf(const char* s) const;
        bool endOf(const String& s) const;
        bool endOf(char c) const;
        String& insert(int i, const char* s);
        String& insert(int i, char c);
        String& insert(int i, const String& s);
        String& trim();
        int indexOf(const String& s) const;
        int indexOf(const char* s) const;
        String& remove(int i, int len);
        String& remove(const String& s);
        String& remove(const char* s);
        String operator-(const String& s) const;
        String operator-(const char* s) const;
        String& operator-=(const String& s);
        String& operator-=(const char* s);
        String& replace(const char* t, const char* s);
        String& replace(const String& t, const char* s);
        String& replace(const char* t, const String* s);
        String& replace(const String& t, const String& s);
        String substring(int i, int len) const;
        
        ~String();
    };
    
}
```

实现时候的注意事项：

- 无缝实现String和char *字符串的互操作
- 操作符重载函数需要考虑是否支持const版本
- 通过C语言的字符串函数实现String的成员函数

### 15.1 KMP子串查找算法

从头到尾进行匹配太费时间了

发现

- $\color{red}{匹配失败到时候右移的位数和子串本身有关，与目标串没关系}$
- 移动位数 = 已经匹配的字符数 - 对应的部分匹配值
- 任意子串都存在一个唯一的部分匹配表

$\color{red}{部分匹配表如何得到？}$

- 前缀
  - 除了最后一个字符外，一个字符串的全部头部的组合
- 后缀
  - 除了第一个字符外，一个字符串的全部尾部的组合
- 部分匹配值
  - 前缀和后缀最长共有元素的长度

示例ABCDABD
|字符|前缀|后缀|交集|匹配值|
|---|----|---|----|----|
| A | 空 | 空 | 空 | 0  |
| AB | A | B | 空 | 0  |
| ABC | A,AB | BC,C |空|0|
| ABCD | A,AB,ABC | BCD,CD,D |空|0|
| ABCDA  | A,AB,ABC,ABCD | BCDA,CDA,DA,A | A | 1 |
| ABCDAB | A,AB,ABC,ABCD,ABCDA | BCDAB,CDAB,AB,B | AB | 2 |
| ABCDABD| A,AB,ABC,ABCD,ABCDA,ABCDAB| BCDABD,CDABD,DABD,ABD,BD,D| 空 | 0 |

如何使用编程产生部分匹配表？

- PMT[1] = 0 (下标为0的元素匹配值为0)
- 从第二个字符开始递推(从下标为1的字符开始递推)
- 假设PMT[n] = PMT[n-1] + 1(最长共有元素的长度)
- 当假设不成立，PMT[n]在PMT[n-1]的基础上减小

(1)当前要求的ll值，通过历史ll值推导
(2)当可选ll值为0时，直接比对首尾元素
(3)重叠部分的长度就是当前的LL值，即3，PMT[3]含义是查找3个字符时的LL值，而3个字符时的LL值对应下标为2的情况，编程时需要注意长度与下标对应关系

## 十六、递归的思想与应用

- 递归十一种数学上分而自治的思想
  - 将原问题分解为小规模的问题进行处理
    - 分解后的问题与原问题的类型相同，但是规模小
    - 通过小规模问题的解，能够轻易求出原问题的解
- 问题的分解是有限的，不能无限进行
  - 当边界调节不满足的时候，分解问题(递归继续)
  - 当边界条件满足的时候直接求解(递归结束)

- 递归函数
  - 函数体存在自我调用的函数
  - 递归函数必须有出口
  - 函数的无限递归将导致程序崩溃

```c++
// 求字符串长度
int length(const char *s)
{
    if(*s == '\0')
    {
        return 0;
    }
    else
    {
        return 1 + length(s + 1);
    }
}
```

函数调用过程:

- 程序运行后有一个特殊的内存区域供函数调用使用
  - 用于保存函数中的实参，局部变量，临时变量，等
  - 从起始地址开始向一个方向增长(如：高地址->低地址)
  - 有一个专用指针标识当前已使用内存的"顶部"

## 十七、排序

- 排序的一般定义
  - 排序是极速你内经常进行的一种操作，其目的是将一组无序的数据调整为有序的数据元素

- 排序的数学定义
  - 假设含有n个数据元素的序列为:{R1,R2,...,Rn},其相应的关键字序列为{K1,K2,...,Kn}
  - 这些关键字相互之间可以进行比较，即在他们之间存在这样的一个关系:Kp1 < Kp2 < ... Kpn
  - 按此固定关系将上式记录序列重新排列为:{Rp1,Rp2,...,Rpn}的操作称为排序

- 排序的稳定性
  - 如果在序列中有两个元素r[i]和r[j],他们的关键字K[i] = K[j],对象r[i]在r[j]前面，如果排序之后，对象r[i]仍然在r[j]前面，则称这个排序方法是稳定的，否则称这个排序不稳定。

- 多关键字排序
  - 排序时需要比较的关键字多于一个
    - 排序结果首先按关键字1进行排序
    - 当关键字1相同时用关键字2进行排序
    - ...
    - 当关键字n-1相同时按照关键字n进行排序
- 多关键字排序和单个关键字排序无本质区别

- 排序中的关键操作
  - 比较
    - 任意两个数据元素后确定先后顺序
  - 交换
    - 数据元素之间需要交换才能得到预期的结果

- 排序的审判
  - 时间性能
    - 关键性能体现在比较和交换的数量
  - 辅助存储空间
    - 为完成排序操作需要的额外存储孔家
    - 必要时可以“空间换时间”
  - 算法的实现复杂性
    - 过于复杂的排序法可能影响可读性和可维护性

### 17.1 选择排序

- 每次从后面n-i个待排序的数据中选出关键字最小的元素，最为有序元素序列第i个元素
- 选择排序是不稳定的排序法，因为元素会进行交换
- 时间复杂度O(n^2)

### 17.2 插入排序

- 当插入第i个数据元素时，前面的V[0]，V[1]，...，V[i-1]已经排好顺序；这时，用V[i]关键字与V[i-1]，V[i-2]，V[0]进行比较,找到位置后将V[i]插入，原来位置上的对象往后顺移。
- 插入排序是稳定排序
- 时间复杂度O(n^2)

### 17.3 冒泡排序

- 每次从后向前进行,(假设为第i次)，j = n - 1, n - 2, ..., i, 两两比较V[j-1]和V[j]的关键字，如果发生逆序则进行交换。
- 冒泡排序是稳定排序
- 时间复杂度O(n^2)

### 17.4 希尔排序

- 通过分组的方式进行多次插入排序
- 希尔排序是一种不稳定排序法，分组间隔造成
- 希尔排序的时间复杂度为O(n^3/2)

### 17.5 归并排序

- 将两个或者两个以上的有序序列合并成一个新的有序序列
- V[0]...V[m]和V[m+1]...V[n]合并为V[0]...V[n]
- 归并排序是一种稳定排序
- 时间复杂度为O(n*logn)

### 17.6 快速排序

- 任取序列中的某个元素作为基准将整个序列划分为左右两个子序列
  - 左侧子序列中所有元素都小于或等于基准元素
  - 右侧子序列中所有元素都大于基准元素
  - 基准元素排列在两个子序列中间
- 分别对这两个子序列重复进行划分，直到所有元素都排列在相应位置上面为止。
- 快速排序是一种不稳定排序
- 时间复杂度为O(n*logn)
