#include "avatar.hh"

#include <assert.h>

Avatar::Avatar() : SolidGameObject(), SurroundingsAware()
{

}

void Avatar::setSurroundings(Space adjacentSpace)
{
    adjacentSpace_ = adjacentSpace;
}

Space Avatar::getSurroundings() const
{
    return adjacentSpace_;
}

SpaceCube* Avatar::getNeighboringSpaceCube(Point direction)
{
    SpaceCube* cube = adjacentSpace_
            .at(direction.getX())
            .at(direction.getY())
            .at(direction.getZ());
}

SpaceCube* Avatar::getCurrentSpaceCube() {
    SpaceCube* cube = getNeighboringSpaceCube(Point(1,1,1));
    assert(cube != nullptr);
    return cube;
}
