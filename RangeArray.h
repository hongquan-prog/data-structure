//
// Created by lhq on 2022/2/12.
//

#ifndef DATA_STRUCTURE_RANGEARRAY_H
#define DATA_STRUCTURE_RANGEARRAY_H

#include "Array.h"

namespace data_structure
{
    template <typename T>
    class RangeArray:public Array<T>
    {
    protected:
        int bottom;
        int top;
        int m_length;

    public:
        RangeArray(int lower, int upper)
        {
            if(upper > lower)
            {
                this->bottom = lower;
                this->top = upper;
                m_length = upper - lower + 1;
                this->m_array = new T[m_length];
            }
            else
            {
                m_length = 0;
                this->bottom = 0;
                this->top = 0;
            }
        }

        RangeArray(const RangeArray<T>& array)
        {
            T* toDel = this->m_array;
            T* newArray = new T[array.m_length];

            for(int i = 0; i < array.m_length; i++)
            {
                newArray[i] = array.m_array[i];
            }

            this->bottom = array.bottom;
            this->top = array.top;
            this->m_length = array.m_length;
            this->m_array = newArray;

            delete [] toDel;
        }

        bool set(int position, const T& val)
        {
            bool ret = false;

            if((position >= bottom) && (position <= top))
            {
                ret = true;
                this->m_array[position] = val;
            }

            return ret;
        }

        bool get(int position, T& val)
        {
            bool ret = false;

            if((position >= bottom) && (position <= top))
            {
                val = this->m_array[position];
                ret = true;
            }

            return true;
        }

        int length(void) const
        {
            return m_length;
        }

        int lower() const
        {
            return bottom;
        }

        int upper() const
        {
            return top;
        }

        T& operator [] (int position)
        {
            if((position >= bottom) && (position <= top))
            {
                return this->m_array[position];
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "index of RangeArray is valid!");
            }
        }

        T operator [] (int position) const
        {
            return const_cast<RangeArray<T>&>(*this)[position];
        }

        ~RangeArray()
        {
            delete [] this->m_array;
        }
    };
}


#endif //DATA_STRUCTURE_RANGEARRAY_H
