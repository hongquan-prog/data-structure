#pragma once

#include <exception>
namespace DataStructure
{
    template <typename T>
    class DynamicArray:public Array<T>
    {
    protected:
        int m_length;

        T * copy(T* array, int len, int newLen)
        {
            T* ret = new T[newLen];

            if(ret)
            {
                int copy_length = (len < newLen)?(len):(newLen);
                for(int i = 0; i < copy_length; i++)
                {
                    ret[i] = array[i];
                }
            }
            return ret;
        }

        void update(T* array, int length)
        {
            if(array)
            {
                T* temp = this->m_array;
                this->m_array = array;
                this->m_length = length;
                delete []temp;
            }
            else
                throw std::bad_alloc();
        }
        
        void init(T * array, int length)
        {
            if(array)
            {
                this->m_array = array;
                this->m_length = length;
            }
            else
                throw std::bad_alloc();
        }
    public:
        DynamicArray(int length)
        {
            init(new T[length], length); 
        }

        DynamicArray(const DynamicArray<T> & obj)
        {
            init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        }
        DynamicArray<T> & operator= (const DynamicArray<T> & obj)
        {
            if(this != obj)
            {
                update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
            }
            return *this;
        }

        void resize(int size)
        {
            if(size != m_length)
            {
                update(copy(this->m_array, this->m_length, size), size);
            }
        }

        ~DynamicArray()
        {
            delete []this->m_array;
        }

        int length()const
        {
            return m_length;
        }
    };
}