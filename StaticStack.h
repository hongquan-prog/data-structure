#pragma once

#include "Stack.h"
#include <iostream>

namespace DataStructure
{
    template <typename T, int N>
    class StaticStack:public Stack<T>
    {
    protected:
        // 缺陷在于类型为自定义类时会多次调用构造函数
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
        int capacity(void) const
        {
            return N;
        }

        // O(1)
        void push(const T& e)
        {
            if(m_size < N)
            {
                // 异常安全
                m_space[m_top + 1] = e;
                m_top ++;
                m_size ++;
            }
            else
                throw std::range_error("Stack is full!");
        }
        
        // O(1)
        void pop()
        {
            if(m_size > 0)
            {
                m_top --;
                m_size --;
            }
            else
                throw std::range_error("No element in current stack!");
        }

        // O(1)
        T top()
        {
            if(m_size > 0)
            {
                return m_space[m_top];
            }
            else
            {
                throw std::range_error("Parameter i is invalid!");
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
        ~StaticStack()
        {
            clear();
        }
    };
}