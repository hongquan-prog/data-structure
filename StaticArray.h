#pragma once

#include "Array.h"

namespace data_structure
{
    template <typename T, int N>
    class StaticArray:public Array<T>
    {
    protected:
        T m_space[N];
    public:

        // O(1)
        StaticArray()
        {
            this->m_array = m_space;
        }

        // O(n)
        StaticArray(const StaticArray& obj)
        {
            this->m_array = m_space;
            for(int i  = 0; i < N; i++)
            {
                m_space[i] = obj[i];
            }
        }

        // O(n)
        StaticArray& operator=(const StaticArray& obj)
        {
            if(this != & obj)
            {
                for(int i  = 0; i < N; i++)
                {
                    m_space[i] = obj[i];
                }
            }
            return *this;
        }

        // O(1)
        int length(void) const
        {
            return N;
        }
    };
}