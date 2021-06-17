#pragma once

#include "Queue.h"

namespace data_structure
{
    template <typename T, int N>
    class StaticQueue:public Queue<T>
    {
    protected:
        T m_space[N];
        int m_length;
        int m_front;
        int m_rear;
    public:

        // O(1)
        StaticQueue()
        {
            m_length = 0;
            m_front = 0;
            m_rear = 0;
        }

        // O(1)
        void add(const T& e)
        {
            if((m_length == N) && (m_rear == m_front))
            {
                THROW_EXCEPTION(InvalidOperationException, "No Space in current stack ...");
            }
            else
            {
                m_space[m_rear] = e;
                m_rear = (m_rear + 1) % N;
                m_length ++;
            }
        }
        
        // O(1)
        void remove()
        {
            if((m_length == 0) && (m_rear == m_front))
            {
                THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
            }
            else
            {
                m_front = (m_front + 1) % N;
                m_length--;
            }
        }

        // O(1)
        T front() const
        {
            if((m_length == 0) && (m_rear == m_front))
            {
                THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
            }
            else
            {
                return m_space[m_front];
            }
        }

        // O(1)
        void clear()
        {
            m_front = 0;
            m_length = 0;
            m_rear = 0;
        }

        // O(1)
        int length() const
        {
            return m_length;
        }

        // O(1)
        int capacity() const
        {
            return N;
        }
        

        // O(1)
        ~StaticQueue()
        {
            clear();
        }
    };
}