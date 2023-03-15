#ifndef SURROUNDINGSAWARE_HH
#define SURROUNDINGSAWARE_HH

#include "point.hh"
#include "spacecube.hh"

const Point OWN_CORDINATES = Point(2,2,2);

class SurroundingsAware {
public:
    virtual void setLocation(SpaceCube* newLocation) = 0;
    virtual SpaceCube* getLocation() const = 0;

};

#endif // SURROUNDINGSAWARE_HH
