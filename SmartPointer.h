#pragma once

#include "Object.h"
#include "Pointer.h"

namespace data_structure
{
    template <typename T>
    class SmartPointer:public Pointer<T>
    {
    public:
        SmartPointer(T* p = NULL):Pointer<T>(p)
        {
        }

        SmartPointer(const SmartPointer<T>& obj)
        {
            this->m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
        }

        SmartPointer<T>& operator = (const SmartPointer<T>& obj)
        {
            if(obj != this->m_pointer)
            {
                T * p = this->m_pointer;
                this->m_pointer = obj.m_pointer;
                const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
                delete p;
            }
            return *this;
        }

        ~SmartPointer()
        {
            delete this->m_pointer;
        }
    };
}