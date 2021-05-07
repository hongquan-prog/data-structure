#pragma once

#include "Stack.h"
#include "LinkList.h"
#include "iostream"

namespace DataStructure
{
    template <typename T>
    class LinkStack
    {
    protected:
        LinkList<T> m_list;

    public:
        // O(1)
        void push(const T& e)
        {
            m_list.insert(0, e);
        }

        // O(1)
        void pop(void)
        {
            if(m_list.length() > 0)
            {
                m_list.remove(0);
            }
            else
                throw std::range_error("Stack is enpty!");
        }

        // O(1)
        T top() const
        {
            if(m_list.length() > 0)
                return m_list.get(0);
            else
                throw std::range_error("Stack is enpty!");
        }

        // O(n)
        void clear()
        {
            m_list.clear();
        }

        // O(1)
        int size() const
        {
            return m_list.length();
        }

        // O(n)
        ~LinkStack()
        {
            clear();
        }
    };
}