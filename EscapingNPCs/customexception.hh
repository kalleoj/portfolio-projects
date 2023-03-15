#ifndef CUSTOMEXCEPTION_HH
#define CUSTOMEXCEPTION_HH

#include <exception>
#include <string>

using namespace std;

class CustomException : public exception
{
public:
    CustomException(const string& message);

    const char* what() const throw();

private:
    std::string message_;
};

#endif // CUSTOMEXCEPTION_HH
