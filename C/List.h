#ifndef LIST_H
#define LIST_H

#include "err.h"

typedef void List;
typedef void* ListNode;

typedef struct
{
    bool (*insert)(List* list, int i, const ListNode node);
    ListNode (*remove)(List* list, int i);
    int (*find)(List* list, const ListNode node);
    bool (*get)(List* list, int i, ListNode* node);
    bool (*set)(List* list, int i, const ListNode node);
    int (*length)(List* list);
}list_vtable_def;

typedef struct
{
    list_vtable_def* vtable;
    int length;
}list_def;


void list_insert(List* list, int i, ListNode node);
ListNode list_remove(List* list, int i);
ListNode list_get(List* list, int i);
bool list_set(List* list, int i, const ListNode node);
int list_length(List* list);
int list_find(List* list, const ListNode node);

#endif