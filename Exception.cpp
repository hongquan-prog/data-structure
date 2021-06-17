#include "Exception.h"
#include <cstring>
#include <cstdlib>

namespace data_structure
{
    void Exception::init(const char * message, const char * file, int line)
    {
        m_message = (message) ? (strdup(message)) : (NULL);
        if(file != NULL)
        {
            m_location = (char *)malloc(strlen(file) + 20);
            if(m_location != NULL)
                snprintf(m_location, strlen(file) + 20, "%s:%d", file, line);
        }
        else
        {
            m_location = NULL;
        }
    }

    Exception::Exception(const char * message)
    {
        init(message, NULL, 0);
    }
    Exception::Exception(const char * file, int line)
    {
        init(NULL, file, line);
    }
    Exception::Exception(const char * message, const char * file, int line)
    {
        init(message, file, line);
    }

    Exception::Exception(const Exception& e)
    {
        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }
    Exception& Exception::operator = (const Exception& e)
    {
        if(this != &e)
        {
            free(m_location);
            free(m_message);
            m_message = strdup(e.m_message);
            m_location = strdup(e.m_location);
        }
        return *this;
    }

    const char * Exception::message() const
    {
        return m_message;
    }
    const char * Exception::location() const
    {
        return m_location;
    }
    
    Exception:: ~Exception()
    {
        free(m_location);
        free(m_message);;
    }
}