#pragma once

#include "Pointer.h"
#include "Exception.h"

namespace data_structure
{
    template <typename T>
    class SharedPointer:public Pointer<T>
    {
    protected:
        int * m_ref;

        void copy(const SharedPointer& e)
        {
            this->m_pointer = e.m_pointer;
            m_ref = e.m_ref;
            if(m_ref)
            {
                (*m_ref)++;
            }
        }
    public:
        SharedPointer(T* p = NULL):Pointer<T>(p)
        {
            m_ref = NULL;
            if(p)
            {
                m_ref = new int;
                if(m_ref)
                {
                    *m_ref = 1;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to use ...");
                }
            }
        }

        SharedPointer(const SharedPointer& e):Pointer<T>(NULL)
        {
            copy(e);
        }

        SharedPointer<T>& operator = (const SharedPointer<T>& e)
        {
            if(this != &e)
            {
                clear();
                copy(e);
            }
            return *this;
        }

        void clear()
        {
            T* toDel = this->m_pointer;
            int* ref = this->m_ref;
            
            this->m_pointer = NULL;
            this->m_ref = NULL;

            if(ref)
            {
                (*ref)--;
                if(*ref == 0)
                {
                    delete toDel;
                    delete ref;
                }
            }
        }

        bool operator == (const SharedPointer<T>& e)
        {
            return (this->get() == e.get());
        }

        bool operator != (const SharedPointer<T>& e)
        {
            return !(*this == e);
        }

        ~SharedPointer()
        {
            clear();
        }
    };   
}