#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef void List;
typedef void* ListNode;

List* list_create(int length);
bool list_insert(List* list, int i, const ListNode node);
bool list_remove(List* list, int i);
int list_find(List* list, const ListNode node);
bool list_get(List* list, int i, ListNode* node);
bool list_set(List* list, int i, const ListNode node);
int list_length(List* list);
void list_clear(List* list);

#endif