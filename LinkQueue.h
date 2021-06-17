#pragma once

#include "Queue.h"
#include "LinkList.h"

namespace data_structure
{
    template <typename T>
    class LinkQueue:Queue<T>
    {
    protected:
        LinkList<T> m_list;
    public:

        // O(n)
        void add(const T& e)
        {
            m_list.insert(e);
        }

        // O(1)
        void remove()
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
        T front() const
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
        int length() const
        {
            return m_list.length();
        }

        // O(n)
        ~LinkQueue()
        {
            clear();
        }
    };
    
}