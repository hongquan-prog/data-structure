#pragma once

namespace DataStructure
{
    template <typename T> class List;
}

template <typename T>
class List
{
public:
    virtual bool insert(int i, const T &e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool set(int i, const T &e) = 0;
    virtual bool get(int i, T &e)const = 0;
    virtual int  length(void) const = 0;
    virtual void clear(void) = 0;
};