#pragma once

#include <stdexcept>

class NotImplementedException : public std::logic_error
{
private:

    std::string _text;

    NotImplementedException(const char* message, const char* function)
        :
        std::logic_error("Function not yet implemented")
    {
        _text = message;
        _text += " : ";
        _text += function;
    };

public:

    NotImplementedException()
        :
        NotImplementedException("Function not yet implemented", __FUNCTION__)
    {
    }

    NotImplementedException(const char* message)
        :
        NotImplementedException(message, __FUNCTION__)
    {
    }

    virtual const char* what() const throw()
    {
        return _text.c_str();
    }
};

class NotInitialisedException : public std::logic_error
{
private:

    std::string _text;

    

public:

    NotInitialisedException(const char* message)
        :
        std::logic_error("Object not properly initialised")
    {
        _text = message;
    }

    NotInitialisedException()
        :
        NotInitialisedException("Object not properly initialised")
    {
    }

    virtual const char* what() const throw()
    {
        return _text.c_str();
    }
};

class ArgumentException : public std::logic_error
{
private:

    std::string _text;

    ArgumentException(const char* message, const char* function, const char* arg)
        :
        std::logic_error("Argument caused an exception")
    {
        _text = message;
        _text += " : ";
        _text += function;
        _text += " : ";
        _text += arg;
    };

public:

    ArgumentException()
        :
        ArgumentException("Argument caused an exception", __FUNCTION__, "")
    {
    }

    ArgumentException(const char* arg)
        :
        ArgumentException("Argument caused an exception", __FUNCTION__, arg)
    {
    }

    ArgumentException(const char* message, const char* arg)
        :
        ArgumentException(message, __FUNCTION__, arg)
    {
    }

    virtual const char* what() const throw()
    {
        return _text.c_str();
    }
};