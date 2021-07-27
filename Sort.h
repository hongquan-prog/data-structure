#pragma once

#include "Object.h"
#include "Array.h"

namespace data_structure
{
    class Sort:public Object
    {
    private:
        Sort();
        Sort(const Sort&);
        Sort& operator = (const Sort&);

        template <typename T>
        static void Swap(T& a, T& b)
        {
            T c(a);
            a = b;
            b = c;
        }

        template <typename T>
        static void Merge(T src[], T helper[], int begin, int mid, int end, bool min2max)
        {
            int i = begin;
            int j = mid + 1;
            int k = begin;

            // 选择较小值放入到辅助存储空间中
            while((i <= mid) && (j <= end))
            {
                if(min2max ? (src[i] < src[j]) : (src[i] > src[j]))
                    helper[k++] = src[i++];
                else
                    helper[k++] = src[j++];
            }

            //左右两边的数组可能不等长
            while(i <= mid)
                helper[k++] = src[i++];
            while(j <= end)
                helper[k++] = src[j++];

            //最后把结果拷贝到原有的数组中
            for(int i = begin; i <= end; i++)
                src[i] = helper[i];
        }

        template <typename T>
        static void Merge(T src[], T helper[], int begin, int end, bool min2max)
        {
            if(begin < end)
            {
                int mid = (begin + end) / 2;
                Merge(src, helper, begin, mid, min2max);
                Merge(src, helper, mid + 1, end, min2max);
                Merge(src, helper, begin, mid, end, min2max);
            }
        }

        template <typename T>
        static int Partition(T array[], int begin, int end, bool min2max)
        {
            T temp = array[begin]; 
            while (begin < end)
            {
                //右边的值都小于基准
                while((begin < end) && (min2max ? (array[end] > temp) : (array[end] < temp)))
                {
                    end--;
                }
                array[begin] = array[end];

                while((begin < end) && (min2max ? (array[begin] <= temp) : (array[begin] >= temp)))
                {
                    begin++;
                }
                array[end] = array[begin];
            }
            array[begin] = temp;
            return begin;
        }

        template <typename T>
        static void Quick(T array[], int begin, int end, bool min2max)
        {
            if(begin < end)
            {
                int ret = Partition(array, begin, end, min2max);
                Quick(array, begin, ret - 1, min2max);
                Quick(array, ret + 1, end, min2max);
            }
        }

        template <typename T>
        static void AdjustHeap(T array[], int begin, int end, bool min2max)
        {
            int parent = begin;
            int child = parent * 2 + 1;

            while (child <= end)
            {
                if ((child + 1 <= end) && (min2max) ? (array[child] < array[child + 1]) : ((array[child] > array[child + 1])))
                {
                    child++;
                }
                if ((min2max) ? (array[parent] > array[child]) : (array[parent] < array[child]))
                {
                    return;
                }
                else
                {
                    Swap(array[parent], array[child]);
                    parent = child;
                    child = parent * 2 + 1;
                }
            }
        }
    public:
        // O(n^2)
        template <typename T>
        static void Select(T array[], const int len, bool min2max = true)
        {
            for(int i = 0; i < len; i++)
            {
                int index = i;
                for(int j = i + 1; j < len; j++)
                {
                    if((min2max) ? (array[index] > array[j]) : (array[index] < array[j]))
                        index = j;
                }
                if(index != i)
                    Swap(array[index], array[i]);
            }
        }

        // O(n^2)
        template <typename T>
        static void Insert(T array[], const int len, bool min2max = true)
        {
            for(int i = 1; i < len; i++)
            {
                int index = i;
                T temp = array[i];
                for(int j = i - 1; (j >= 0) && (min2max ? (array[j] > temp) : (array[j] < temp)); j--)
                {
                        array[j + 1] = array[j];
                        index = j;
                }
                if(index != i)
                {
                    array[index] = temp;
                }
            }
        }

