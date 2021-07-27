#pragma once

#include "DualLinkList.h"
#include "Exception.h"

namespace data_structure
{
    template <typename T>
    class DualCircleLinkList:public DualLinkList<T>
    {
    protected:
        typedef typename DualLinkList<T>::Node Node;

        int mod(int i) const
        {
            if(this->m_length > 0)
            {
                i = i % this->m_length;
            }
            else
            {
                i = 0;
            }
            return i;
        }

        // O(n)
        void first_last(void)
        {
            Node * last = this->position(this->m_length - 1)->next;
            Node * first = this->m_header.next;
            //最后一个节点指向第一个节点
            last->next = this->m_header.next;
            //第一个节点指向最后一个节点
            first->pre = last;
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
            i = (i % (this->m_length + 1));
            bool ret = DualLinkList<T>::insert(i, e);
            if(ret && (i == 0))
            {
                first_last();
            }
            
            return true;
        }

        bool add_to_tail(const T& e)
        {
            bool ret = true;
            if(this->m_length == 0)
            {
                ret = insert(0, e);
            }
            else
            {
                Node * first = this->m_header.next;
                Node * last = first->pre;
                Node * node = DualLinkList<T>::create();
                if(node)
                {
                    node->value = e;
                    node->next = first;
                    node->pre = last;
                    first->pre = node;
                    last->next = node;
                    this->m_length++;
                }
                else
                {
                    THROW_EXCEPTION(IndexOutofBoundsException, "insert failed!");
                }
            }

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
                //整个表为空时需要清除next指针，否则DualLinkList析构时会认为表非空
                if(this->m_length == 0)
                    this->m_header.next = NULL;
                else
                {
                    first_last();
                    if(this->m_current == toDel)
                        this->m_current = toDel->next;
                }
                DualLinkList<T>::destroy(toDel);
            }
            else
            {
                ret = DualLinkList<T>::remove(mod(i));
            }

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
            return DualLinkList<T>::get(mod(i));
        }
        // O(n)
        bool get(int i, T& e) const
        {
            return DualLinkList<T>::get(mod(i), e);
        }

        // O(n)
        bool set(int i, const T& e)
        {
            return DualLinkList<T>::set(mod(i), e);
        }

        // O(1)
        int length(void) const
        {
            return DualLinkList<T>::length();
        }
    
        // O(n)
        void clear(void)
        {
            while(this->m_header.next)
            {
                // O(1)
                remove(0);
            }
        }

        // O(n)
        virtual bool move(int start, int step)
        {
            return DualLinkList<T>::move(mod(start), step);
        }

        virtual bool end(void)
        {
            return ((this->m_current == NULL) || (this->m_length == 0));
        }

        ~DualCircleLinkList()
        {
            clear();
        }
    };
    
}