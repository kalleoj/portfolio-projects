#ifndef MOVEMENTERROREXCEPTION_HH
#define MOVEMENTERROREXCEPTION_HH

#include <exception>
#include <string>

using namespace std;

class MovementErrorException : public exception
{
public:
    MovementErrorException(const string& message);

    virtual const char* what() const throw();

private:
    std::string message_;
};

#endif // MOVEMENTERROREXCEPTION_HH
