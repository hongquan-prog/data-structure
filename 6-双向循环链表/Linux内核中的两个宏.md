# Linux内核中的两个宏

```c++
#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE*)0)->MEMBER)
#endif

#ifndef container_of
#define container_of(ptr, type, member) ({              \
    const typeof(((type *)0)->member)* __mptr = (ptr);  \
    (type*)((char*)__mptr - offsetof(type, member));})
#endif
```

## offsetof用于计算TYPE结构体中MEMBER成员变量的偏移量

- ({})是何方神圣？
  - ({})是GNU C编译器的语法扩展
  - ({})与逗号表达式类似，结果为最后一个语句的值

- 下面两种写法等价
  
```c++
// 写法1
int a = 0;
int b = 0;
int r = (a = 1, b = 2, a + b);

// 写法2
int r = ({ int a = 1;
           int b = 2;
           a + b;})
```

## container_of就是根据成员变量的地址得到整个结构体的首地址

- typeof是GNU C编译器特有的关键字
- typeof只在编译时有效，用于得到变量的类型
  
```c++
int i = 100;
// 等价 int j = i;
typeof(i) j = i;
// 等价 const int * p = &j;
const typeof(i) * p = &j;
```

- container_of使用({})进行类型安全检查(const typeof(((type *)0)->member)* __mptr = (ptr))
- 使用({})是因为逗号表达式不能定义变量
