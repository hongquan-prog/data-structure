#pragma once 

#include "DualLinkList.h"

namespace data_structure
{
    template <typename T, int N>
    class DualStaticLinkList:public DualLinkList<T>
    {
    protected:
        typedef typename DualLinkList<T>::Node Node;

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
        DualStaticLinkList()
        {
            for(int i = 0; i < N; i++)
                m_used[i] = false;
        }

        Node * create(void)
        {
            Node * ret = NULL;
            for (int i = 0; i < N; i++)
            {
                if(m_used[i] == false)
                {
                    ret = reinterpret_cast<Node *>(m_array) + i;
                    ret = new (ret)SNode();
                    m_used[i] = true;
                    break;
                }
            }
            return ret;
        }

        void destroy(Node * pn)
        {
            Node * current = reinterpret_cast<Node *>(m_array);
            for (int i = 0; i < N; i++)
            {
                if(current == pn)
                {
                    m_used[i] = false;
                    break;
                }
                else
                    current++;
            }
        }

        ~DualStaticLinkList()
        {
            this->clear();
        }
    };
}