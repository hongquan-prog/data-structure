#pragma once

namespace DataStructure
{
    template <typename T>
    class Stack
    {
    public:
        virtual void push(const T& e) = 0;
        virtual void pop() = 0;
        virtual T top() = 0;
        virtual void clear() = 0;
        virtual int size() const = 0;
    };
}