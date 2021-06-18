#pragma once

#include "Tree.h"
#include "Exception.h"
#include "GTreeNode.h"

namespace data_structure
{
    template <typename T>
    class GTree:public Tree<T>
    {
    protected:
        GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const
        {
            GTreeNode<T>* ret = NULL;
            if(node != NULL)
            {
                if(node->value == value)
                {
                    return node;
                }
                else
                {
                    for(node->m_child.move(0); !node->m_child.end() && (ret == NULL); node->m_child.next())
                    {
                        ret = find(node->m_child.current(), value);
                    }
                }
            }
            return ret;
        }

        GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) const
        {
            GTreeNode<T>* ret = NULL;
            if(node != NULL)
            {
                if(node == obj)
                {
                    return node;
                }
                else
                {
                    for(node->m_child.move(0); !node->m_child.end() && (ret == NULL); node->m_child.next())
                    {
                        ret = find(node->m_child.current(), obj);
                    }
                }
            }
            return ret;
        }

    public:
        GTree()
        {

        }
        ~GTree()
        {
            clear();
        }

        bool insert(TreeNode<T>* node)
        {
            bool ret = true;
            if(node != NULL)
            {
                if(root() == NULL)
                {
                    node->parent = NULL;
                    this->m_root = node;
                }
                else
                {
                    GTreeNode<T>* np = find(node->parent);
                    if(np != NULL)
                    {
                        GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);
                        if(np->m_child.find(n) < 0)
                        {
                            np->m_child.insert(n);
                        }
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"parameter node cannot equal to NULL");
            }
            return ret;
        }

        bool insert(const T& value, TreeNode<T>* parent)
        {
            bool ret = true;

            GTreeNode<T>* node = new GTreeNode<T>();
            if(node)
            {
                node->parent = parent;
                node->value = value;
                ret = insert(node);
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree node");
            }
            

            return ret;
        }

        SharedPointer< Tree<T> > remove(const T& value)
        {
            return NULL;
        }

        SharedPointer< Tree<T> > remove(TreeNode<T>* node)
        {
            return NULL;
        }

        GTreeNode<T>* find(const T& value)const
        {
            return find(root(), value);
        }

        GTreeNode<T>* find(TreeNode<T>* node)const
        {
            return find(root(), dynamic_cast<GTreeNode<T>*>(node));
        }

        GTreeNode<T>* root() const
        {
            return dynamic_cast< GTreeNode<T>* >(this->m_root);
        }

        int degree() const
        {
            return 0;
        }
        int count() const
        {
            return 0;
        }
        int height() const
        {
            return 0;
        }
        void clear()
        {

        }
    };
}