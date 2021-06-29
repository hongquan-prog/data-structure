#pragma once

#include "Tree.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "GTreeNode.h"
#include "SharedPointer.h"

namespace data_structure
{
    template <typename T>
    class GTree:public Tree<T>
    {
    protected:
        LinkQueue<GTreeNode<T>*> m_queue; 

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

        void free(GTreeNode<T>* node)
        {
            if(node == NULL)
            {
                return;
            }
            else
            {
                for(node->m_child.move(0); !node->m_child.end(); node->m_child.next())
                {
                    free(node->m_child.current());
                }
                if(node->flag())
                {
                    delete node;
                }
            }
        }

        void remove(GTreeNode<T>* node, GTree<T>*& ret)
        {
            ret = new GTree<T>();
            if(ret)
            {
                if(root() == node)
                {
                    this->m_root = NULL;
                }
                else
                {
                    LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->m_child;
                    child.remove(child.find(node));
                    node->parent = NULL;
                }
                ret->m_root = node;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree");
            }
        }

        int count(GTreeNode<T>* node) const
        {
            int ret = 0;
            if(node)
            {
                ret  = 1;
                for(node->m_child.move(0); !(node->m_child.end()); node->m_child.next())
                {
                    ret += count(node->m_child.current());
                }
            }
            return ret;
        }

        int height(GTreeNode<T>* node) const
        {
            int ret = 0;
            if(node)
            {
                for(node->m_child.move(0); !(node->m_child.end()); node->m_child.next())
                {
                   int h = height(node->m_child.current());
                   if(h > ret)
                   {
                       ret = h;
                   }
                }
                ret = ret + 1;
            }
            return ret;
        }

        int degree(GTreeNode<T>* node) const
        {
            int ret = 0;
            if(node)
            {
                ret = node->m_child.length();
                for(node->m_child.move(0); !(node->m_child.end()); node->m_child.next())
                {
                    int d = degree(node->m_child.current());
                    if(d > ret)
                    {
                        ret = d;
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

            GTreeNode<T>* node = GTreeNode<T>::NewNode();
            if(node)
            {
                node->parent = parent;
                node->value = value;
                ret = insert(node);
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree node ...");
            }
        
            return ret;
        }

        SharedPointer< Tree<T> > remove(const T& value)
        {
            GTree<T>* ret = NULL;
            GTreeNode<T>* node = find(value);

            if(node == NULL)
            {
                THROW_EXCEPTION(InvalidParameterException, "Can not find the node via parameter value ...");
            }
            else
            {
                remove(node, ret);
                m_queue.clear();
            }
            return ret;
        }

        SharedPointer< Tree<T> > remove(TreeNode<T>* node)
        {
            GTree<T>* ret = NULL;
            node = find(node);

            if(node == NULL)
            {
                THROW_EXCEPTION(InvalidParameterException, "Parameter is invalid ...");
            }
            else
            {
                remove(dynamic_cast<GTreeNode<T>*>(node), ret);
                m_queue.clear();
            }
            return ret;
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
            return degree(root());
        }
        int count() const
        {
            return count(root());
        }
        int height() const
        {
            return height(root());
        }
        void clear()
        {
            free(root());
            this->m_root = NULL;
            m_queue.clear();
        }

        bool begin()
        {
            bool ret = (root() != NULL);
            if(ret)
            {
                m_queue.clear();
                m_queue.add(root());
            }
            return ret;
        }

        bool end()
        {
            return (m_queue.length() == 0);
        }
        
        bool next()
        {
            bool ret = (m_queue.length() != 0);
            if(ret)
            {
                GTreeNode<T>* node = m_queue.front();
                m_queue.remove();
                for(node->m_child.move(0); !(node->m_child.end()); node->m_child.next())
                {
                    m_queue.add(node->m_child.current());
                }
            }
            return ret;
        }

        T current()
        {
            if(!end())
            {
                return m_queue.front()->value;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
            }
        }

    };
}