#ifndef SPACECUBE_HH
#define SPACECUBE_HH

#include "solidgameobject.hh"

#include <vector>
#include <algorithm>
#include <typeindex>

using namespace std;

class SpaceCube;

using Space = vector<vector<vector<SpaceCube*>>>;
using Plane = vector<vector<SpaceCube*>>;
using Column = vector<SpaceCube*>;

class SpaceCube
{
public:
    SpaceCube();

    bool add(GameObject* object);
    bool remove(GameObject* object);

    vector<GameObject*> getOccupants() const;
    bool setOccupants(vector<GameObject*> newOccupants);

    Space getNeighbors() const;
    bool setNeighbors(Space newNeighbors);

protected:
    vector<GameObject*> occupants_;
    Space neighbors_;
};

#endif // SPACECUBE_HH
