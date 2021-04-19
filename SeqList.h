#pragma once

#include "List.h"

namespace DataStructure
{
    template <typename T>
    class SeqList:public List<T>
    {
    protected:
        T * m_array;
        int m_length;

    public:

        // O(n)
        bool insert(int i, const T &e)
        {
            bool ret = ((i >= 0) && (i <= m_length) && (m_length < capacity()));
            
            if(ret)
            {
                for(int p = m_length -1; p >= i; p--)
                {
                    m_array[p + 1] = m_array[p];
                }
                m_array[i] = e;
                ++ m_length;
            }
            return ret;
        }

        bool insert(const T &e)
        {
            return insert(m_length, e);
        }

        // O(n)
        bool remove(int i)
        {
            bool ret = ((i >= 0) && (i < m_length));

            if(ret)
            {
                for(int p = i; p < m_length - 1; p++)
                {
                    m_array[p] = m_array[p + 1];
                }
                --m_length;
            }
            return ret;
        }

        //O(1)
        bool set(int i, const T &e)
        {
            bool ret = ((i >= 0) && (i < m_length));
            if(ret)
                m_array[i] = e;
            return ret;
        }
        // O(1)
        bool get(int i, T &e)const
        {
            bool ret = ((i >= 0) && (i < m_length));
            if(ret)
                e = m_array[i];
            return ret;
        }
        // O(1)
        int  length(void) const
        {
            return m_length;
        }
        // O(1)
        void clear(void)
        {
            m_length = 0;
        }

        // 顺序存储结构线性表的数组访问
        T& operator[] (int i)
        {
            if(((i >= 0) && (i < m_length)))
            {
                return m_array[i];
            }
            else
            {
                throw std::range_error("Parameter i is invalid");
            }
        }

        T operator[] (int i) const
        {
            return (const_cast<SeqList<T> &>(*this))[i];
        }

        int find(const T& e)const
        {
            int ret = -1;
            for (int i = 0; i < m_length; i++)
            {
                if(m_array[i] == e)
                    ret = i;
            }
            return ret;
        }

        // 顺序存储空间的容量
        virtual  int capacity(void)const = 0;
    };
}
