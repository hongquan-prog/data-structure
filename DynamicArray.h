#pragma once

#include "Array.h"

namespace data_structure
{
    template <typename T>
    class DynamicArray:public Array<T>
    {
    protected:
        int m_length;

        // O(n)
        T* copy(T* array, int len, int newLen)
        {
            T * obj = new T[newLen];
            if(obj)
            {
                int length = (len < newLen)?(len):(newLen);
                for(int i = 0; i < length; i++)
                {
                    obj[i] = array[i];
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "copy failed!");
            }
            return obj;
        }

        // O(1)
        void update(T* array, int len)
        {
            T * temp = this->m_array;
            this->m_array = array;
            this->m_length = len;
            delete []temp;
        }

        // O(1)
        void init(T * array, int length)
        {
            if(array)
            {
                this->m_array = array;
                this->m_length = length;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "DynamicArray construct failed!");
            }
        }
    public:

        // O(1)
        DynamicArray(int length)
        {
            init(new T[length], length);
        }

        // O(n)
        DynamicArray(const DynamicArray& obj)
        {
            init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        }

        // O(n)
        DynamicArray& operator=(const DynamicArray& obj)
        {
            if(this != & obj)
            {
                update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
            }
            return *this;
        }

        // O(n)
        void resize(int size)
        {
            if(m_length != size)
            {
                update(copy(this->m_array, this->m_length, size), size);
            }
        }
        
        // O(1)
        int length(void) const
        {
            return m_length;
        }

        // O(1)
        ~DynamicArray()
        {
            delete [] this->m_array;
        }
    };
}