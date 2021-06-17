#include <iostream>
#include "Exception.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "StaticStack.h"
#include "LinkStack.h"
#include "StaticQueue.h"
#include "DualCircleLinkList.h"
#include "LinkQueue.h"
#include "StackToQueue.h"
#include "QueueToStack.h"
#include "DTString.h"
#include "Sort.h"
#include <unistd.h>

using namespace std;
using namespace data_structure;


int main(void)
{
    DynamicArray<int> array(10);

    array.set(0, 500);
    array.set(1, 600);
    array.set(2, 200);
    array.set(3, 700);
    array.set(4, 800);
    array.set(5, 100);
    array.set(6, 900);
    array.set(7, 400);
    array.set(8, 000);
    array.set(9, 300);

    Sort::Quick(array);

    for(int i = 0; i < array.length(); i++)
    {
        int ret = 0;
        array.get(i, ret);
        cout << ret << endl;
    }
}