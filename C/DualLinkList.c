#include "DualLinkList.h"

typedef struct
{
    list_def base;
    struct dual_link_list_node head;
}dual_link_list_def;

static list_vtable_def s_dual_link_list_vtable = 
{
    .insert = dual_link_list_insert,
    .remove = dual_link_list_remove,
    .find = link_list_find,
    .get = link_list_get,
    .set = NULL,
    .length = vector_length
};

DualLinkListNode dual_link_list_position(DualLinkList* list,int position)
{
    dual_link_list_def* obj = (dual_link_list_def*)list;
    struct dual_link_list_node* current = (struct dual_link_list_node*)(&(obj->head));
    for(int i = 0; i < position; i++)
    {
        current = current->next;
    }
    return current; 
}

DualLinkList* dual_link_list_create()
{
    dual_link_list_def* list = malloc(sizeof(dual_link_list_def));
    if(list)
    {
        list->base.length = 0;
        list->base.vtable = &s_dual_link_list_vtable;
        list->head.next = NULL;
        list->head.pre = NULL;
    }
    return (DualLinkList*)list;
}

bool dual_link_list_insert(DualLinkList* list, int i, const DualLinkListNode node)
{
    bool ret = true;
    dual_link_list_def* obj = (dual_link_list_def*)list;
    if(obj && (i >= 0) && (i <= obj->base.length) && node)
    {
        struct dual_link_list_node* current = dual_link_list_position(obj, i);
        if(current)
        {
            struct dual_link_list_node* next = current->next;
            ((struct dual_link_list_node*)node)->next = next;
            ((struct dual_link_list_node*)node)->pre = (current == &(obj->head)) ? (NULL) : (current);
            current->next = node;
            ++obj->base.length;
            if(next)
            {
                next->pre = node;
            }
        }        
    }
    else
    {
        ret = false;
    }
    return ret;
}
#include <stdio.h>
DualLinkListNode dual_link_list_remove(DualLinkList* list, int i)
{
    DualLinkListNode ret = NULL;
    dual_link_list_def* obj = (dual_link_list_def*)list;
    if(obj && (i >= 0) && (i < obj->base.length))
    {
        struct dual_link_list_node* current = dual_link_list_position(obj, i);
        struct dual_link_list_node* toDel = (current) ? (current->next) : (NULL);
        struct dual_link_list_node* next = (toDel) ? (toDel->next) : (NULL);
        if(current && toDel)
        {
            ret = toDel;
            current->next = next;
            --obj->base.length;
            if(next)
            {
                next->pre = current;
            }
        }        
    }
    return ret;
}

void dual_link_list_clear(DualLinkList* list)
{
    free(list);
}