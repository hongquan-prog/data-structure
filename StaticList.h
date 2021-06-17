#pragma once

#include "SeqList.h"
#include "Exception.h"

namespace data_structure
{
    template <typename T, int N>
    class StaticList:public Seqlist<T>
    {
    protected:
        T m_space[N];

    public:

        // O(1)
        StaticList()
        {
            this->m_array = m_space;
            this->m_length = 0;
        }

        // O(1)
        int capacity(void)const
        {
            return N;
        }

    };
}