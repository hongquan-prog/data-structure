#pragma once

#include "Queue.h"
#include "LinkStack.h"

namespace data_structure
{
    template <typename T>
    class StackToQueue:public Queue<T>
    {
    protected:
        mutable LinkStack<T> m_stack_in;
        mutable LinkStack<T> m_stack_out;

        void in_to_out() const
        {
            if(m_stack_out.size() == 0)
            {
                while(m_stack_in.size() > 0)
                {
                    m_stack_out.push(m_stack_in.top());
                    m_stack_in.pop();
                }
            }
        }
    public:

        // O(1)
        void add(const T& e)
        {
            m_stack_in.push(e);
        }

        // O(n)
        void remove()
        {
            in_to_out();
            if(m_stack_out.size() > 0)
            {
                m_stack_out.pop();
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
            }
        }

        // O(n)
        T front() const
        {
            in_to_out();
            if(m_stack_out.size() > 0)
            {
                return m_stack_out.top();
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
            }
        }

        // O(n)
        void clear()
        {
            m_stack_out.clear();
            m_stack_in.clear();
        }

        // O(1)
        int length() const
        {
            return m_stack_in.size() + m_stack_out.size();
        }

        ~StackToQueue()
        {
            clear();
        }
    };
}