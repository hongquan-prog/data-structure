#pragma once

#include "Object.h"

namespace data_structure
{
    template <typename T>
    class Pointer:public Object
    {
        protected:
            T * m_pointer;
        public:
            Pointer(T* p = NULL)
            {
                m_pointer = p;
            }

            T* operator ->()
            {
                return m_pointer;
            }

            T* operator *()
            {
                return *m_pointer;
            }

            bool isNull()
            {
                return (m_pointer == NULL);
            }

            T* get() const
            {
                return m_pointer;
            }
    };
}