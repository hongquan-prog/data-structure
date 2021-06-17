#pragma once

#include "LinkList.h"

namespace data_structure
{
    template <typename T>
    class CircleList:public LinkList<T>
    {
    protected:
        typedef typename LinkList<T>::Node Node;

        // O(n)
        Node * last(void)
        {
            // 此处指向最后一个节点本身时，position后面还得加一个next
            return LinkList<T>::position(this->m_length - 1)->next;
        }

        // O(n)
        void last_to_first()
        {
            last()->next = this->m_header.next;
        }

        // O(1)
        int mod(int i) const
        {
            if(this->m_length == 0)
                return 0;
            else
                return (i % this->m_length);
        }

    public:

        // O(n)
        bool insert(const T& e)
        {
            return insert(this->m_length, e);
        }
        
        // O(n)
        bool insert(int i, const T& e)
        {
            bool ret = true;

            i = (i % (this->m_length + 1));
            ret = LinkList<T>::insert(i, e);
            if(ret && (0 == i))
                last_to_first();
            return ret;
        }

        // O(n)
        bool remove(int i)
        {
            bool ret = true;

            if(mod(i) == 0)
            {
                Node * toDel = this->m_header.next;
                this->m_header.next = toDel->next;
                this->m_length --;
                if(this->m_length == 0)
                    this->m_header.next = NULL;
                else
                {
                    last_to_first();
                    if(this->m_current == toDel)
                    {
                        this->m_current = toDel->next;
                    }
                }
                LinkList<T>::destroy(toDel);
            }
            else
                LinkList<T>::remove(mod(i));

            return ret;
        }

        // O(n)
        int find(const T& e) const
        {
            int ret = -1;
            int i = 0;
            Node * node = this->m_header.next;

            for(int i = 0; i < this->m_length; i++)
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
        T get(int i) const
        {
            return LinkList<T>::get(mod(i));
        }
        // O(n)
        bool get(int i, T& e) const
        {
            return LinkList<T>::get(mod(i), e);
        }

        // O(n)
        bool set(int i, const T& e)
        {
            return LinkList<T>::set(mod(i), e);
        }

        // O(1)
        int length(void) const
        {
            return LinkList<T>::length();
        }
    
        // O(n)
        void clear(void)
        {
            while(this->m_length > 1)
            {
                // O(1)
                remove(1);
            }
            if(this->m_length == 1)
                remove(0);
        }

        virtual bool move(int start, int step)
        {
            return LinkList<T>::move(mod(start), step);
        }

        virtual bool end(void)
        {
            return ((this->m_current == NULL) || (this->m_length == 0));
        }

        ~CircleList()
        {
            clear();
        }
    };
}