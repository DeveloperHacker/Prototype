#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>

class Exception : public std::exception
{
public:
    std::string name;
    std::string message;

public:
    Exception(const std::string &name, const std::string &message) : name(name), message(message) {}
    ~Exception() = default;
};

#endif // EXCEPTION_H
