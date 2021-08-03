#pragma once

#include "Object.h"

namespace data_structure
{
    template <typename T>
    struct BlockIndex:public Object
    {
        unsigned int begin;
        T value;
        unsigned int end;

        bool operator> (const BlockIndex& param)
        {
            return (param.value < this->value);
        }

        bool operator< (const BlockIndex& param)
        {
            return (param.value > this->value);
        }

        bool operator== (const BlockIndex& param)
        {
            return (param.value == this->value);
        }

        bool operator!= (const BlockIndex& param)
        {
            return !(*this == param);
        }
    };
    
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
                    ret = i;
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

        template <typename T>
        static int Bolock(T array[], int len, const T& value, int block_size)
        {
            int ret = -1;
            int block_cnt = ((len + block_size - 1) / block_size);

            BlockIndex<T>* index = new BlockIndex<T>[block_cnt];
            if(index)
            {
                for(int i = 0; (i < block_cnt); i++)
                {
                    T max = array[index[i].begin];

                    // 查找各块中的最大值作为索引值
                    index[i].begin = block_size * i;
                    index[i].end = ((index[i].begin + block_size) > len) ? (len) : (index[i].begin + block_size); 
                    for(int j = index[i].begin; j < index[i].end; j++)
                    {
                        if(array[j] > max)
                        {
                            max = array[j];
                        }
                    }
                    index[i].value = max;
                }
                // 索引进行排序
                Sort::Bubble(index, block_cnt);

                // 查找位于哪一块
                int block_position = -1;
                for(int i = 0; i < block_cnt; i++)
                {
                    if(value <= index[i].value)
                    {
                        block_position = i;
                        break;
                    }
                }

                // 在子块中进行查找
                if(block_position != -1)
                {
                    ret = Search::Sequential(&array[index[block_position].begin], index[block_position].end - index[block_position].begin, value);
                    if(ret != -1)
                    {
                        ret += index[block_position].begin;
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create BlockIndex!");
            }
            delete [] index;

            return ret;
        }
    };
       
}
