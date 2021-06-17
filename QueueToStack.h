#pragma once

#include "Stack.h"
#include "LinkQueue.h"

namespace data_structure
{
    template <typename T>
    class QueueToStack:public Stack<T>
    {
    protected:
        LinkQueue<T> m_queue1;
        LinkQueue<T> m_queue2;
        LinkQueue<T> * m_in;
        LinkQueue<T> * m_out;

        // O(n)
        void move() const
        {
            int n = m_in->length() - 1;
            for(int i = 0; i < n; i++)
            {
                m_out->add(m_in->front());
                m_in->remove();
            }
        }

        // O(1)
        void exchange()
        {
            LinkQueue<T> * temp = m_in;
            m_in = m_out;
            m_out = temp;
        }

    public:
        // O(1)
        QueueToStack(/* args */)
        {
            m_in = &m_queue1;
            m_out = &m_queue2;
        }

        // O(1)
        void push(const T& e)
        {
            m_in->add(e);
        }

        // O(n)
        void pop()
        {
            if(m_in->length() > 0)
            {
                move();
                m_in->remove();
                exchange();
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
            }
        }

        // O(n)
        T top() const
        {
            if(m_in->length() > 0)
            {
                move();
                return m_in->front();
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
            }
        }

        // O(n)
        void clear()
        {
            m_in->clear();
            m_out->clear();
        }

        // O(1)
        int size() const
        {
            return m_in->length() + m_out->length();
        }

        // O(n)
        ~QueueToStack()
        {
            clear();
        }
    };
    
}