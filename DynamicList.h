#include "SeqList.h"

namespace data_structure
{
    template <typename T>
    class DynamicList:public Seqlist<T>
    {
    protected:
        int m_capacity;
    public:

        // O(1)
        DynamicList(int capacity)
        {
            this->m_array = new T[capacity];
            if(this->m_array)
            {
                this->m_capacity = capacity;
                this->m_length = 0;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "DynamicList construct failed!");
            }
        }

        // O(n)
        void resize(int capacity)
        {
            if(this->m_capacity != capacity)
            {
                T * array = new T[capacity];
                int length  = (capacity > this->m_length)?(this->m_length):(capacity);
                if(array)
                {
                    for(int i = 0; i < length; i++)
                    {
                        array[i] = this->m_array[i];
                    }
                    
                    T * temp = this->m_array;
                    this->m_array = array;
                    this->m_length = length;
                    this->m_capacity = capacity;
                    delete []temp;
                    
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "resize failed!");
                }
            }
        }

        // O(1)
        int capacity(void)const
        {
            return m_capacity;
        }

        // O(1)
        ~DynamicList()
        {
            delete [] this->m_array;
        }
    };
}