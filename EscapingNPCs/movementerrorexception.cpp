#include "movementerrorexception.hh"

MovementErrorException::MovementErrorException(const std::string& message) : message_(message)
{

}

const char *MovementErrorException::what() const throw()
{
    return message_.c_str();
}
