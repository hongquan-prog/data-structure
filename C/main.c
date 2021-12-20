#include "err.h"
#include "Vector.h"
#include "LinkList.h"
#include "CircleList.h"
#include "DualLinkList.h"

#define MAX_LEN 10

struct list_node
{
    struct dual_link_list_node next;
    int data;
};
// 100个链表节点
struct list_node  array1[MAX_LEN] = {0};

int main()
{
    DualLinkList* list = dual_link_list_create();
   
    // 将数据插入表中
    for(int i = 0; i < MAX_LEN; i++)
    {
        array1[i].data = i;
        list_insert(list, i, &array1[i]);
        // printf("%x  ", &array1[i]);
    }
    printf("list length:%d\n", list_length(list));

    // while(list_length(list))
    // {
    //     DualLinkListNode ret = list_remove(list, 0);
    //     printf("%x  ", ret);
    // }
    // printf("list length:%d\n", list_length(list));

    // 输出链表中的值
    printf("list:");
    for(int i = 0; i < 2 * MAX_LEN; i++)
    {
        struct list_node* ret = list_get(list, i);
        if(ret)
            printf("%d ", ret->data);
    }
    printf("\n");

    circle_list_clear(list);
}