#include "StaticLinkList.h"
#include "CircleList.h"
#include "SmartPointer.h"
#include "SharedPointer.h"
#include "DualLinkList.h"
#include "StaticStack.h"
#include "LinkStack.h"
#include "StaticQueue.h"
#include "LinkQueue.h"
#include <iostream>


bool is_left(char c)
{
    return (c == '(') || (c == '{') || (c == '[') || (c == '<');
}

bool is_right(char c)
{
    return (c == ')') || (c == '}') || (c == ']') || (c == '>');
}

bool is_quot(char c)
{
    return (c == '\'') || (c == '\"');
}

bool is_match(char l, char r)
{
    return  ((l == '(') && (r == ')')) ||
            ((l == '{') && (r == '}')) ||
            ((l == '[') && (r == ']')) ||
            ((l == '<') && (r == '>')) ||
            ((l == '\'') && (r == '\'')) ||
            ((l == '\"') && (r == '\"'));
}

bool scan(const char * code)
{
    DataStructure::LinkStack<char> stack;
    int i = 0;
    bool ret = true;

    code = (code == NULL) ? ("") : (code);
    while(ret && (code[i] != '\0'))
    {
        if(is_left(code[i]))
        {
            stack.push(code[i]);
        }
        else if(is_right(code[i]))
        {
            if((stack.size() > 0) && is_match(stack.top(), code[i]))
            {
                stack.pop();
            }
            else
                ret = false;
        }
        else if(is_quot(code[i]))
        {
            if((stack.size() == 0) || !is_match(stack.top(), code[i]))
            {
                stack.push(code[i]);
            }
            else if(is_match(stack.top(), code[i]))
            {
                stack.pop();
            }
        }
        i++;
    }

    return ret && (stack.size() == 0);
}
int main()
{
    DataStructure::LinkQueue<int, 10> queue;

    for(int i = 0; i < 10; i++)
    {
        queue.add(i);
    }

    for(int i = 0; i < 10; i++)
    {
        std::cout << queue.front() << std::endl;
        queue.remove();
    }
}