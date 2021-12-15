#include "err.h"
#include "list.h"


int array[100];

int main()
{
    List* list = list_create(100);
    for(int  i = 0; i < list_length(list); i++)
    {
        array[i] = i;
        list_set(list, 99 - i, (ListNode)&(array[i]));
    }

    for(int i = 0; i < list_length(list); i++)
    {
        ListNode ret = NULL;
        list_get(list, i, &ret);
        printf("%d\n", *((int *)ret));
    }

    list_clear(list);
}