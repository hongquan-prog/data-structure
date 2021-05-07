#pragma once

namespace DataStructure
{
    template <typename T>
    class Queue
    {
    public:
        virtual void add(const T& e) = 0;
        virtual void remove() = 0;
        virtual T front() const = 0;
        virtual void clear(void) = 0;
        virtual int length() const = 0;
    };
}