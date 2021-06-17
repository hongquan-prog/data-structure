#pragma once

#include "List.h"
#include "Exception.h"

namespace data_structure
{
    template <typename T>
    class DualLinkList:public List<T>
    {
    protected:
        struct Node:public Object
        {
            T value;
            Node * pre;
            Node * next;
        };

        mutable struct:public Object
        {
            char reserve[sizeof(T)];
            Node * pre;
            Node* next;
        }m_header;

        int m_length;
        int m_step;
        Node * m_current;

        Node * position(int position) const
        {
            Node * current = reinterpret_cast<Node *>(&m_header);
            for(int i = 0; i < position; i++)
            {
                current = current->next;
            }
            return current; 
        }

        virtual Node * create(void)
        {
            return new Node;
        }

        virtual void destroy(Node * pn)
        {
            delete pn;
        }

    public:

        // O(1)
        DualLinkList()
        {
            m_header.next = NULL;
            m_header.pre = NULL;
            m_current = NULL;
            m_step = 0;
            m_length = 0;
        }

        // O(n)
        bool insert(const T& e)
        {
            return insert(m_length, e);
        }

        // O(n)
        bool insert(int i, const T& e)
        {
            if(i >= 0 && i <= m_length)
            {
                Node * current = position(i);
                Node * next = current->next;
                Node * node = create();
                if(node != NULL)
                {
                    node->value = e;
                    // 1、新节点的next指向下一个节点
                    node->next = next;
                    // 2、插入位置是0的时候 node->pre = NULL
                    if(current != reinterpret_cast<Node *>(&m_header))
                        node->pre = current;
                    else
                        node->pre = NULL;
                    // 3、当前节点next指向新节点
                    current->next = node;
                    // 4、下一个节点存在时，pre指向当前节点
                    if(next)
                        next->pre = node;
                    m_length ++;
                }
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "insert failed!");
            }
            return true;
        }

        // O(n)
        bool remove(int i)
        {
            if(i >= 0 && i < m_length)
            {
                Node * current = position(i);
                Node * toDel = current->next;
                Node * next = toDel->next;

                if(toDel == m_current)
                {
                    m_current = toDel->next;
                }

                //当前节点指向删除点后一个节点
                current->next = next;
                //后继存在，指向删除点前一个节点
                if(next)
                {
                    next->pre = toDel->pre;
                }

                m_length --;
                destroy(toDel);
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "remove failed!");
            }
            return true;
        }

        // O(n)
        int find(const T& e) const
        {
            int ret = -1;
            int i = 0;
            Node * node = m_header.next;

            while(node)
            {
                if(node->value == e)
                {
                    ret = i;
                    break;
                }
                else
                {
                    node = node->next;
                    i++;
                }
            }

            return ret;
        }

        // O(n)
        bool get(int i, T& e) const
        {
            if(i >= 0 && i < m_length)
            {
                e = position(i)->next->value;
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "get failed!");
            }
            return true;
        }

        virtual T get(int i) const
        {
            if(i >= 0 && i < m_length)
            {
                return position(i)->next->value;
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "get failed!");
            }
            return true;
        }

        // O(n)
        bool set(int i, const T& e)
        {
            if(i >= 0 && i < m_length)
            {
                position(i)->next->value = e;
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "set failed!");
            }
            return true;
        }

        // O(1)
        int length(void) const
        {
            return m_length;
        }

        // O(n)
        void clear(void)
        {
            while(m_header.next)
            {
                remove(0);
            }
        }

        virtual bool move(int start, int step)
        {
            bool ret = true;
            if((start >= 0) && (start < m_length))
            {
                m_current = position(start)->next;
                m_step = step;
            }
            else
            {
                ret = false;
            }
            return ret;
        }

        virtual bool end(void)
        {
            return (m_current == NULL);
        }

        virtual bool next(void)
        {
            int i = 0;

            while(!end() && (i < m_step))
            {
                i++;
                m_current = m_current->next;
            }
            
            return (i == m_step);
        }

        virtual bool pre(void)
        {
            int i = 0;
            while(!end() && (i < this->m_step))
            {
                i++;
                this->m_current = this->m_current->pre;
            }
            return (i == this->m_step);
        }

        virtual T current(void)
        {
            return m_current->value;
        }

        ~DualLinkList()
        {
            clear();
        }
    };
}