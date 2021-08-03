#include <iostream>
#include "Exception.h"
#include "SmartPointer.h"
#include "SharedPointer.h"
#include "SeqList.h"
#include "DynamicList.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "LinkList.h"
#include "StaticLinkList.h"
#include "CircleList.h"
#include "DualCircleLinkList.h"
#include "DualLinkList.h"
#include "LinkStack.h"
#include "StaticStack.h"
#include "LinkQueue.h"
#include "StaticQueue.h"
#include "StackToQueue.h"
#include "QueueToStack.h"
#include "DTString.h"
#include "Sort.h"
#include "Search.h"
#include "GTree.h"
#include "BTree.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include <unistd.h>
#include <cstring>

using namespace std;
using namespace data_structure;

int main(void)
{
    int array[12] = {59, 95, 7, 34, 60, 168, 171, 259, 372, 45, 88, 133};

    try
    {
        bool min2_max = 0;
        Sort::Heap(array, 12, min2_max);
        cout << Search::Bolock(array, 12, 259, 2) << endl;
        for(int i = 0; i < 12; i++)
        {
            cout<< array[i] << " ";
        }
        cout<< endl;
    }
    catch(const Exception& exception)
    {
        cout << exception.message() << endl;
    }
}