#pragma once

#include "TreeNode.h"
#include "LinkList.h"
#include "Exception.h"

namespace data_structure
{
    template <typename T>
    class GTreeNode:public TreeNode<T>
    {
        public:

            LinkList<GTreeNode<T>*> m_child;

            GTreeNode()
            {
            }

            static GTreeNode<T>* NewNode()
            {
                GTreeNode<T>* node = new GTreeNode<T>();
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