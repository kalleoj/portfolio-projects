#ifndef AVATAR_HH
#define AVATAR_HH

#include "SurroundingsAware.hh"
#include "solidgameobject.hh"

class Avatar : public SolidGameObject, public SurroundingsAware
{
public:
    Avatar();

    void setSurroundings(Space adjacentSpace) override;
    Space getSurroundings() const override;
    SpaceCube* getNeighboringSpaceCube(Point direction) override;

    SpaceCube *getCurrentSpaceCube();
private:
    Space adjacentSpace_;
};

#endif // AVATAR_HH