        template <typename T>
        static void Bubble(T array[], const int len, bool min2max = true)
        {
            bool exchange = true;

            for(int i = 1; (i < len) && exchange; i++)
            {
                exchange = false;
                for(int j = len - 1; (j >= i); j--)
                {
                    if((min2max ? (array[j] < array[j - 1]) : (array[j] > array[j - 1])))
                    {
                        Swap(array[j], array[j - 1]);
                        exchange = true;
                    }
                }
            }
        }

        template <typename T>
        static void Shell(T array[], const int len, bool min2max = true)
        {
            int d = len;
            do
            {
                d = d / 3 + 1;
                for(int i = d; i < len; i++)
                {
                    int index = i;
                    T temp = array[i];
                    for(int j = i - d; (j >= 0) && (min2max ? (array[j] > temp) : (array[j] < temp)); j = j - d)
                    {
                        array[j + d] = array[j];
                        index = j;
                    }
                    if(index != i)
                    {
                        array[index] = temp;
                    }
                }
            
            } while (d > 1);
        }

        template <typename T>
        static void Merge(T array[], const int len, bool min2max = true)
        {
            T* helper = new T[len];
            if(helper)
                Merge(array, helper, 0, len - 1, min2max);
            delete [] helper;
        }

        template<typename T>
        static void Radix(T array[], const int len, bool min2max = true)
        {
            // 找出最大值
            int max = array[0];
            for(int i = 1; i < len; i++)
            {
                if(array[i] > max)
                {
                    max = array[i];
                }
            }

            // 申请内存
            T count[10] = {0};
            T* temp[10];
            for (int i = 0; i < 10; i++)
            {
                temp[i] = new T[len];
                if(temp[i] == NULL)
                {
                    for (int j = i; j >= 0; j--)
                    {
                        delete temp[j];
                    }
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create array!");
                }
            }
            
            for(int n = 1; n <= max; n *= 10)
            {
                for(int  i = 0; i < 10; i++)
                {
                    count[i] = 0;
                }

                for(int i = 0; i < len; i++)
                {
                    int ret = (array[i] / n) % 10;
                    temp[ret][count[ret]] = array[i];
                    count[ret]++;
                }

                int index = 0;
                for(int i = (min2max) ? (0) : (9); (min2max) ? (i < 10) : (i >= 0); (min2max) ? (i++) : (i--))
                {
                    for(int j = 0; j < count[i]; j++)
                    {
                        array[index++] = temp[i][j];
                    }
                }
            }

            for (int i = 0; i < 10; i++)
            {
                delete [] temp[i];
            }
        }

        template<typename T>
        static void Heap(T array[], const int len, bool min2max = true)
        {
            for(int i = len / 2 - 1; i >= 0; i--)
            {
                AdjustHeap(array, i, len - 1, min2max);
            }
            for(int i = len - 1; i > 0; i--)
            {
                Swap(array[0], array[i]);
                AdjustHeap(array, 0, i - 1, min2max);
            }
        }

        template <typename T>
        static void Quick(T array[], int len, bool min2max = true)
        {
            Quick(array, 0, len - 1, min2max);
        }

        template <typename T>
        static void Select(Array<T>& array, bool min2max = true)
        {
            Select(array.array(), array.length(), min2max);
        }

        template <typename T>
        static void Insert(Array<T>& array, bool min2max = true)
        {
            Insert(array.array(), array.length(), min2max);
        }

        template <typename T>
        static void Bubble(Array<T>& array, bool min2max = true)
        {
            Bubble(array.array(), array.length(), min2max);
        }

        template <typename T>
        static void Shell(Array<T>& array, bool min2max = true)
        {
            Shell(array.array(), array.length(), min2max);
        }

        template <typename T>
        static void Merge(Array<T>& array, bool min2max = true)
        {
            Merge(array.array(), array.length(), min2max);
        }

        template <typename T>
        static void Quick(Array<T>& array, bool min2max = true)
        {
            Quick(array.array(), array.length(), min2max);
        }

        template <typename T>
        static void Radix(Array<T>& array, bool min2max = true)
        {
            Radix(array.array(), array.length(), min2max);
        }

        template <typename T>
        static void Heap(Array<T>& array, bool min2max = true)
        {
            Heap(array.array(), array.length(), min2max);
        }
    };
}