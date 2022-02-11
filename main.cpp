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
#include "RangeArray.h"
#include <unistd.h>
#include <cstring>

using namespace std;
using namespace data_structure;

int main(void)
{
    RangeArray<float> array(-5, 5);

    try
    {

        for(int i = array.lower(); i <= array.upper(); i++)
        {
            array[i] = i / 10.0;
        }

        const RangeArray<float>& const_array = array;

        for(int i = array.lower(); i <= array.upper(); i++)
        {
            cout << const_array[i] << endl;
        }
    }
    catch(const Exception& exception)
    {
        cout << exception.message() << endl;
    }
}