#include "StaticLinkList.h"
#include "CircleList.h"
#include "SharedPointer.h"
#include <iostream>

void josephus(int n, int s, int m)
{
    DataStructure::CircleList<int> list;
    for(int i = 1; i <= n; i++)
    {
        list.insert(i);
    }

    for(list.move(2, m - 1); list.length() > 0; list.next())
    {
        std::cout << list.current() <<std::endl;
        list.remove(list.find(list.current()));
    }
}

int main()
{
    josephus(41, 1, 3);
}