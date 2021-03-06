#pragma once

#include "Object.h"

namespace data_structure
{
    template <typename T>
    class List:public Object
    {
        private:
        List(const List&);
        List& operator=(const List&);

        public:
        List(){}
        virtual bool insert(const T& e) = 0;
        virtual bool insert(int i, const T& e) = 0;
        virtual bool remove(int i) = 0;
        virtual int find(const T& e) const = 0;
        virtual bool get(int i, T& e) const = 0;
        virtual bool set(int i, const T& e) = 0;
        virtual int length(void) const = 0;
        virtual void clear(void) = 0;
    };
}