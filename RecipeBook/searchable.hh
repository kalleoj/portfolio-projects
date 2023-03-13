#ifndef SEARCHABLE_HH
#define SEARCHABLE_HH

#include <string>


class Searchable {
public:
    virtual std::string getName() const = 0;
};

#endif // SEARCHABLE_HH
