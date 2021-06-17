#include "DTString.h"
#include "Exception.h"
#include <cstring>
#include <cstdlib>

namespace data_structure
{

void String::init(const char * s)
{
    m_str = strdup(s);
    if(m_str)
    {
        m_length = strlen(s);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to create string object ...")
    }
}

String::String()
{
    m_str = NULL;
    m_length = 0;
}

String::String(const char * s)
{
    init(s ? s : "");
}

String::String(const String& s)
{
    init(s.m_str);
}

String::String(char c)
{
    char s[] = {c, '\0'};
    init(s);
}

int String::length() const
{
    return m_length;
}

const char * String::str() const
{
    return m_str;
}

/*比较操作符重载函数*/
bool String::operator == (const String& s) const
{
    return (strcmp(m_str, s.m_str) == 0);
}

bool String::operator == (const char* s) const
{
    return (strcmp(m_str, s ? s : "") == 0);
}

bool String::operator != (const String& s) const
{
    return (strcmp(m_str, s.m_str) != 0);
}

bool String::operator != (const char* s) const
{
    return (strcmp(m_str, s ? s : "") != 0);
}

bool String::operator > (const String& s) const
{
    return (strcmp(m_str, s.m_str) > 0);
}

bool String::operator > (const char* s) const
{
    return (strcmp(m_str, s ? s : "") > 0);
}
bool String::operator < (const String& s) const
{
    return (strcmp(m_str, s.m_str) < 0);
}
bool String::operator < (const char* s) const
{
    return (strcmp(m_str, s ? s : "") < 0);
}
bool String::operator >= (const String& s) const
{
    return (strcmp(m_str, s.m_str) >= 0);
}
bool String::operator >= (const char* s) const
{
    return (strcmp(m_str, s ? s : "") >= 0);
}
bool String::operator <= (const String& s) const
{
    return (strcmp(m_str, s.m_str) <= 0);
}
bool String::operator <= (const char* s) const
{
    return (strcmp(m_str, s ? s : "") <= 0);
}
/*加法操作符重载函数*/
String String::operator + (const String& s) const
{
    return *this + s;
}

String String::operator + (const char* s) const
{
    String ret;
    int len = m_length + strlen(s ? s : "");
    char * str = reinterpret_cast<char *>(malloc(len + 1));
    if(str)
    {
        memcpy(str, m_str, m_length);
        memcpy(str + m_length, s ? s : "", strlen(s ? s : ""));
        str[len] = '\0';

        ret.m_length = len;
        ret.m_str = str;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add string values ...");
    }

    return ret;
}
String& String::operator += (const String& s)
{
    return (*this = *this + s);
}
String& String::operator += (const char* s)
{
    return (*this = *this + s);
}
/*赋值操作符重载函数*/
String& String::operator = (const String& s)
{
    return (*this = s.m_str);
}
String& String::operator = (const char* s)
{
    if(s != m_str)
    {
        char * str = strdup(s ? s : "");
        if(str)
        {
            free(m_str);
            m_str = str;
            m_length = strlen(m_str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add change values ...");
        }
    }
    return *this;
}

String& String::operator = (char c)
{
    char s[] = {c, '\0'};
    return (*this = s);
}

char String::operator [](int i) const
{
    return (const_cast<String&>(*this))[i];
}

char& String::operator [](int i)
{
    if((i < m_length) && (i >= 0))
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutofBoundsException, "Index is more than length ...");
    }
}

bool String::startWith(const char* s) const
{
    bool ret = (s != NULL);
    if(ret)
    {
        int len = strlen(s);
        ret = (len < m_length);
        ret = ret && (memcmp(s, m_str, len) == 0);
    }
    return ret;
}
bool String::startWith(const String& s) const
{
    return startWith(s.m_str);
}

bool String::endOf(const char* s) const
{
    bool ret = (s != NULL);
    if(ret)
    {
        int len = strlen(s);
        ret = (len < m_length);
        ret = ret && (memcmp(s, m_str + (m_length - len), len) == 0);
    }
    return ret;
}

bool String::endOf(const String& s) const
{
    return endOf(s.m_str);
}

String& String::insert(int i, const char* s)
{
    if((i <= m_length) && (i >= 0) && s)
    {
        int len = m_length + strlen(s);
        char * str = reinterpret_cast<char *>(malloc(len + 1));
        if(str)
        {
            memcpy(str, m_str, i);
            memcpy(str + i, s, strlen(s));
            memcpy(str + i + strlen(s), m_str + i, len - strlen(s) - i);
            str[len] = '\0';
            free(m_str);
            m_str = str;
            m_length = len;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Memory to insert string ...");
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutofBoundsException,"No position to insert string ...");
    }
    return *this;
}
String& String::insert(int i, char c)
{ 
    char s[] = {c, '\0'};
    insert(i, s);
    return *this;
}

