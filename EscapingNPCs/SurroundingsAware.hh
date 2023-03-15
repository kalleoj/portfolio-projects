#ifndef SURROUNDINGSAWARE_HH
#define SURROUNDINGSAWARE_HH

#include "point.hh"
#include "spacecube.hh"

const Point OWN_CORDINATES = Point(2,2,2);

class SurroundingsAware {
public:
    virtual void setSurroundings(Space adjacentSpace) = 0;
    virtual Space getSurroundings() const = 0;
    virtual SpaceCube* getNeighboringSpaceCube(Point direction);

};

#endif // SURROUNDINGSAWARE_HH
