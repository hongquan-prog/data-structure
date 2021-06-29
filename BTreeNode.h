#pragma once

#include "TreeNode.h"

namespace data_structure
{
    template <typename T>
    struct BTreeNode:public TreeNode<T>
    {
    public:
        BTreeNode<T> * left;
        BTreeNode<T> * right;

        BTreeNode()
        {
            left = NULL;
            right = NULL;
        }

        static BTreeNode<T>* NewNode()
        {
            BTreeNode<T>* node = new BTreeNode<T>();
            if(node)
            {
                node->m_flag = true;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to creat node");
            }
            return node;
        }
    };
    
}