#pragma once

namespace DataStructure
{
    template <typename T>
    class  List
    {
    protected:
        List(const List& e);
        List & operator= (const List& e);
    public:
        List(){};
        virtual bool insert(const T& e) = 0;
        virtual bool insert(int i, const T& e) = 0;
        virtual bool remove(int i) = 0;
        virtual bool get(int i, T& e) const = 0;
        virtual bool set(int i, const T& e) = 0;
        virtual int length(void) const = 0;
        virtual void clear(void) = 0;
        virtual int find(const T& e) const = 0;
    };
}