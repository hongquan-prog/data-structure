#include "StaticLinkList.h"
#include <iostream>

int main()
{
    DataStructure::StaticLinkList<int, 10> val;

    for(int i = 0; i < 5; i++)
    {
        val.insert(i);
    }

    for(val.move(0); !val.end(); val.next())
    {
        if(val.current() == 3)
        {
            val.remove(val.find(val.current()));
            std::cout << val.current() << std::endl;
        }
        std::cout<< val.current() << std::endl;
    }
}