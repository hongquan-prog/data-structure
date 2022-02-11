#pragma once

#include "Object.h"
#include "Exception.h"

namespace data_structure
{
    template <typename T>
    class Array:public Object
    {
        protected:
        T* m_array;
        
        public:
        virtual bool set(int position, const T& e)
        {
            if((position >= 0) && (position < length()))
            {
                m_array[position] = e;
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "set failed!");
            }
            return true;
        }
        
        virtual bool get(int position, T& e)
        {
            if((position >= 0) && (position < length()))
            {
                e = m_array[position];
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "get failed!");
            }
            return true;
        }

        virtual int length(void) const = 0;

        T& operator[](int position)
        {
            if((position >= 0) && (position < length()))
            {
                return m_array[position];
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "[] failed!");
            }
        }

        T operator[](int position) const
        {
            return const_cast<Array<T>&>(*this)[position];
        }

        T* array() const
        {
            return m_array;
        }
    };
}