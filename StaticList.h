#pragma once

#include "SeqList.h"

namespace DataStructure
{
    template <typename T, int N>
    class StaticList:public SeqList<T>
    {
        protected:
            T m_space[N];
        public:

            StaticList()
            {
                this->m_array = m_space;
                this->m_length = 0;
            }

            int capacity(void)const
            {
                return N;
            }
    };
}