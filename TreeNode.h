#pragma once

#include "Object.h"

namespace data_structure
{
    template <typename T>
    class TreeNode:public Object
    {
    protected:
        bool m_flag;

        TreeNode(const TreeNode<T>&);
        TreeNode<T>& operator= (const TreeNode<T>&);

        void * operator new(size_t size) throw()
        {
            return Object::operator new(size);
        }

    public:
        T value;
        TreeNode<T>* parent;
            
        bool flag()
        {
            return m_flag;
        }
        
        TreeNode()
        {
            parent = NULL;
            m_flag = false;
        }

        virtual ~TreeNode();
    };

    template <typename T>
    TreeNode<T>::~TreeNode()
    {

    }
}