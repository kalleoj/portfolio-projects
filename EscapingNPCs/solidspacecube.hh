#ifndef SOLIDSPACECUBE_HH
#define SOLIDSPACECUBE_HH

#include "spacecube.hh"

class SolidSpaceCube : public SpaceCube
{
public:
    SolidSpaceCube(GameObject *object);

    bool add(GameObject* object) override;
    bool remove(GameObject* object) override;
};

#endif // SOLIDSPACECUBE_HH
