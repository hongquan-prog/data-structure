#pragma once

#include "Object.h"

namespace data_structure
{
    class Search:public Object
    {
    private:
    public:
        // O(n)
        template <typename T>
        static int Sequential(T array[], int len, const T& value)
        {
            int ret = -1;

            for(int i = 0; i < len; i++)
            {
                if(value == array[i])
                {
                    i = -1;
                    break;
                }
            }

            return ret;
        }

        template <typename T>
        static int Binsearch(T array[], int len, const T& value, bool min2max = true)
        {
            int ret = -1;
            if(len > 0)
            {
                int begin = 0;
                int end = len - 1;
                int mid = 0;

                while(begin < end)
                {
                    mid = (begin + end) / 2;
                    if(array[mid] == value)
                    {
                        ret = mid;
                        break;
                    }
                    else if(array[mid] < value)
                    {
                        (min2max) ? (begin = mid + 1) : (end = mid - 1);
                    }
                    else
                    {
                        (min2max) ? (end = mid - 1) : (begin = mid + 1);
                    }
                }
            }
            return ret;
        }

        template <typename T>
        static int Interpolation(T array[], int len, const T& value, bool min2max = true)
        {
            int ret = -1;

            if(len > 0)
            {
                int begin = 0;
                int end = len - 1;
                int mid = 0;

                while (begin < end)
                {
                    mid = begin + (value - array[begin]) * (end - begin) / (array[end] - array[begin]);
                    if(array[mid] == value)
                    {
                        ret = mid;
                        break;
                    }
                    else if(array[mid] < value)
                    {
                        (min2max) ? (begin = mid + 1) : (end = mid - 1);
                    }
                    else
                    {
                        (min2max) ? (end = mid - 1) : (begin = mid + 1);
                    }
                }
            }

            return ret;
        }
    };
       
}
