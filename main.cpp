#include <iostream>
#include "Exception.h"
#include "StaticArray.h"
#include "SmartPointer.h"
#include "SharedPointer.h"
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
#include "GTree.h"
#include <unistd.h>
#include <cstring>

using namespace std;
using namespace data_structure;

int main(void)
{
    GTree<char> tree;
    GTreeNode<char>* node = NULL;

    tree.insert('A', NULL);

    node = tree.find('A');
    tree.insert('B', node);
    tree.insert('C', node);
    tree.insert('D', node);

    node = tree.find('B');
    tree.insert('E', node);
    tree.insert('F', node);
    node = tree.find('E');
    tree.insert('K', node);
    tree.insert('L', node);

    node = tree.find('C');
    tree.insert('G', node);

    node = tree.find('D');
    tree.insert('H', node);
    tree.insert('I', node);
    tree.insert('J', node);
    node = tree.find('H');
    tree.insert('M', node);

    char* s = "KLFGMIJ";
    for(int i = 0; i < strlen(s); i++)
    {
        TreeNode<char>* node = tree.find(s[i]);
        while(node)
        {
            cout << node->value << " ";
            node = node->parent;
        }
        cout << endl;
    }
}