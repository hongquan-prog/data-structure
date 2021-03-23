#include <iostream>
#include "StaticList.h"
#include "DynamicList.h"


int main(void)
{
    StaticList<int, 10> l;

    // for(int i = 0; i < l.capacity(); i++)
    //     l.insert(0, i);

    // for(int i = 0; i < l.length(); i++)
    //     std::cout<< l[i] <<std::endl;

    // try
    // {
    //     l[20] = 1;
    // }
    // catch(std::exception &e)
    // {
    //     std::cout << e.what() << std::endl;
    // }

    DynamicList<int> l1(20);


    for(int i = 0; i < l1.capacity(); i++)
        l1.insert(0, i);

    for(int i = 0; i < l1.length(); i++)
        std::cout<< l1[i] <<std::endl;

    l1.resize(10);
    for(int i = 0; i < l1.length(); i++)
        std::cout<< l1[i] <<std::endl;

}