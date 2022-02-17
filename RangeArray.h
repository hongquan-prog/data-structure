//
// Created by lhq on 2022/2/12.
//

#ifndef RANGEARRAY_H
#define RANGEARRAY_H

#include "Array.h"

namespace data_structure
{
    template <typename T>
    class RangeArray : public Array<T>
    {
    protected:
        int m_lower;
        int m_upper;
        int m_length;

    public:
        RangeArray(int lower, int upper)
        {
            if (upper >= lower)
            {
                this->m_lower = lower;
                this->m_upper = upper;
                this->m_length = upper - lower + 1;
                this->m_array = new T[m_length];
            }
            else
            {
                this->m_length = 0;
                this->m_lower = 0;
                this->m_upper = 0;
            }
        }

        RangeArray(const RangeArray<T> &array)
        {
            T *toDel = this->m_array;
            T *newArray = new T[array.m_length];

            for (int i = 0; i < array.m_length; i++)
            {
                newArray[i] = array.m_array[i];
            }

            this->m_lower = array.m_lower;
            this->m_upper = array.m_upper;
            this->m_length = array.m_length;
            this->m_array = newArray;

            delete[] toDel;
        }

        virtual void resize(int lower, int upper)
        {
            if (upper >= lower)
            {
                T *toDel = this->m_array;
                int length = upper - lower + 1;
                T *newArray = new T[length];

                if (newArray)
                {
                    for (int i = 0; i < length; i++)
                    {
                        newArray[i] = this->m_array[i];
                    }

                    this->m_lower = lower;
                    this->m_upper = upper;
                    this->m_length = length;
                    this->m_array = newArray;
                    delete[] toDel;
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException, "Parameter upper less than lower!");
            }
        }

        bool set(int position, const T &val)
        {
            bool ret = false;

            if ((position >= this->m_lower) && (position <= this->m_upper))
            {
                ret = true;
                this->m_array[position] = val;
            }

            return ret;
        }

        bool get(int position, T &val)
        {
            bool ret = false;

            if ((position >= this->m_lower) && (position <= this->m_upper))
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
            return this->m_lower;
        }

        int upper() const
        {
            return this->m_upper;
        }

        T &operator[](int position)
        {
            if ((position >= this->m_lower) && (position <= this->m_upper))
            {
                return this->m_array[position];
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "index of RangeArray is valid!");
            }
        }

        RangeArray<T>& operator = (const RangeArray<T>& obj)
        {
            if(this != obj)
            {
                T* toDel = this->m_array;
                int length = obj.m_length;
                T* newArray = new T[length];

                if(newArray)
                {
                    for (int i = 0; i < length; i++)
                    {
                        newArray[i] = obj.m_array[i];
                    }

                    this->m_lower = obj.lower;
                    this->m_upper = obj.upper;
                    this->m_length = length;
                    this->m_array = newArray;
                    delete[] toDel;
                }
            }
            
            return *this;
        }

        T operator[](int position) const
        {
            return const_cast<RangeArray<T> &>(*this)[position];
        }

        ~RangeArray()
        {
            delete[] this->m_array;
        }
    };
}

#endif // DATA_STRUCTURE_RANGEARRAY_H
