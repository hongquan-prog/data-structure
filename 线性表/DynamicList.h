#pragma once

#include <exception>
#include "SeqList.h"

namespace DataStructure
{
    template <typename T> class DynamicList;
}

template <typename T>
class DynamicList:public SeqList<T>
{
protected:
    int m_capacity;
public:
    DynamicList(int capacity)
    {
        if(capacity >= 0)
            this->m_array = new T[capacity];

        if(this->m_array)
        {
            this->m_capacity = capacity;
            this->m_length = 0;
        }
    }

    int capacity() const
    {
        return m_capacity;
    }

    void resize(int capacity)
    {
        if(capacity != m_capacity)
        {
            T * array = new T[capacity];
            if(array)
            {
                int length = this->m_length < capacity ? this->m_length : capacity;
                for(int i = 0; i < length; i++)
                {
                    array[i] = this->m_array[i];
                }
                T * temp = this->m_array;
                this->m_array = array;
                
                this->m_length = length;
                m_capacity = capacity;
                delete []temp;
            }
        }
    }
    ~DynamicList()
    {
        delete [] this->m_array;
    }
};