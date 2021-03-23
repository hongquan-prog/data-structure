#pragma once

#include "List.h"

namespace DataStructure
{
    template <typename T> class SeqList;
}

template <typename T>
class SeqList:public List<T>
{
protected:
    T * m_array;
    int m_length;

public:

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

    bool set(int i, const T &e)
    {
        bool ret = ((i >= 0) && (i < m_length));
        if(ret)
            m_array[i] = e;
        return ret;
    }

    bool get(int i, T &e)const
    {
        bool ret = ((i >= 0) && (i < m_length));
        if(ret)
            e = m_array[i];
        return ret;
    }

    int  length(void) const
    {
        return m_length;
    }

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

    // 顺序存储空间的容量
    virtual  int capacity(void)const = 0;
};
