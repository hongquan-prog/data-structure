#pragma once

#include "Stack.h"
#include "LinkList.h"

namespace data_structure
{
    template <typename T>
    class LinkStack:public Stack<T>
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
        void pop()
        {
            if(m_list.length())
            {
                m_list.remove(0);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
            }
        }

        // O(1)
        T top() const
        {
            if(m_list.length())
            {
                return m_list.get(0);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
            }
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

        ~LinkStack()
        {
            clear();
        }
    };
};