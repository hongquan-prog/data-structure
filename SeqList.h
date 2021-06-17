#pragma once

#include "List.h"
#include "Exception.h"

namespace data_structure
{
    template <typename T>
    class Seqlist:public List<T>
    {
    protected:
        int m_length;
        T* m_array;
    public:
        
        // O(1)
        T& operator[] (int position)
        {
            if((position >= 0) && (position < m_length))
            {
                return m_array[position];
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "[] failed!")
            }
        }

        // O(1)
        T operator[] (int position) const
        {
            return const_cast<Seqlist<T>&>(*this)[position];
        }

        // O(1)
        bool insert(const T& e)
        {
            return insert(m_length, e);
        }
        
        // O(n)
        bool insert(int position, const T& e)
        {
            // 1
            if((position >= 0) && (position <= m_length) && (m_length < capacity()))
            {
                // 2
                for(int i = position; i < m_length; i++)
                {
                    m_array[i + 1] = m_array[i];
                }
                // 3
                m_array[position] = e;
                // 4
                m_length++;
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "insert failed!")
            }
            return true;
        }

        // O(n)
        bool remove(int position)
        {
            // 1
            if((position >= 0) && (position < m_length))
            {
                // 2
                for(int i = position + 1; i < m_length; i++)
                {
                    m_array[i] = m_array[i + 1];
                }
                // 3
                m_length--;
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "remove failed!")
            }
            return true;
        }

        // O(n)
        int find(const T& e) const
        {
            for(int i = 0; i < m_length; i++)
            {
                if(m_array[i] == e)
                {
                    return i;
                }
            }

            return -1;
        }

        // O(1)
        bool get(int position, T& e) const
        {
            if((position >= 0) && (position < m_length))
            {
                e = m_array[position];
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "get failed!")
            }
            return true;
        }

        // O(1)
        bool set(int position, const T& e)
        {
            if((position >= 0) && (position < m_length))
            {
                m_array[position] = e;
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "set failed!")
            }
            return true;
        }

        // O(1)
        int length(void) const
        {
            return m_length;
        }

        // O(1)
        void clear(void)
        {
            m_length = 0;
        }

        virtual  int capacity(void)const = 0;
    };
    
}