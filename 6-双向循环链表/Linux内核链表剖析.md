# Linux内核链表剖析

- 移植Linux内核链表,使其使用于非GNU编译器
- 分析Linux内核中链表的基本实现
- include/linux/list.h
- 依赖
  - #include <linux/types.h>
  - #include <linux/stddef.h>
  - #include <linux/position.h>
  - #include <linux/prefetch.h>
- 移植的注意事项
  - 清除文件间的依赖
  - 剥离依赖文件中与链表实现相关的代码
- 清除平台相关代码（GNU C）
  - ({})
  - typeof
  - __buitin_prefetch
  - static inline
