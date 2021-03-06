#pragma once

#include "LinkList.h"

namespace data_structure
{
    template <typename T, int N>
    class StaticLinkList:public LinkList<T>
    {
    protected:
        typedef typename LinkList<T>::Node Node;

        struct SNode:public Node
        {
            void* operator new(unsigned long size, void * loc)
            {
                (void)size;
                return loc;
            }
        };

        unsigned char m_array[sizeof(Node) * N];
        bool m_used[N];
    public:
        StaticLinkList()
        {
            for(int i = 0; i < N; i++)
            {
                m_used[i] = false;
            }
        }

        Node * create(void)
        {
            Node * ret = NULL;
            for(int i = 0; i < N; i++)
            {
                if(m_used[i] == false)
                {
                    ret = reinterpret_cast<Node*>(m_array) + i;
                    ret = new (ret)SNode();
                    m_used[i] = true;
                    break;
                }
            }
            return ret;
        }

        void destroy(Node * pn)
        {
            Node * array = reinterpret_cast<Node*>(m_array);

            for(int i = 0; i < N; i++)
            {
                if(array == pn)
                {
                    m_used[i] = false;
                    break;
                }
                else
                    array++;
            }
        }

        ~StaticLinkList()
        {
            this->clear();
        }
    };
}