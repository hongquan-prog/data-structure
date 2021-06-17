#pragma once

#include "Object.h"
#include <iostream>

namespace data_structure
{
    template <typename T>
    class SmartPointer:public Object
    {
    protected:
        T * m_pointer;
    public:
        SmartPointer(T* p = NULL)
        {
            m_pointer = p;
        }

        SmartPointer(const SmartPointer<T>& obj)
        {
            m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
        }

        SmartPointer<T>& operator = (const SmartPointer<T>& obj)
        {
            if(obj != m_pointer)
            {
                delete m_pointer;
                m_pointer = obj.m_pointer;
                const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
            }
            return *this;
        }

        T * operator ->()
        {
            return m_pointer;
        }

        T& operator * ()
        {
            return *m_pointer;
        }

        bool isNull()
        {
            return (m_pointer == NULL);
        }

        T* get()
        {
            return m_pointer;
        }

        ~SmartPointer()
        {
            delete m_pointer;
        }
    };
}