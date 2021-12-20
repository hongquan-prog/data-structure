#include "DualCircleList.h"

typedef struct
{
    list_def base;
    struct dual_link_list_node head;
}dual_circle_list_def;

static list_vtable_def s_dual_circle_list_vtable = 
{
    .insert = dual_circle_list_insert,
    .remove = dual_circle_list_remove,
    .find = link_list_find,
    .get = link_list_get,
    .set = NULL,
    .length = vector_length
};

DualLinkList* dual_circle_list_create()
{
    dual_circle_list_def* ret = dual_link_list_create();
    if(ret)
    {
        ret->base.vtable = &s_dual_circle_list_vtable;
    }
    return ret;
}