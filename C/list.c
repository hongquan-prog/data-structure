#include "list.h"

struct list
{
    int length;
    ListNode* node;
};

List* list_create(int length)
{
    struct list* ret = NULL;

    if(length > 0)
    {
        ret = malloc(sizeof(struct list));
        ret->node = malloc(sizeof(ListNode) * length);
        if(ret && ret->node)
        {
            ret->length = length;
            for(int i = 0; i < length; i++)
            {
                ret->node[i] = NULL;
            }
        }
    }

    return (List*)ret;
}

bool list_insert(List* list, int i, const ListNode node)
{
    bool ret = true;
    struct list* obj = (struct list*)list;

    if(obj && (i >= 0) && (i < obj->length) && node)
    {
        for(int j = obj->length - 1; j > i; j--)
        {
            obj->node[j] = obj->node[j - 1];
        }
        obj->node[i] = node;
    }
    else
    {
        ret = false;
    }
    return ret;
}

bool list_remove(List* list, int i)
{
    bool ret = true;
    struct list* obj = (struct list*)list;

    if(obj && (i >= 0) && (i < obj->length))
    {
        for(int j = i + 1; j < obj->length; j++)
        {
            obj->node[j - 1] = obj->node[j];
        }
    }
    else
    {
        ret = false;
    }
    return ret;
}

int list_find(List* list, const ListNode node)
{
    int ret = -1;
    struct list* obj = (struct list*)list;

    if(obj && node)
    {
        for(int i = 0; i < obj->length; i++)
        {
            if(obj->node[i] == node)
            {
                ret = i;
                break;
            }
        }
    }
    return ret;
}

bool list_get(List* list, int i, ListNode* node)
{
    bool ret = true;
    struct list* obj = (struct list*)list;

    if(obj && (i >= 0) && (i < obj->length) && node)
    {
        *node = obj->node[i];
    }
    else
    {
        ret = false;
    }
    return ret;
}

bool list_set(List* list, int i, const ListNode node)
{
    bool ret = true;
    struct list* obj = (struct list*)list;

    if(obj && (i >= 0) && (i < obj->length) && node)
    {
        obj->node[i] = node;
    }
    else
    {
        ret = false;
    }
    return ret;
}

int list_length(List* list)
{
    int ret = 0;

    ret = (list) ? ((struct list*)list)->length : (0);

    return ret;
}

void list_clear(List* list)
{
    if(list)
    {
        free(((struct list*)list)->node);
        free(list);
    }
}