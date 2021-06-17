#pragma once

#include "Object.h"

namespace data_structure
{
    class String:public Object
    {
    protected:
        char * m_str;
        int m_length;

        void init(const char * s);
        static int kmp(const char * s, const char *p);
        static int * make_pmt(const char * p);
    public:
        String();
        String(const char * s);
        String(const String& s);
        String(char c);
        int length() const;
        const char * str() const;

        /*比较操作符重载函数*/
        bool operator == (const String& s) const;
        bool operator == (const char* s) const;
        bool operator != (const String& s) const;
        bool operator != (const char* s) const;
        bool operator > (const String& s) const;
        bool operator > (const char* s) const;
        bool operator < (const String& s) const;
        bool operator < (const char* s) const;
        bool operator >= (const String& s) const;
        bool operator >= (const char* s) const;
        bool operator <= (const String& s) const;
        bool operator <= (const char* s) const;
        /*加法操作符重载函数*/
        String operator + (const String& s) const;
        String operator + (const char* s) const;
        String& operator += (const String& s);
        String& operator += (const char* s);
        /*赋值操作符重载函数*/
        String& operator = (const String& s);
        String& operator = (const char* s);
        String& operator = (char c);
        char operator [](int i) const;
        char& operator [](int i);

        bool startWith(const char* s) const;
        bool startWith(const String& s) const;
        bool startWith(char c) const;
        bool endOf(const char* s) const;
        bool endOf(const String& s) const;
        bool endOf(char c) const;
        String& insert(int i, const char* s);
        String& insert(int i, char c);
        String& insert(int i, const String& s);
        String& trim();
        int indexOf(const String& s) const;
        int indexOf(const char* s) const;
        String& remove(int i, int len);
        String& remove(const String& s);
        String& remove(const char* s);
        String operator-(const String& s) const;
        String operator-(const char* s) const;
        String& operator-=(const String& s);
        String& operator-=(const char* s);
        String& replace(const char* t, const char* s);
        String& replace(const String& t, const char* s);
        String& replace(const char* t, const String* s);
        String& replace(const String& t, const String& s);
        String substring(int i, int len) const;
        
        ~String();
    };
    
}