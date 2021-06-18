#pragma once

#include "TreeNode.h"
#include "LinkList.h"

namespace data_structure
{
    template <typename T>
    class GTreeNode:public TreeNode<T>
    {
        public:
            LinkList<GTreeNode<T>*> m_child;
        
    };
}