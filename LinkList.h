#pragma once

#include "List.h"
#include "Exception.h"

namespace data_structure
{
    template <typename T>
    class LinkList:public List<T>
    {
    protected:
        struct Node:public Object
        {
            T value;
            Node * next;
        };

        mutable struct:public Object
        {
            char reserve[sizeof(T)];
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
        LinkList()
        {
            m_header.next = NULL;
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
                Node * temp = create();
                if(temp != NULL)
                {
                    temp->value = e;
                    temp->next = current->next;
                    current->next = temp;
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
                if(toDel == m_current)
                    m_current = toDel->next;
                current->next = toDel->next;
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
                Node * toDel = m_header.next;
                m_header.next = toDel->next;
                destroy(toDel);
            }
        }

        virtual bool move(int start, int step = 1)
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
            while(m_current && (i < m_step))
            {
                i++;
                m_current = m_current->next;
            }
            return (i == m_step);
        }

        virtual T current(void)
        {
            return m_current->value;
        }

        ~LinkList()
        {
            clear();
        }
    };
}