String& String::insert(int i, const String& s)
{
    insert(i, s.m_str);
    return *this;
}

String& String::trim()
{
    int b = 0;
    int e = m_length - 1;
    if(m_length > 0)
    {
        while((m_str[b] == ' ') && (b < m_length)) b++;
        while((m_str[e] == ' ') && (e >= 0)) e--;

        if(b <= e)
        {
            if(b == 0)
            {
                m_str[e + 1] = '\0';
                m_length = e + 1;
            }
            else
            {
                int i = 0;
                for(i = b; i <= e; i++)
                {
                    m_str[i - b] = m_str[i];
                }
                m_str[i - b] = '\0';
                m_length = e + 1 - b;
            }
        }
        else
        {
            m_str[0] = '\0';
            m_length = 0;
        }
    }
    return *this;
}
// O(m)
int * String::make_pmt(const char * p)
{
    int len = strlen(p);
    int *ret = static_cast<int *>(malloc(sizeof(int) * len));
    if(ret)
    {
        int ll = 0;
        ret[0] = 0;
        for(int i = 1; i < len; i++)
        {
            while((ll > 0) && (p[ll] != p[i]))
            {
                ll = ret[ll - 1];
            }
            if(p[ll] == p[i])
            {
                ll++;
            }
            ret[i] = ll;
        }
    }

    return ret;
}
// O(m) + O(n) == O(m + n)
int String::kmp(const char * s, const char *p)
{
    int ret = -1;
    int sl = strlen(s);
    int pl = strlen(p);
    int * pmt = make_pmt(p);

    if(pmt && (pl > 0) && (pl <= sl))
    {
        for(int i = 0, j = 0; i < sl; i++)
        {
            while((j > 0) && (s[i] != p[j]))
            {
                j = pmt[j - 1];
            }

            if(s[i] == p[j])
            {
                j++;
            }
            
            if(j == pl)
            {
                ret = i + 1 - pl;
                break;
            }
        }
    }

    free(pmt);
    return ret;
}

int String::indexOf(const String& s) const
{
    return indexOf(s.m_str);
}

int String::indexOf(const char* s) const
{
    if(s)
        return kmp(m_str, s);
    else
        return -1;
}
String& String::remove(int i, int len)
{
    if((i >= 0) && (i < m_length))
    {
        int start = i;
        int end = i + len;
        while((start < end) && (end < m_length))
        {
            m_str[start++] = m_str[end++];
        }
        m_str[start] = '\0';
        m_length = m_length - len;
    }
    return *this;
}

String& String::remove(const String& s)
{
    return remove(indexOf(s), s.m_length);
}

String& String::remove(const char* s)
{
    return remove(indexOf(s), s ? strlen(s) : 0);
}

String String::operator-(const String& s) const
{
    return String(*this).remove(s);
}

String String::operator-(const char* s) const
{
    return String(*this).remove(s);
}

String& String::operator-=(const String& s)
{
    return remove(s);
}

String& String::operator-=(const char* s)
{
    return remove(s);
}

String& String::replace(const char* t, const char* s)
{
    if(s && t)
    {
        int index = indexOf(t);
        if(index >= 0)
        {
            remove(t);
            insert(index, s);
        }
    }
    return *this;
}

String& String::replace(const String& t, const char* s)
{
    return replace(t.m_str, s);
}

String& String::replace(const char* t, const String* s)
{
    return replace(t, s->m_str);
}

String& String::replace(const String& t, const String& s)
{
    return replace(t.m_str, s.m_str);
}

String String::substring(int i, int len) const
{
    String ret;
    if((i >= 0) && (i < m_length))
    {
        if(len < 0) 
            len = 0;
        if((len + i) > m_length)
            len = m_length - i;
        char * str =  reinterpret_cast<char *>(malloc(len + 1));
        if(str)
        {
            memcpy(str, &m_str[i], len);
            str[len] = '\0';
            ret = str;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No memory to create substring ...");
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutofBoundsException,"Parameter i is invalid ...");
    }
    return ret; 
}

String::~String()
{
    free(m_str);
    m_str = NULL;
    m_length = 0;
}
}
