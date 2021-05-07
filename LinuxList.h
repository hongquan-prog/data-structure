#pragma once

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE*)0)->MEMBER)
#endif

#ifndef container_of
#define container_of(ptr, type, member) ({              \
    const typeof(((type *)0)->member)* __mptr = (ptr);  \
    (type*)((char*)__mptr - offsetof(type, member));})
#endif

struct list_head {
    struct  list_head *next, *prev;    
};

struct hlist_head{
    struct hlist_node *first;
};

struct hlist_node{
    struct hlist_node *next, **pprev;
};