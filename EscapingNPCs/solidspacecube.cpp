#include "solidspacecube.hh"

SolidSpaceCube::SolidSpaceCube(GameObject* object) : SpaceCube()
{
    SpaceCube::add(object);
}

bool SolidSpaceCube::add(GameObject *object)
{
    if (occupants_.size() == 1) {
        return false;
    }

    return SpaceCube::add(object);
}

bool SolidSpaceCube::remove(GameObject *object)
{
    if (occupants_.size() == 1) {
        return false;
    }

    return SpaceCube::remove(object);
}
