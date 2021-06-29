#pragma once

#include "Tree.h"
#include "BTreeNode.h"
#include "SharedPointer.h"
#include "DynamicArray.h"
#include "LinkQueue.h"

namespace data_structure
{
    enum BTNodePos
    {
        ANY,
        LEFT,
        RIGHT
    };

    enum BTTraversal
    {
        PreOrder,
        InOrder,
        PostOrder,
        LevelOrder
    };

    template <typename T>
    class BTree:public Tree<T>
    {
    protected:
        LinkQueue<BTreeNode<T>*> m_queue;
        BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const
        {
            BTreeNode<T>* ret = NULL;
            if(node)
            {
                if(node->value == value)
                {
                    return node;
                }
                if(node->left)
                {
                    ret = find(node->left, value);
                }
                if((ret == NULL) && node->right)
                {
                    ret = find(node->right, value);
                }
            }
            return ret;
        }

        BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const
        {
            BTreeNode<T>* ret = NULL;
            if(node)
            {
                if(node == obj)
                {
                    return node;
                }
                if(node->left)
                {
                    ret = find(node->left, obj);
                }
                if((ret == NULL) && node->right)
                {
                    ret = find(node->right, obj);
                }
            }
            return ret;
        }

        int degree(BTreeNode<T>* node) const
        {
            int ret = 0;

            if(node == NULL)
            {
                return 0;
            }
            else
            {
                ret = !!(node->left) + !!(node->right);
                if(ret < 2)
                {
                    int left = degree(node->left);
                    ret = (ret < left)?(left):(ret);
                }
                if(ret < 2)
                {
                    int right = degree(node->right);
                    ret = (ret < right)?(right):(ret);
                }
            }
            return ret;
        }

        int count(BTreeNode<T>* node) const
        {
            int ret = 0;
            if(NULL == node)
            {
                return 0;
            }
            else
            {
                ret += count(node->left) + count(node->right) + 1;
            }
            return ret;
        }

        int height(BTreeNode<T>* node) const
        {
            int ret = 0;
            if(NULL == node)
            {
                return 0;
            }
            else
            {
                int left = height(node->left);
                int right = height(node->right);
                ret = (left < right) ? (right + 1) : (left + 1);
            }
            return ret;
        }

        void remove(BTreeNode<T>* node, BTree<T>*& ret)
        {
            ret = new BTree<T>();
            if(ret)
            {
                if(root() == node)
                {
                    this->m_root = NULL;
                }
                else
                {
                    BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);
                
                    if(parent->left == node)
                    {
                        // node->parent->left = NULL;
                        parent->left = NULL;
                    }
                    else if(parent->right == node)
                    {
                        parent->right = NULL;
                    }
                    node->parent = NULL;
                }
                ret->m_root = node;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create node ...");
            }
        }

        void free(BTreeNode<T>* node)
        {
            if(node == NULL)
            {
                return;
            }
            else
            {
                free(node->left);
                free(node->right);
                if(node->flag())
                {
                    delete node;
                }
            }
        }

        void preOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
        {
            if(node != NULL)
            {
                queue.add(node);
                preOrderTraversal(node->left, queue);
                preOrderTraversal(node->right, queue);
            }
        }

        void inOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
        {
            if(node != NULL)
            {
                inOrderTraversal(node->left, queue);
                queue.add(node);
                inOrderTraversal(node->right, queue);
            }
        }

        void postOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
        {
            if(node != NULL)
            {
                postOrderTraversal(node->left, queue);
                postOrderTraversal(node->right, queue);
                queue.add(node);
            }
        }

        void levelOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
        {
            if(node != NULL)
            {
                LinkQueue<BTreeNode<T>*> temp;
                temp.add(node);
                while(temp.length() > 0)
                {
                    BTreeNode<T>* n = temp.front();
                    if(n->left)
                    {
                        temp.add(n->left);
                    }
                    if(n->right)
                    {
                        temp.add(n->right);
                    }
                    temp.remove();
                    queue.add(n);
                }
            }
        }

        BTreeNode<T>* clone(BTreeNode<T>* node) const
        {
            BTreeNode<T>* ret = NULL;
            if(node != NULL)
            {
                ret = BTreeNode<T>::NewNode();
                if(ret)
                {
                    ret->value = node->value;
                    ret->parent = NULL;

                    ret->left = clone(node->left);
                    if(ret->left)
                    {
                        ret->left->parent = ret;
                    }
                    ret->right = clone(node->right);
                    if(ret->right)
                    {
                        ret->right->parent = ret;
                    }
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create node ...");
                }
            }
            return ret;
        }

        bool equal(BTreeNode<T>* lh, BTreeNode<T>* rh)
        {
            if(lh == rh)
            {
                return true;
            }
            else if((lh != NULL) && (rh != NULL))
            {
                return (lh->value == rh->value) && equal(lh->left, rh->left) && equal(lh->right, rh->right);
            }
            else
            {
                return false;
            }
        }

        BTreeNode<T>* add(BTreeNode<T>* lh, BTreeNode<T>* rh) const
        {
            BTreeNode<T>* ret = NULL;
            if((lh == NULL) && (rh != NULL))
            {
                ret = clone(rh);
            }
            else if((lh != NULL) && (rh == NULL))
            {
                ret = clone(lh);
            }
            else if(lh && rh)
            {
                ret = BTreeNode<T>::NewNode();
                if(ret)
                {
                    ret->value = lh->value + rh->value;
                    ret->parent = NULL;
                    ret->left = add(lh->left, rh->left);
                    ret->right = add(lh->right, rh->right);
                    if(ret->left)
                    {
                        ret->left->parent = ret;
                    }
                    if(ret->right)
                    {
                        ret->right->parent = ret;
                    }
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create node ...");
                }
            }

            return ret;
        }

