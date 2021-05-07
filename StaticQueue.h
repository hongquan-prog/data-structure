#include "Queue.h"
#include <iostream>

namespace DataStructure
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
        int capacity() const
        {
            return N;
        }

        // O(1)
        void add(const T& e)
        {
            if(m_length < N)
            {
                m_space[m_rear] = e;
                m_rear = (m_rear + 1) % N;
                m_length++;
            }
            else
                throw std::range_error("Queue is full!");
        }

        // O(1)
        void remove()
        {
            if(m_length > 0)
            {
                m_front = (m_front + 1) % N;
                m_length--;
            }
            else
                throw std::range_error("Queue is empty!");
        }

        // O(1)
        T front() const
        {
            return m_space[m_front];
        }

        // O(1)
        void clear(void)
        {
            m_length = 0;
            m_front = -1;
            m_rear = -1;
        }

        // O(1)
        int length() const
        {
            return m_length;
        }

        // O(1)
        ~StaticQueue()
        {
            clear();
        }
    };
    
    
}