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
    

    try
    {
        ListGraph<int, int> g(4);
        g.setEdge(0, 1, 1);
        g.setEdge(0, 2, 3);
        g.setEdge(1, 2, 1);
        g.setEdge(1, 3, 4);
        g.setEdge(2, 3, 1);

        // ListGraph<int, int> g(5);
        // g.setEdge(0, 1, 10);
        // g.setEdge(0, 4, 100);
        // g.setEdge(0, 3, 30);
        // g.setEdge(1, 2, 50);
        // g.setEdge(2, 4, 10);
        // g.setEdge(3, 2, 20);
        // g.setEdge(3, 4, 60);

        SharedPointer< Array<int> > r = g.dijkstra(0, 3, 65535);
        int weigh = 0;
        for(int i = 0; i < r->length(); i++)
        {
            cout << (*r)[i] << " ";
        }
        cout << endl;
    }
    catch(const Exception& exception)
    {
        cout << exception.message() << endl;
    }
}