        void traversal(BTTraversal order, LinkQueue<BTreeNode<T>*>& queue)
        {
            switch (order)
            {
            case PreOrder:
                preOrderTraversal(root(), queue);
                break;
            case InOrder:
                inOrderTraversal(root(), queue);
                break;
            case PostOrder:
                postOrderTraversal(root(), queue);
                break;
            case LevelOrder:
                levelOrderTraversal(root(), queue);
                break;
            default:
                THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid ...");
                break;
            }
        }
    public:

        bool insert(TreeNode<T>* node)
        {
            return insert(node, ANY);
        }

        bool insert(TreeNode<T>* node, BTNodePos pos)
        {
            bool ret = true;

            if(node)
            {
                if(root() == NULL)
                {
                    node->parent = NULL;
                    this->m_root = node;
                }
                else
                {
                    BTreeNode<T>* parent = find(node->parent);
                    if(parent)
                    {
                        if(((pos == LEFT) || (pos == ANY)) && (NULL == parent->left))
                        {
                            parent->left = dynamic_cast<BTreeNode<T>*>(node);
                            node->parent = parent;
                        }
                        else if(((pos == RIGHT) || (pos == ANY)) && (NULL == parent->right))
                        {
                            parent->right = dynamic_cast<BTreeNode<T>*>(node);
                            node->parent = parent;
                        }
                        else
                        {
                            ret = false;
                        }
                    }
                    else
                    {
                        ret = false;
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
            return insert(value, parent, ANY);
        }

        bool insert(const T& value, TreeNode<T>* parent, BTNodePos pos)
        {
            bool ret = true;

            BTreeNode<T>* node = BTreeNode<T>::NewNode();
            if(node)
            {
                node->parent = parent;
                node->value = value;
                ret = insert(node, pos);
                if(false == ret)
                {
                    delete node;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree node ...");
            }
            return ret;
        }

        SharedPointer< Tree<T> > remove(const T& value)
        {
            BTree<T>* ret = NULL;
            BTreeNode<T>* node = find(value);

            if(node == NULL)
            {
                THROW_EXCEPTION(InvalidParameterException, "Can not find the node via parameter value ...");
            }
            else
            {
                remove(node, ret);
            }
            return ret;
        }

        SharedPointer< Tree<T> > remove(TreeNode<T>* node)
        {
            BTree<T>* ret = NULL;

            if(node == NULL)
            {
                THROW_EXCEPTION(InvalidParameterException, "Can not find the node via parameter value ...");
            }
            else
            {
                remove(dynamic_cast<BTreeNode<T>*>(node), ret);
            }
            return ret;
        }

        BTreeNode<T>* find(const T& value)const
        {
            return find(dynamic_cast<BTreeNode<T>*>(this->m_root), value);
        }

        BTreeNode<T>* find(TreeNode<T>* node)const
        {
            return find(dynamic_cast<BTreeNode<T>*>(this->m_root), dynamic_cast<BTreeNode<T>*>(node));
        }

        BTreeNode<T>* root() const
        {
            return dynamic_cast<BTreeNode<T>*>(this->m_root);
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
                BTreeNode<T>* node = m_queue.front();
                m_queue.remove();
                if(node->left)
                {
                    m_queue.add(node->left);
                }
                if(node->right)
                {
                    m_queue.add(node->right);
                }
            }
            return ret;
        }

        T current()
        {
            return m_queue.front()->value;
        }

        SharedPointer< Array<T> > traversal(BTTraversal order)
        {
            DynamicArray<T>* ret = NULL;
            LinkQueue<BTreeNode<T>*> queue;

            traversal(order, queue);
            ret = new DynamicArray<T>(queue.length());
            if(ret)
            {
                for(int i = 0; i < ret->length(); i++)
                {
                    ret->set(i, queue.front()->value);
                    queue.remove();
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to create DynamicArray ...");
            }
            return ret;
        }

        BTreeNode<T>* connect(LinkQueue<BTreeNode<T>*>& queue)
        {
            BTreeNode<T>* ret = NULL;
            if(queue.length() > 0)
            {
                ret = queue.front();
                BTreeNode<T>* slider = ret;
                queue.remove();
                slider->left = NULL;

                while (queue.length() > 0)
                {
                    slider->right = queue.front();
                    queue.front()->left = slider;
                    slider = queue.front();
                    queue.remove();
                }
                slider->right = NULL;
            }
            return ret;
        }
        
        BTreeNode<T>* thread(BTTraversal order)
        {
            LinkQueue<BTreeNode<T>*> queue;
            BTreeNode<T>* ret = NULL;

            //遍历
            traversal(order, queue);

            //连接双向链表
            ret = connect(queue);

            //清空二叉树
            this->m_queue.clear();
            this->m_root = NULL;

            return ret;
        }

        SharedPointer< BTree<T> > clone() const
        {
            BTree<T>* ret = new BTree<T>();
            if(ret)
            {
                ret->m_root = clone(root());
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to create BTree object...");
            }
            return ret;
        }

        bool operator == (const BTree<T>& btree)
        {
            return equal(root(), btree.root());
        }

        bool operator != (const BTree<T>& btree)
        {
            return !(*this == btree);
        }

        SharedPointer< BTree<T> > add(const BTree<T>& btree) const
        {
            BTree<T> * ret = new BTree<T>();
            if(ret)
            {
                ret->m_root = add(root(), btree.root());
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to create BTree object...");
            }
            return ret;
        }

        ~BTree()
        {
            clear();
        }
    };
}