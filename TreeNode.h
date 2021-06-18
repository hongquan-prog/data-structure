#pragma once

#include "Object.h"

namespace data_structure
{
    template <typename T>
    class TreeNode:public Object
    {
    public:
        T value;
        TreeNode<T>* parent;
        
        TreeNode()
        {
            parent = NULL;
        }

        virtual ~TreeNode();
    };

    template <typename T>
    TreeNode<T>::~TreeNode()
    {

    }
}