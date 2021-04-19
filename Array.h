#pragma once

#include <exception>

namespace DataStructure
{
    template <typename T> 
    class Array
    {
    protected:
        T * m_array;
    public:
        virtual int length() const = 0;
        virtual bool set(int i, const T& e)
        {
            if((i >= 0) && (i < length()))
            {
                m_array[i] = e;
                return true;
            }
            return false;
        }
        virtual bool get(int i, T& e) const
        {
            if((i >= 0) && (i < length()))
            {
                e = m_array[i];
                return true;
            }
            return false;
        }
        T& operator[] (int i)
        {
            if((i >= 0) && (i < length()))
                return m_array[i];
            else
                throw std::out_of_range("Parameter is invalid");
        }
        T operator[] (int i) const
        {
            return (const_cast<Array<T>&>(*this))[i];
        }
    };
}