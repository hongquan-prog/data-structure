#pragma once

#include "Object.h"
#include <iostream>
#include <exception>

namespace data_structure
{
    #define THROW_EXCEPTION(type, msg) {throw type(msg, __FILE__, __LINE__);}
    class Exception:public Object
    {
    protected:
        char * m_message;
        char * m_location;

        void init(const char * message, const char * file, int line);
    public:
        Exception(const char * message);
        Exception(const char * file, int line);
        Exception(const char * message, const char * file, int line);

        Exception(const Exception& e);
        Exception& operator = (const Exception& e);

        virtual const char * message() const;
        virtual const char * location() const;
        virtual ~Exception();
    }; 

    class ArithmeticException:public Exception
    {
        public:
        ArithmeticException():Exception(NULL, 0){}
        ArithmeticException(const char * message):Exception(message, NULL, 0){}
        ArithmeticException(const char * file, int line):Exception(NULL, file, line){}
        ArithmeticException(const char * message, const char * file, int line):Exception(message, file, line){}
        ArithmeticException(const ArithmeticException& e):Exception(e){}
        ArithmeticException& operator=(const ArithmeticException& e)
        {
            Exception::operator=(e);
            return *this;
        }
    }; 
    class NullPointerException:public Exception
    {
        public:
        NullPointerException():Exception(NULL, 0){}
        NullPointerException(const char * message):Exception(message, NULL, 0){}
        NullPointerException(const char * file, int line):Exception(NULL, file, line){}
        NullPointerException(const char * message, const char * file, int line):Exception(message, file, line){}
        NullPointerException(const NullPointerException& e):Exception(e){}
        NullPointerException& operator=(const NullPointerException& e)
        {
            Exception::operator=(e);
            return *this;
        }
    }; 
    class IndexOutofBoundsException:public Exception
    {
        public:
        IndexOutofBoundsException():Exception(NULL, 0){}
        IndexOutofBoundsException(const char * message):Exception(message, NULL, 0){}
        IndexOutofBoundsException(const char * file, int line):Exception(NULL, file, line){}
        IndexOutofBoundsException(const char * message, const char * file, int line):Exception(message, file, line){}
        IndexOutofBoundsException(const IndexOutofBoundsException& e):Exception(e){}
        IndexOutofBoundsException& operator=(const IndexOutofBoundsException& e)
        {
            Exception::operator=(e);
            return *this;
        }
    }; 
    class NoEnoughMemoryException:public Exception
    {
        public:
        NoEnoughMemoryException():Exception(NULL, 0){}
        NoEnoughMemoryException(const char * message):Exception(message, NULL, 0){}
        NoEnoughMemoryException(const char * file, int line):Exception(NULL, file, line){}
        NoEnoughMemoryException(const char * message, const char * file, int line):Exception(message, file, line){}
        NoEnoughMemoryException(const NoEnoughMemoryException& e):Exception(e){}
        NoEnoughMemoryException& operator=(const NoEnoughMemoryException& e)
        {
            Exception::operator=(e);
            return *this;
        }
    }; 
    class InvalidParameterException:public Exception
    {
        public:
        InvalidParameterException():Exception(NULL, 0){}
        InvalidParameterException(const char * message):Exception(message, NULL, 0){}
        InvalidParameterException(const char * file, int line):Exception(NULL, file, line){}
        InvalidParameterException(const char * message, const char * file, int line):Exception(message, file, line){}
        InvalidParameterException(const InvalidParameterException& e):Exception(e){}
        InvalidParameterException& operator=(const InvalidParameterException& e)
        {
            Exception::operator=(e);
            return *this;
        }
    }; 
    class InvalidOperationException:public Exception
    {
        public:
        InvalidOperationException():Exception(NULL, 0){}
        InvalidOperationException(const char * message):Exception(message, NULL, 0){}
        InvalidOperationException(const char * file, int line):Exception(NULL, file, line){}
        InvalidOperationException(const char * message, const char * file, int line):Exception(message, file, line){}
        InvalidOperationException(const InvalidOperationException& e):Exception(e){}
        InvalidOperationException& operator=(const InvalidOperationException& e)
        {
            Exception::operator=(e);
            return *this;
        }
    }; 
}