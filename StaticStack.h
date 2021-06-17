#pragma once

#include "Stack.h"

namespace data_structure
{
    template <typename T, int N>
    class StaticStack:public Stack<T>
    {
    protected:
        T m_space[N];
        int m_top;
        int m_size;
    public:

        // O(1)
        StaticStack()
        {
            m_top = -1;
            m_size = 0;
        }

        // O(1)
        void push(const T& e)
        {
            if(m_size < N)
            {
                m_space[m_top + 1] = e;
                m_top++;
                m_size++;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No Space in current stack ...");
            }
        }

        // O(1)
        void pop()
        {
            if(m_size > 0)
            {
                m_top--;
                m_size--;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
            }
        }

        // O(1)
        T top() const
        {
            if(m_size > 0)
            {
                return m_space[m_top];
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
            }
        }

        // O(1)
        void clear()
        {
            m_top = -1;
            m_size = 0;
        }

        // O(1)
        int size() const
        {
            return m_size;
        }

        // O(1)
        int capacity() const
        {
            return N;
        }

        ~StaticStack()
        {
            clear();
        }
    };
};