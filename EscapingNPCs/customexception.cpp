#include "customexception.hh"

CustomException::CustomException(const std::string& message) : message_(message)
{

}

const char* CustomException::what() const throw()
{
    return message_.c_str();
}
