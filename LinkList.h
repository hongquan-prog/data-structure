#pragma once

#include <iostream>
#include "List.h"

namespace DataStructure
{
    template <typename T>
    class LinkList:public List<T>
    {
    public:
        struct Node
        {
            T data;
            Node* next;
        };

    protected:
        // 为了防止自定义类型无参构造函数抛出异常
        mutable struct{
            char reserve[sizeof(T)];
            Node* next;
        }m_head;

        int m_step;
        int m_length;
        Node * m_current;
        
        //O(n)
        Node * position(int i) const     
        {
            Node * current = reinterpret_cast<Node *>(&m_head);
            for(int p = 0; p < i; p++)
            {
                current = current->next;
            }
            return current;
        }

        virtual Node * create()
        {
            return new Node;
        }

        virtual void destroy(Node * pn)
        {
            delete pn;
        }
    public:
        LinkList()
        {
            m_current = NULL;
            m_step = 0;
            m_head.next = NULL;
            m_length = 0;
        }
        bool insert(const T& e)
        {
            return insert(m_length, e);
        }
        //O(n)
        bool insert(int i, const T& e)
        {
            bool ret = ((i >= 0) && (i <= m_length));
            if(ret)
            {
                Node * temp = create();
                if(temp)
                {
                    Node * current = position(i);    
                    temp->data = e;
                    temp->next = current->next;
                    current->next = temp;
                    ++m_length;
                    return true;
                }
            }
            return false;
        }
        //O(n)
        bool remove(int i)
        {
            bool ret = ((i >= 0) && (i < m_length));

            if(ret)
            {
                Node * current = position(i);
                Node *del = current->next;
                if(m_current == del)
                {
                    m_current = del->next;
                }
                current->next = del->next;
                --m_length;
                destroy(del);
                return true;
            }
            return false;
        }
        //O(n)
        bool get(int i, T& e) const
        {
            bool ret = ((i >= 0) && (i < m_length));

            if(ret)
            {
                Node * current = position(i);
                e = current->next->data;
                return true;
            }
            return false;
        }

        T get(int i) const
        {
            T ret = 0;

            if(get(i, ret))
                return ret;
            else
                throw std::bad_alloc();
            return ret;
        }
        //O(n)
        bool set(int i, const T& e)
        {
            bool ret = ((i >= 0) && (i < m_length));

            if(ret)
            {
                Node * current = position(i);
                current->next->data = e;
                return true;
            }
            return false;
        }
        //O(1)
        int length(void) const
        {
            return m_length;
        }
        //O(n)
        void clear(void)
        {
            Node * current = reinterpret_cast<Node *>(&m_head);
            while(current->next)
            {
                Node * del = current->next;
                current->next = del->next;
                destroy(del);
                --m_length;
            }
        }
        //O(n)
        int find(const T& e) const
        {
            int i = 0;

            Node * current = reinterpret_cast<Node *>(&m_head); 
            while (current->next)
            {
                if(current->next->data == e)
                {
                    return i;
                }
                else
                {
                    ++i;
                    current = current->next;
                }
            }
            
            return -1;
        }

        bool move(int i, int step = 1)
        {
            bool ret = (i >= 0 && i < m_length && step > 0);

            if(ret)
            {
                m_current = position(i)->next;
                m_step = step;
            }
            return ret;
        }

        bool end()
        {
            return (m_current == NULL);
        }

        T current()
        {
            return m_current->data;
        }

        bool next()
        {
            int i = 0;
            while(!end() && (i < m_step))
            {
                m_current = m_current->next;
                i++;
            }
            return (i == m_step);
        }

        ~LinkList()
        {
            clear();
        }
    };
}