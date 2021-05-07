#include "Queue.h"
#include "LinkList.h"
#include <iostream>

namespace DataStructure
{
    template <typename T, int N>
    class LinkQueue:public Queue<T>
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
        void remove(void)
        {
            if(m_list.length() > 0)
            {
                m_list.remove(0);
            }
            else
                throw std::range_error("Stack is enpty!");
        }

        // O(1)
        T front() const
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