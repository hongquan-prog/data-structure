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
#include "BTreeArray.h"
#include <unistd.h>
#include <cstring>

using namespace std;
using namespace data_structure;

void InOrderPrint(BTreeArray<char> &tree, int i)
{
    if(!tree.isNull(i))
    {
        InOrderPrint(tree, tree.left(i));
        cout << "index:" << i << "   "<< "value:" << tree[i] << endl;
        InOrderPrint(tree, tree.right(i));
    }
}

int Count2Degree(BTreeArray<char> &tree, int i)
{
    if(!tree.isNull(i))
    {
        if(!tree.isNull(tree.left(i)) && !tree.isNull(tree.right(i)))
        {
            return 1 + Count2Degree(tree, tree.left(i)) + Count2Degree(tree, tree.right(i));
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int main(void)
{
    BTreeArray<char> tree(5);
    int node;

    try
    {
        tree.set(1, 'A');

        node = tree.find('A');
        tree.set(tree.left(node), 'B');
        tree.set(tree.right(node), 'C');

        node = tree.find('C');
        tree.set(tree.left(node), 'F');
        tree.set(tree.right(node), 'G');

        cout << "length:" << tree.length() << endl;
        cout << "count:" << tree.count() << endl;

        InOrderPrint(tree, 1);
        cout << Count2Degree(tree, 1) << endl;

    }
    catch (const Exception &exception)
    {
        cout << exception.message() << endl;
    }
}