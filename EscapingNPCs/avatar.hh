#ifndef AVATAR_HH
#define AVATAR_HH

#include "SurroundingsAware.hh"
#include "solidgameobject.hh"

class Avatar : public SolidGameObject, public SurroundingsAware
{
public:
    Avatar(SpaceCube* location);
    SpaceCube* getLocation() const override;
    void setLocation(SpaceCube*location) override;

private:
    SpaceCube* location_;
};

#endif // AVATAR_HH
