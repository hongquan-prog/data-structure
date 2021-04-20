#pragma once

#include <iostream>
#include "Pointer.h"

namespace DataStructure
{
    template <typename T>
    class SharedPointer:public Pointer<T>
    {
        protected:
        int* m_ref;

        void assign(const SharedPointer<T>& obj)
        {
            this->m_ref = obj.m_ref;
            this->m_pointer = obj.m_pointer;
            if(this->m_ref)
            {
                ++(*this->m_ref);
            }
        }

        public:

        SharedPointer(T * p = NULL):m_ref(NULL)
        {
            if(p)
            {
                this->m_ref = new int;
                if(this->m_ref)
                {
                    *(this->m_ref) = 1;
                    this->m_pointer = p;
                }
            }
        }
        
        SharedPointer(const SharedPointer<T>& obj):Pointer<T>(NULL)
        {
            assign(obj);
        }

        SharedPointer<T>& operator= (const SharedPointer<T>& obj)
        {
            if(&obj != this)
            {
                clear();
                assign(obj);
            }
            return *this;
        }

        void clear()
        {
            T* del = this->m_pointer;
            int* ref = this->m_ref;

            this->m_pointer = NULL;
            this->m_ref = NULL;

            if(ref)
            {
                (*ref)--;
                if(*ref == 0)
                {
                    delete ref;
                    delete del;
                }
            }
        }

        ~SharedPointer()
        {
            clear();
        }
    };

    template <typename T>
    bool operator== (const SharedPointer<T>& l, const SharedPointer<T>& r)
    {
        return (l.get() == r.get());
    }

    template <typename T>
    bool operator!= (const SharedPointer<T>& l, const SharedPointer<T>& r)
    {
        return !(l == r);
    }
}