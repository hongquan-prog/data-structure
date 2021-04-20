#pragma once

#include "LinkList.h"

namespace DataStructure
{
    template <typename T>
    class CircleList:public LinkList<T>
    {
    protected:
        typedef typename LinkList<T>::Node Node;
        
        // O(n)
        Node * last(void)
        {
            return LinkList<T>::position(this->m_length - 1)->next;
        }

        // O(n)
        void last_to_first()
        {
            last()->next = this->m_head.next;
        }

        // O(1)
        int mod(int i) const
        {
            if(this->m_length == 0)
                return 0;
            else
                return i % this->m_length;
        }
    public:

        // O(n)
        bool insert(const T& e)
        {
            return insert(this->m_length, e);
        }

        // O(2n+1) = O(n)
        bool insert(int i, const T& e)
        {
            bool ret = true;
            // i 的区间在0～m_length之间，所以归一化还要加一
            // O(1)
            i = i % (this->m_length + 1);
            // O(n)
            ret = LinkList<T>::insert(i, e);
            if(i == 0)
            {
                // O(n)
                last_to_first();
            }
            return ret;
        }

        // O(2n) = O(n)
        bool remove(int i)
        {
            bool ret = true;

            i = mod(i);
            
            // O(n)
            if(i == 0)
            {
                Node * toDel = this->m_head.next;
                if(toDel != NULL)
                {
                    this->m_head.next = toDel->next;
                    this->m_length--;
                    if(this->m_length > 0)
                    {
                        last_to_first();
                        if(this->m_current == toDel)
                            this->m_current = toDel->next;
                    }
                    else
                    {
                        this->m_current = NULL;
                        this->m_head.next = NULL;
                    }
                    LinkList<T>::destroy(toDel);
                }
                else
                {
                    ret = false;
                }
            }
            // O(n)
            else
                ret = LinkList<T>::remove(i);
            return ret;
        }

        // O(n)
        bool set(int i, const T& e)
        {
            return LinkList<T>::set(mod(i), e);
        }

        // O(n)
        T get(int i) const
        {
            return LinkList<T>::get(mod(i));
        }
        // O(n)
        bool get(int i, const T& e) const
        {
            return LinkList<T>::get(mod(i), e);
        }

        // O(n)
        int find(const T& e) const
        {
            int ret = -1;

            Node * slider = this->m_head.next;
            for(int i = 0; i < this->m_length; i++)
            {
                if(slider->data == e)
                {
                    ret = i;
                    break;
                }
                slider = slider->next;
            }
            return ret;
        }

        // O(n)
        void clear(void)
        {
            //删除1位置和删除单链表一样，但是如果删除0每次都需要大量遍历
            // O(n)
            while (this->m_length > 1)
            {
                remove(1); // O(1)
            }
            //最后处理特殊位置
            if(this->m_length == 1)
            {
                Node * toDel = this->m_head.next;
                this->m_head.next = NULL;
                this->m_length = 0;
                this->m_current = NULL;
                LinkList<T>::destroy(toDel);
            }
        }

        // O(n)
        ~CircleList()
        {
            clear();
        }

        // O(n)
        bool move(int i, int step = 1)
        {
            return LinkList<T>::move(mod(i), step);
        }

        // O(1)
        bool end()
        {
            return (this->m_length == 0)||(this->m_current == NULL);
        }
    };
}