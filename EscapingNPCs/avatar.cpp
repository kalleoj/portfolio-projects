#include "avatar.hh"
#include "customexception.hh"

#include <assert.h>

Avatar::Avatar(SpaceCube* location) : SolidGameObject(), SurroundingsAware(), location_(location)
{
    location->add(this);
}

SpaceCube *Avatar::getLocation() const
{
    return location_;
}

void Avatar::setLocation(SpaceCube* location)
{
    location_ = location;
}
