#pragma once

#include "LinkList.h"
#include <iostream>

namespace DataStructure
{
    template <typename T,int N>
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
        
        unsigned char m_space[sizeof(SNode) * N];
        int m_used[N];

        Node * create()
        {
            SNode * ret = NULL;

            for(int i = 0; i < N; i++)
            {
                if(!m_used[i])
                {
                    ret = reinterpret_cast<SNode *>(m_space) + i;
                    ret = new (ret)SNode();
                    m_used[i] = true;
                    break;
                }
            }

            return ret;
        }

        void destroy(Node * pn)
        {
            SNode* space = reinterpret_cast<SNode *>(m_space);
            SNode* spn = reinterpret_cast<SNode *>(pn);
            for(int i = 0; i < N; i++)
            {
                if(pn == (space + i))
                {
                    m_used[i] = false;
                    spn->~SNode();
                    break;
                }
            }
        }
    public:

        StaticLinkList()
        {
            for(int i = 0; i < N; i++)
            {
                m_used[i] = false;
            }
        }

        int capacity()
        {
            return N;
        }

        ~StaticLinkList()
        {
           this->clear();
        }
    };
}